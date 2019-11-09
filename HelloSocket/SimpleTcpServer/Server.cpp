#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<Windows.h>
#include<WinSock2.h>
#include<stdio.h>

#pragma comment(lib, "ws2_32.lib")
int main()
{
	//-------����Windows Socet 2.x���绷��,���ö�̬��----------//
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//--��Socket API��������TCP�����
	//1.����һ��socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("���󣬽���Socketʧ��...\n");
	}
	else {
		printf("����Socket�ɹ�...\n");
	}
	//2.�����ڽ��ܿͻ������ӵ�����˿� bind
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("127.0.0.1")
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)(&_sin), sizeof(sockaddr)))
	{
		printf("Error,������˿�ʧ��...\n");
	}
	else {
		printf("������˿ڳɹ�...\n");
	}
	//3.��������˿� listen
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("Error,��������˿�ʧ��...\n");
	}
	else {
		printf("��������˿ڳɹ�...\n");
	}
	//4.�ȴ����տͻ������� accept
	SOCKET _csock = INVALID_SOCKET;
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	char msgBuf[] = "Hello, I'm your father!";
	while (true)
	{
		_csock =  accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
		if (INVALID_SOCKET == _csock)
		{
			printf("Error,���յ���Ч�Ŀͻ���...\n");
		}
		printf("�¿ͻ��˼��룬 IP = %s\n", inet_ntoa(clientAddr.sin_addr));
		//5.��ͻ��˷���һ������ send
		send(_csock, msgBuf, sizeof(msgBuf) + 1, 0);
	}
	//6.�ر��׽��� closesocket
	closesocket(_sock);

	WSACleanup();
	return 0;
}