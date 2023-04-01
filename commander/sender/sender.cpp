#include<iostream>  
#include<winsock.h>  
#include<cstring>  
#include<string>
#include<cstdio> 
using namespace std;  
char buffer[10001];
char server_name[32];
char client_name[32];  
int relen;
int selen;
WSADATA wsaData;
SOCKET ServerSocket;
int main() 
{
	WSAStartup(MAKEWORD(2,2),&wsaData);
	cout<<"Remote Command Sender\nCopyright 2023 ZZCjas\n";
	ServerSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);  
	if(ServerSocket==INVALID_SOCKET)  
	{  
        cout<<"ERROR";  
	    WSACleanup();  
	    return 0;  
	} 
	SOCKADDR_IN ServerAddr;  
	ServerAddr.sin_family=AF_INET;
    USHORT uPort=8888;
	ServerAddr.sin_port=htons(uPort);
	ServerAddr.sin_addr.S_un.S_addr=INADDR_ANY;  
	if(bind(ServerSocket,(SOCKADDR*)&ServerAddr,sizeof(ServerAddr))==SOCKET_ERROR)
	{  
        cout<<"ERROR";   
        return 0;  
    }  
    listen(ServerSocket,1);    
    SOCKET ClientSocket;  
    SOCKADDR_IN ClientAddr;  
	int ClientAddrlen=sizeof(ClientAddr);  
    cout<<"Waiting for the Client to connect..."<<endl;  
    ClientSocket = accept(ServerSocket,(SOCKADDR*)&ClientAddr,&ClientAddrlen);  
    if(ClientSocket==INVALID_SOCKET)  
	{  
       	cout<<"ERROR:"<<WSAGetLastError();  
       	WSACleanup();  
       	return 0;  
    } 
    client_name[relen]=0;  
    while(1)  
    {  
       	while(1) 
		{
			memset(buffer,0,sizeof(buffer)); 
			cout<<">";
           	cin.getline(buffer,sizeof(buffer));
            selen = send(ClientSocket,buffer,sizeof(buffer),0);  
            cout<<"Command has been sended\n"; 
            if(string(buffer)=="exit")
			{
				WSACleanup();
				return 0;
			}
            int ret=recv(ClientSocket,buffer,sizeof(buffer),0);
			if(ret<0) 
			{
				printf("Failed to receive result!\n");
				break; 
			}
			buffer[ret]=0;
			for(int i=0;i<ret;i++)
			{
				printf("%c",buffer[i]);	
			} 
			puts("");
	    }  
    }  
}  
