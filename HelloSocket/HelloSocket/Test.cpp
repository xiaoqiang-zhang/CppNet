#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<WinSock2.h>

//#pragma comment(lib, "ws2_32.lib")
int main()
{
	//-------����Windows Socet 2.x���绷��,���ö�̬��----------//
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//--------------------------
	//--��Socket API�������׵�TCP�ͻ���
	//1.����һ��socket
	//2.���ӷ����� connect
	//3.���շ�������Ϣ recv
	//4.�ر��׽��� closesocket
	//--��Socket API��������TCP�����
	//1.����һ��socket
	//2.�����ڽ��ܿͻ������ӵ�����˿� bind
	//3.��������˿� listen
	//4.�ȴ����տͻ������� accept
	//5.��ͻ��˷���һ������ send
	//6.�ر��׽��� closesocket



	WSACleanup();
	return 0;
} 