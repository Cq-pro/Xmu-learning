#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#define MAX_MSG_SIZE 1024
#define SERVER_PORT 49152
#define BACKLOG 5
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main()
{
    printf("Lab6 UDP-服务器\n");
    WORD version = MAKEWORD(2, 0);
    WSADATA wsadata;
    int socket_return = WSAStartup(version, &wsadata); // 初始化套接字库
    if (socket_return != 0)
    {
        getchar();
        getchar();
        return 0;
    } // 这些初始化步骤是必不可少的，否则无法正确创建套接字

    // 删除可能存在的 data.txt 文件
    remove("data.txt");

    // 创建UDP套接字
    int ser_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // 设置套接字超时时间
    timeval tv = { 100, 0 };
    setsockopt(ser_sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(timeval));

    struct sockaddr_in ser_addr; // 服务器地址信息
    struct sockaddr_in cli_addr; // 客户端地址信息

    char msg[MAX_MSG_SIZE]; // 缓冲区，用于存放从客户端接收的数据
    memset(msg, 0, MAX_MSG_SIZE); // 清空缓冲区

    if (ser_sockfd < 0)
    { // 检查套接字是否创建成功
        fprintf(stderr, "Socket Error: %s\n", strerror(errno));
        getchar();
        getchar();
        exit(1);
    }

    // 初始化服务器地址结构
    int addrlen = sizeof(struct sockaddr_in);
    int cli_addrlen = sizeof(struct sockaddr_in);
    memset(&ser_addr, 0, addrlen);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 绑定到本机所有IP地址
    ser_addr.sin_port = htons(SERVER_PORT); // 指定服务器端口

    if (bind(ser_sockfd, (struct sockaddr*)&ser_addr, sizeof(struct sockaddr_in)) < 0)
    { // 绑定套接字
        fprintf(stderr, "Bind Error: %s\n", strerror(errno));
        exit(1);
    }
    printf("服务器已启动，等待客户端连接...\n");

    int num = 0; // 用于计数客户端连接尝试次数
    while (1)
    { // 无限循环，等待和处理客户端请求

        memset(msg, 0, MAX_MSG_SIZE); // 清空缓冲区

        // 接收客户端数据
        int len = recvfrom(ser_sockfd, msg, MAX_MSG_SIZE, 0, (struct sockaddr*)&cli_addr, &cli_addrlen);
        if (len <= 0)
        {
            num++;
            if (num > 100)
            {
                cerr << "客户端 IP：127.0.0.1 失去连接。" << endl;
                remove("data.txt");
                getchar();
                getchar();
                exit(-1);
            }
            else
            {
                continue; // 如果接收失败但未超过尝试次数，继续等待
            }
        }
        num = 0; // 重置计数器
        printf("接收到来自客户端 %s 的连接请求\n", inet_ntoa(cli_addr.sin_addr));
        printf("收到的数据：\n%s\n", msg); // 打印收到的数据

        // 打开文件，将接收到的数据写入文件
        FILE* fp = fopen("data.txt", "a+");
        if (fp == NULL)
        {
            printf("文件无法打开写入！\n");
            _exit(-1);
        }
        printf("将接收到的数据写入文件...\n");
        int write_length = fwrite(msg, sizeof(char), len, fp);
        if (write_length < len)
        {
            printf("文件写入失败！\n");
            break;
        }
        printf("成功接收并保存客户端数据！\n");
        fclose(fp);

        // 发送响应给客户端
        sendto(ser_sockfd, "服务器已收到文件!", sizeof(msg), 0, (struct sockaddr*)&cli_addr, cli_addrlen);
    } // 服务器无限循环运行

    closesocket(ser_sockfd); // 关闭服务器套接字
}
