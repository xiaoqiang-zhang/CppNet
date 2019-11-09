#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

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
	//--用Socket API建立建议TCP服务端
	//1.建立一个socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("错误，建立Socket失败...\n");
	}
	else {
		printf("建立Socket成功...\n");
	}
	//2.绑定用于接受客户端连接的网络端口 bind
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("127.0.0.1")
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)(&_sin), sizeof(sockaddr)))
	{
		printf("Error,绑定网络端口失败...\n");
	}
	else {
		printf("绑定网络端口成功...\n");
	}
	//3.监听网络端口 listen
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("Error,监听网络端口失败...\n");
	}
	else {
		printf("监听网络端口成功...\n");
	}
	//4.等待接收客户端连接 accept
	SOCKET _csock = INVALID_SOCKET;
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	char msgBuf[] = "Hello, I'm your father!";
	while (true)
	{
		_csock =  accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
		if (INVALID_SOCKET == _csock)
		{
			printf("Error,接收到无效的客户端...\n");
		}
		printf("新客户端加入， IP = %s\n", inet_ntoa(clientAddr.sin_addr));
		//5.向客户端发送一条数据 send
		send(_csock, msgBuf, sizeof(msgBuf) + 1, 0);
	}
	//6.关闭套接字 closesocket
	closesocket(_sock);

	WSACleanup();
	return 0;
}