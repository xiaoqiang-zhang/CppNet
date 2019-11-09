#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<WinSock2.h>

//#pragma comment(lib, "ws2_32.lib")
int main()
{
	//-------启动Windows Socet 2.x网络环境,调用动态库----------//
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//--------------------------
	//--用Socket API建立简易的TCP客户端
	//1.建立一个socket
	//2.连接服务器 connect
	//3.接收服务器信息 recv
	//4.关闭套接字 closesocket
	//--用Socket API建立建议TCP服务端
	//1.建立一个socket
	//2.绑定用于接受客户端连接的网络端口 bind
	//3.监听网络端口 listen
	//4.等待接收客户端连接 accept
	//5.向客户端发送一条数据 send
	//6.关闭套接字 closesocket



	WSACleanup();
	return 0;
} 