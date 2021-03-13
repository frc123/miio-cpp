#include "mi_home_device.h"
#include "type_tools.h"

int MiHomeDevice::Init(const unsigned char* token, struct sockaddr_in* addr)
{
    if (inited_)
    {
        return 0;
    }
    //open udp client
    if (udp_client_.OpenUdpClient(addr) == 0)
    {
        return 0;
    }
    //set token
    memcpy(token_, token, 16);
    //set aes ctx
    Token2AesCtx(token_, &ctx_, iv_);
    //handshake
    unsigned char handshake_buf[32] = { 0x21, 0x31, 0, 0x20, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    UdpSendSync(handshake_buf, 32, handshake_buf, 32);
    Msg msg;
    UnpackHandshakeMsg((unsigned char*)handshake_buf, &msg);
    //set did
    memcpy(did_, msg.did, 4);
    //set root_stamp
    time_t seconds;
    time(&seconds);
    root_stamp_ = (uint32_t)seconds - msg.stamp;
    inited_ = 1;
    return 1;
}

//iv has not been set
void MiHomeDevice::Token2AesCtx(const unsigned char* token, AES_ctx* ctx_with_key, uint8_t* iv)
{
    string token_str;
    token_str.append((char*)token, 16);
    MD5* md5;
    md5 = new MD5(token_str);
    const byte* key_byte = md5->getDigest();
	string key_str;
	key_str.append((char*)key_byte, 16);
    AES_init_ctx(ctx_with_key, key_byte);//AES_init_ctx only will use key_byte[0] to key_byte[15]
    delete md5;
    md5 = new MD5(key_str + token_str);
    const byte* iv_byte = md5->getDigest();
    memcpy(iv, iv_byte, 16);
    //AES_init_ctx_iv(ctx, key_byte, iv_byte);
    delete md5;

}

void MiHomeDevice::UnpackHandshakeMsg(const unsigned char* msg_buf, Msg* msg)
{
    memcpy(&(msg->did), &(msg_buf[8]), 4);
    CharToUint32BigEndian(&(msg_buf[12]), &(msg->stamp));
}

void MiHomeDevice::UnpackMsgHeader(const uint8_t* msg_buf, Msg* msg)
{
    CharToUint16BigEndian(&(msg_buf[2]), &(msg->length));
    memcpy(&(msg->did), &(msg_buf[8]), 4);
    CharToUint32BigEndian(&(msg_buf[12]), &(msg->stamp));
    memcpy(&(msg->md5_checksum), &(msg_buf[16]), 16);
}

void MiHomeDevice::DecryptPayloads(uint8_t* payloads, uint16_t payloads_len)
{
    AES_ctx_set_iv(&ctx_, iv_);
    AES_CBC_decrypt_buffer(&ctx_, payloads, payloads_len);
}

void MiHomeDevice::EncryptPayloads(uint8_t* payloads, uint16_t payloads_len)
{
    AES_ctx_set_iv(&ctx_, iv_);
    AES_CBC_encrypt_buffer(&ctx_, payloads, payloads_len);
}

void MiHomeDevice::PackMsgHeader(const Msg* msg, uint8_t* msg_buf)
{
    msg_buf[0] = 0x21;
    msg_buf[1] = 0x31;
    Uint16ToCharBigEndian(&(msg->length), &(msg_buf[2]));
    memset(&(msg_buf[4]), 0, 4);
    memcpy(&(msg_buf[8]), &(msg->did), 4);
    Uint32ToCharBigEndian(&(msg->stamp), &(msg_buf[12]));
    memcpy(&(msg_buf[16]), &(msg->md5_checksum), 16);
}

void MiHomeDevice::FillMd5Checksum(unsigned char* msg_buf, u_int32_t packet_length)
{
    string md5_checksum_str;
    md5_checksum_str.append((char*)msg_buf, packet_length);
    MD5* md5;
    md5 = new MD5(md5_checksum_str);
    //const unsigned char* md5_checksum_byte = md5->getDigest();
    memcpy(&(msg_buf[16]), md5->getDigest(), 16);
    delete md5;
}

void MiHomeDevice::MakePayloads16Multiple(string* payloads_send)
{
    const char empty[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u_int32_t len = (u_int32_t)payloads_send->length();
    int remain = len % 16;
    if (remain != 0)
    {
        remain = 16 - remain;
        payloads_send->append(empty,remain);
    }
}

void MiHomeDevice::GetPayloadsActualLength(uint8_t* payloads, uint16_t* payloads_len)
{

    while (payloads[*payloads_len - 1] != 0x7d && payloads[*payloads_len - 1] != 0)
    {
        (*payloads_len)--;
    }
}

int MiHomeDevice::SendCommand(string* payloads)
{
    MakePayloads16Multiple(payloads);
    uint8_t* buf = new uint8_t[2000];
    uint16_t payloads_len = (uint16_t)payloads->length();
    payloads->copy((char*)&(buf[32]), payloads_len, 0);
    Msg msg;
    msg.length = uint16_t(32 + payloads_len);
    memcpy(msg.did, did_,4);
    time_t seconds;
    time(&seconds);
    msg.stamp = (uint32_t)seconds - root_stamp_;
    memcpy(msg.md5_checksum, token_, 16);
    PackMsgHeader(&msg, buf);
    EncryptPayloads(&(buf[32]), payloads_len);
    FillMd5Checksum(buf, msg.length);
    int ret = UdpSendSync(buf, msg.length, buf, 2000);
    if (ret < 0)
    {
        delete[] buf;
        return ret;//-1 or -2
    }
    //do NOT need msg struct for received msg
    UnpackMsgHeader(buf, &msg);
    payloads_len = (uint16_t)(ret - 32);
    DecryptPayloads(&(buf[32]), payloads_len);
    GetPayloadsActualLength(&(buf[32]), &payloads_len);
    payloads->clear();
    payloads->append((char*)&(buf[32]), payloads_len);
    delete[] buf;
    return 1;//1
}

void MiHomeDevice::DebugDecryptAsciiHexMsg(const char* msg_asciihex_cstr, string* payload)
{
    size_t len;
    len = strlen(msg_asciihex_cstr);
    len /= 2;
    uint8_t* buf = new uint8_t[len];
    Hex2Ascii(msg_asciihex_cstr, buf);
    DecryptPayloads(&(buf[32]), (uint16_t)len);
    payload->clear();
    payload->append((char*)&(buf[32]), len);
    delete[] buf;
}

int MiHomeDevice::Init(const char* ip_addr, const char* token_ascii_cstr)
{
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_addr);
    addr.sin_port = htons(54321);
    unsigned char token_buf[16];
    Hex2Ascii(token_ascii_cstr, token_buf);
    return MiHomeDevice::Init(token_buf, &addr);
}

void MiHomeDevice::WriterAddGetPropertiesParamsSingle(const PropertyId& property,
    Writer<StringBuffer>& writer)
{
    writer.StartObject();
    writer.Key("did");
    writer.String(property.did.c_str());
    writer.Key("siid");
    writer.Int(property.siid);
    writer.Key("piid");
    writer.Int(property.piid);
    writer.EndObject();
}

void MiHomeDevice::WriterAddGetPropertiesParamsArray(const PropertyId* properties,
    int arr_size, Writer<StringBuffer>& writer)
{
    for (int i = 0; i < arr_size; i++)
    {
        WriterAddGetPropertiesParamsSingle(properties[i], writer);
    }
}

void MiHomeDevice::JsonGenGetBatchProperties(int id, PropertyId* property_list, int properties_start_index,
    int properties_size, string& json_str)
{
    StringBuffer str_buf;
    Writer<StringBuffer> writer(str_buf);
    writer.StartObject();
    writer.Key("id");   writer.Int(id);
    writer.Key("method");   writer.String("get_properties");
    writer.Key("params");   writer.StartArray();
    WriterAddGetPropertiesParamsArray(&(property_list[properties_start_index]),
        properties_size, writer);
    writer.EndArray();
    writer.EndObject();
    json_str = str_buf.GetString();
}

void MiHomeDevice::JsonGenGetProperty(int id, PropertyId* property_list, int property_index, string& json_str)
{
    StringBuffer str_buf;
    Writer<StringBuffer> writer(str_buf);
    writer.StartObject();
    writer.Key("id");   writer.Int(id);
    writer.Key("method");   writer.String("get_properties");
    writer.Key("params");   writer.StartArray();
    WriterAddGetPropertiesParamsSingle(property_list[property_index], writer);
    writer.EndArray();
    writer.EndObject();
    json_str = str_buf.GetString();
}

int MiHomeDevice::GetProperty(int property_index, string* value)
{
    Document doc;
    string payload;
    JsonGenGetProperty(GetPacketIdPlus1(), property_list_, property_index, payload);
    if (SendCommand(&payload) < 0)
        return 0;
    if (doc.Parse(payload.c_str()).HasParseError())
        return 0;
    *((string*)value) = doc["result"][0]["value"].GetString();
    return 1;
}


