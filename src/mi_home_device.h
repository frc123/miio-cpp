#pragma once
#include "stdafx.h"
#include "socket_class.h"

#include "md5.h"

#define CBC 1
#define CTR 0
#define ECB 0
#include "aes.hpp"

#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
using namespace rapidjson;

class MiHomeDevice
{
	struct Msg
	{
		uint16_t length;
		unsigned char did[4];
		uint32_t stamp;
		unsigned char md5_checksum[16];
	};
	int inited_ = 0;
	unsigned char token_[16];
	AES_ctx ctx_;
	uint8_t iv_[16];
	UdpClient udp_client_;
	unsigned char did_[4];
	uint32_t root_stamp_;
	inline int UdpSendSync(void* send_buf, u_int32_t send_buf_size, void* recv_buf, u_int32_t recv_buf_size)
	{
		return udp_client_.SendSync((char*)send_buf, send_buf_size, (char*)recv_buf, recv_buf_size);
	}
	static void Token2AesCtx(const unsigned char* token, AES_ctx* ctx, uint8_t* iv);
	static void UnpackHandshakeMsg(const unsigned char* msg_buf, Msg* msg);
	static void UnpackMsgHeader(const uint8_t* msg_buf, Msg* msg);
	void DecryptPayloads(uint8_t* payloads, uint16_t payloads_len);
	void EncryptPayloads(uint8_t* payloads, uint16_t payloads_len);
	static void PackMsgHeader(const Msg* msg, uint8_t* msg_buf);
	static void FillMd5Checksum(unsigned char* msg_buf, u_int32_t packet_length);
	static void MakePayloads16Multiple(string* payloads_send);
	static void GetPayloadsActualLength(uint8_t* payloads, uint16_t* payloads_len);
	int Init(const unsigned char* token, struct sockaddr_in* addr);
protected:
	int SendCommand(string* payloads);
public:
	int Init(const char* ip_addr, const char* token_ascii_cstr);
	inline int GetInited()
	{
		return inited_;
	}
	void DebugDecryptAsciiHexMsg(const char* msg_asciihex_cstr, string* payload);
//-----------------------------------------------------------------------------------
	struct PropertyId
	{
		string did;
		int siid;
		int piid;
	};
protected:
	PropertyId* property_list_;
	uint32_t packet_id_ = 0;
	inline int GetPacketIdPlus1()
	{
		return ++packet_id_;
	}
private:
	static void WriterAddGetPropertiesParamsSingle(const PropertyId& property,
		Writer<StringBuffer>& writer);
	static void WriterAddGetPropertiesParamsArray(const PropertyId* properties,
		int arr_size, Writer<StringBuffer>& writer);
	template<typename T>
	static int WriterAddSetPropertiesParamsSingle(const PropertyId& property,
		Writer<StringBuffer>& writer, const T* value)
	{
		writer.StartObject();
		writer.Key("did");
		writer.String(property.did.c_str());
		writer.Key("siid");
		writer.Int(property.siid);
		writer.Key("piid");
		writer.Int(property.piid);
		writer.Key("value");
		if (std::is_same<T, int>::value)
		{
			writer.Int(*(int*)value);
		}
		else if (std::is_same<T, bool>::value)
		{
			writer.Bool(*(bool*)value);
		}
		else if (std::is_same<T, float>::value)
		{
			writer.Double(*(float*)value);
		}
		else if (std::is_same<T, string>::value)
		{
			writer.String(((string*)value)->c_str());
		}
		else
		{
			return 0;
		}
		writer.EndObject();
		return 1;
	}
	static void JsonGenGetProperty(int id, PropertyId* property_list, int property_index, string& json_str);
	template<typename T>
	static void JsonGenSetProperty(int id, PropertyId* property_list, int property_index, const T* value,
		string& json_str)
	{
		StringBuffer str_buf;
		Writer<StringBuffer> writer(str_buf);
		writer.StartObject();
		writer.Key("id");   writer.Int(id);
		writer.Key("method");   writer.String("set_properties");
		writer.Key("params");   writer.StartArray();
		WriterAddSetPropertiesParamsSingle(property_list[property_index], writer, value);
		writer.EndArray();
		writer.EndObject();
		json_str = str_buf.GetString();
	}
protected:
	static void JsonGenGetBatchProperties(int id, PropertyId* property_list, int properties_start_index,
		int properties_size, string& json_str);
	template<typename T>
	int GetProperty(int property_index, T* value)
	{
		Document doc;
		string payload;
		JsonGenGetProperty(GetPacketIdPlus1(), property_list_, property_index, payload);
		if (SendCommand(&payload) < 0)
			return 0;
		if (doc.Parse(payload.c_str()).HasParseError())
			return 0;
		if (std::is_same<T, int>::value)
		{
			*value = (T)doc["result"][0]["value"].GetInt();
		}
		else if (std::is_same<T, bool>::value)
		{
			*value = (T)doc["result"][0]["value"].GetBool();
		}
		else if (std::is_same<T, float>::value)
		{
			*value = (T)(doc["result"][0]["value"].GetDouble());
		}

		return 1;
	}
	int GetProperty(int property_index, string* value);
	template<typename T>
	int SetProperty(int property_index, const T* value)
	{
		Document doc;
		string payload;
		MiHomeDevice::JsonGenSetProperty(GetPacketIdPlus1(), property_list_, property_index, value, payload);
		if (SendCommand(&payload) < 0)
			return 0;
		if (doc.Parse(payload.c_str()).HasParseError())
			return 0;
		if (doc["result"][0]["code"].GetInt() != 0)
		{
			return 0;
		}
		return 1;
	}


};
