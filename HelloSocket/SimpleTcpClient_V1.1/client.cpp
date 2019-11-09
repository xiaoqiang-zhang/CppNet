#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<WinSock2.h>
#include<stdio.h>

#pragma comment(lib, "ws2_32.lib")
int main()
{
	//-------启动Windows Socet 2.x网络环境,调用动态库----------//
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//--------------------------
	//--用Socket API建立简易的TCP客户端
	//1.建立一个socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("错误，建立Socket失败...\n");
	}
	else
	{
		printf("建立Socket成功...\n");
	}
	//2.连接服务器 connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		printf("错误，连接服务器失败...\n");
	}
	else {
		printf("连接服务器成功...\n");
	}
	while (true)
	{
		//3.输入请求命令
		char cmdBuf[256] = {};
		scanf("%s", cmdBuf);
		//4处理请求命令
		if (0 == strcmp(cmdBuf, "exit"))
		{
			printf("收到退出命令，任务结束");
			break;
		}else{
			//5.向服务器发送请求命令
			send(_sock, cmdBuf, strlen(cmdBuf) + 1, 0);
		}
		//6.接受服务器信息
		char recvBuf[256] = {};
		int nLen = recv(_sock, recvBuf, 256, 0);
		if (nLen > 0)
		{
			printf("接收到数据：%s\n", recvBuf);
		}
	}
	//4.关闭套接字 closesocket
	closesocket(_sock);

	WSACleanup();
	
	getchar();

	return 0;
}