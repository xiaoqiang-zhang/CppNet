#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<Windows.h>
#include<WinSock2.h>
#include<stdio.h>

#pragma comment(lib, "ws2_32.lib")

struct DataPackage
{
	int age;
	char name[32];
};

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

	_csock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (INVALID_SOCKET == _csock)
	{
		printf("Error,���յ���Ч�Ŀͻ���...\n");
		return -1;
	}
	printf("�¿ͻ��˼��룬Socket=%d, IP = %s\n", (int)_csock, inet_ntoa(clientAddr.sin_addr));

	char _recvBuf[256] = {};
	while (true)
	{
		//5.���տͻ��˵���������
		int nLen = recv(_csock, _recvBuf, 256, 0);
		if (nLen <= 0)
		{
			printf("�ͻ������˳����������...\n");
			break;
		}
		printf("�յ�����:%s\n", _recvBuf);
		//6.��������
		if (0 == strcmp(_recvBuf, "getInfo"))
		{
			DataPackage dp = { 80, "̷ӽ��" };
			//char msgBuf[] = "xiaoQiang";
			//7.��ͻ��˷���һ������ send
			send(_csock, (const char*)&dp, sizeof(DataPackage), 0);
		}
		//else if (0 == strcmp(_recvBuf, "getAge"))
		//{
		//	char msgBuf[] = "26";
			//7.��ͻ��˷���һ������ send
		//	send(_csock, msgBuf, sizeof(msgBuf) + 1, 0);
		//}
		else {
			//7.��ͻ��˷���һ������ send
			char msgBuf[] = "???.";
			send(_csock, msgBuf, sizeof(msgBuf) + 1, 0);
		}
		
	}
	//8.�ر��׽��� closesocket
	closesocket(_sock);

	WSACleanup();
	printf("���˳����������");

	getchar();

	return 0;
}