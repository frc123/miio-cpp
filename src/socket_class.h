#pragma once
#include "stdafx.h"

class UdpServer
{
public:
    typedef int (*OnReceiveCallbackFunc)(int, struct sockaddr_in*, char*, void*);
private:
    int sock_fd_;
    struct sockaddr_in addr_serv_;

    void Create(void);
    void FillStructSockaddr(u_int16_t port);
    void Bind(void);
    void StartReceive(char* recv_buf, u_int32_t recv_buf_size, OnReceiveCallbackFunc callback_func, void* data);
    void Close(void);
public:
    void OpenUdpServer(u_int16_t port, char* recv_buf, u_int32_t recv_buf_size, 
                    OnReceiveCallbackFunc callback_func, void* data);
};

class UdpClient
{
private:
    int sock_fd_;
    struct sockaddr_in addr_serv_;

    int Create(void);
    void FillStructSockaddr(struct sockaddr_in* addr_serv);
    void FillStructSockaddr(const char* ip_addr, u_int16_t port);
    int SendOne(char* send_buf, u_int32_t send_buf_size);
    int RecvOne(char* recv_buf, u_int32_t recv_buf_size);
    void Close(void);
public:
    int OpenUdpClient(struct sockaddr_in* addr_serv);
    int SendSync(char* send_buf, u_int32_t send_buf_size, char* recv_buf, u_int32_t recv_buf_size);
};

