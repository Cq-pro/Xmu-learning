#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <winsock.h>
#include <string.h>
#include <time.h>
#include <iostream>
#define MAX_MSG_SIZE 1024
#define SERVER_PORT 49152
#define BACKLOG 5    
char recData[MAX_MSG_SIZE];
char sendData[MAX_MSG_SIZE];
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main(int argc, char* argv[])
{
    printf("Lab6 UDP-客户端 文件名: data.txt\n");
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        getchar(); getchar();
        return 0;
    } // 初始化套接字库，否则无法创建套接字，socket() 会报错。

    SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    // 创建客户端套接字
    if (sclient == INVALID_SOCKET)
    {
        printf("invalid socket !");
        getchar(); getchar();
        return 0;
    }

    timeval tv = { 100, 0 }; // 设置接收超时时间，timeval(x, y) 表示时间 x 秒 + y 微秒
    setsockopt(sclient, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(timeval));

    struct sockaddr_in rec_addr; // 接收地址信息
    struct sockaddr_in sen_addr; // 发送地址信息
    int rec_addrlen = sizeof(struct sockaddr_in);
    int sen_addrlen = sizeof(struct sockaddr_in);

    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(SERVER_PORT);
    serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 使用本地地址
    // serAddr.sin_addr.S_un.S_addr = inet_addr("192.168.3.25"); // 使用其他地址（如果需要）
    // 准备好服务器端的信息，便于连接。
    printf("连接服务器端\n");

    FILE* fp;
    if ((fp = fopen("data.txt", "r")) == NULL)
    {
        printf("文件不存在！\n");
    }
    else
    {
        printf("文件打开成功！\n");
        memset(sendData, 0, MAX_MSG_SIZE);
        int file_block_length = 0;
        int i = 0;
        // 循环读取文件内容到 sendData
        while ((file_block_length = fread(sendData, sizeof(char), MAX_MSG_SIZE, fp)) > 0)
        {
            printf("读取到的文件长度 file_block_length = %d\n", file_block_length);

            // 发送 sendData 中的字符串到服务器端
            if (sendto(sclient, sendData, MAX_MSG_SIZE, 0, (struct sockaddr*)&serAddr, sizeof(serAddr)) < 0)
            {
                printf("文件发送失败！\n");
                break;
            }
            // 清空 sendData 缓存区
            memset(sendData, 0, MAX_MSG_SIZE);
            memset(recData, 0, MAX_MSG_SIZE);
            int ret = recvfrom(sclient, recData, MAX_MSG_SIZE, 0, (struct sockaddr*)&rec_addr, &rec_addrlen); // 接收服务器响应
            if (ret > 0)
            {
                printf("%s\n", recData);
            }
            else if (ret <= 0)
            {
                printf("服务器 127.0.0.1:49152 失去连接！\n");
                getchar(); getchar();
                exit(-1);
            }
        }
        fclose(fp); // 关闭文件描述符
        printf("文件传输成功！\n");
    }

    closesocket(sclient);
    WSACleanup(); // 终止对套接字库的使用
    getchar(); getchar();
    return 0;
}
