#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<winsock.h>
#include <string.h>
#include<time.h>
#include<iostream>
#define MAX_MSG_SIZE 1024
#define SERVER_PORT 49152
#define BACKLOG 5    
char recData[MAX_MSG_SIZE];
char sendData[MAX_MSG_SIZE];
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main(int argc, char* argv[])
{
    printf("实验6 TCP 客户端 文件名: data.txt\n");
    WORD sockVersion = MAKEWORD(2, 2);
    // 初始化Winsock
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        getchar(); getchar();
        return 0;
    }// 初始化Winsock 是必需的，否则无法创建套接字插口。

    // 创建套接字
    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // 客户端套接字的创建
    if (sclient == INVALID_SOCKET)
    {
        printf("无效的套接字!");
        getchar(); getchar();
        return 0;
    }
    // 设置服务器地址信息
    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(SERVER_PORT);
    serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 设置服务器IP地址为本机地址

    printf("连接服务器端\n");
    // 尝试连接服务器
    if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        printf("连接错误 !");
        closesocket(sclient);
        getchar(); getchar();
        return 0;
    }


    //char file_name[1000];
    //memset(file_name, 0, 1000);
    //strncpy(file_name, buffer, strlen(buffer) > FILE_NAME_MAX_SIZE ? FILE_NAME_MAX_SIZE : strlen(buffer));
    FILE* fp;
    if ((fp = fopen("data.txt", "r")) == NULL)
    {
        printf("文件不存在！\n");
    }
    else
    {
        printf("文件打开成功！\n");
        //bzero(buffer, BUFFER_SIZE);
        memset(sendData, 0, MAX_MSG_SIZE);
        int file_block_length = 0;
        // 循环将文件内容读取到sendData中
        int i = 0;
        while ((file_block_length = fread(sendData, sizeof(char), MAX_MSG_SIZE, fp)) > 0)
        {
            //测试
            i++;
            if (i == 2) {
                closesocket(sclient);
                WSACleanup();//终止对套接字库的使用。
                getchar(); getchar();
                return 0;
            }
            printf("读取到的文件长度file_block_length = %d\n", file_block_length);

            // 发送sendData中的数据到服务器端
            if (send(sclient, sendData, MAX_MSG_SIZE, 0) < 0)
            {
                printf("文件发送失败！\n");
                break;
            }
            //清空sendData缓存区
            memset(sendData, 0, MAX_MSG_SIZE);
            memset(recData, 0, MAX_MSG_SIZE);
            int ret = recv(sclient, recData, MAX_MSG_SIZE, 0); // 返回的是收到的实际字节数
            if (ret > 0)
            {

                printf(recData);
                printf("\n");
            }
            else if (ret <= 0) {
                printf("服务器 127.0.0.1:49152 失去连接!\n");
                getchar(); getchar();
                exit(-1);
            }
        }
        fclose(fp);  // 关闭文件描述符
        printf("文件传输成功！\n");
    }

    int ret = recv(sclient, recData, MAX_MSG_SIZE, 0); // 返回的是收到的实际字节数
    if (ret > 0)
    {

        printf(recData);
        printf("\n");
    }
    else if (ret <= 0) {
        printf("服务器 127.0.0.1:49152 失去连接!\n");
        getchar(); getchar();
        exit(-1);
    }

    closesocket(sclient);
    WSACleanup();// 终止对套接字库的使用。
    getchar(); getchar();
    return 0;
}
