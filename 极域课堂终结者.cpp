#include <iostream>
#include <conio.h>
using namespace std;
int a;
int main()
{
	system("title Fuck�������");
	cout<<"Copyright 2022 ���ϳ�\n\n";
	cout<<"��ܰ��ʾ:Win�ձ��+r��regedit.exe,�ҵ���ֵPreventKill,����ֵ��Ϊ0��ʹ�ñ����Ч�����!\n\n";
	cout<<"��ѡ��ɱ���̷�ʽ:\n1.ntsd.exe(����ɱ����,����ļ�ֵ)\t2.taskkill(���޸ļ�ֵ�ĵ�ǰ����)\n��ѡ��:";
	cin>>a;
	cout<<"��ʼ!\n";
	if(a==1)
	{ 
		system("ntsd -c q -pn studentmain.exe");
	} 
	else
	{
		system("taskkill /f /im studentmain.exe");
	}
	cout<<endl;
	system("pause");
}
