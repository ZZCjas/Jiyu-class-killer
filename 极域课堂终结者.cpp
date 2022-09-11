#include <iostream>
#include <conio.h>
using namespace std;
int a;
int main()
{
	system("title Fuck极域课堂");
	cout<<"Copyright 2022 赵紫辰\n\n";
	cout<<"温馨提示:Win徽标键+r打开regedit.exe,找到键值PreventKill,将键值改为0后使用本软件效果最佳!\n\n";
	cout<<"请选择杀进程方式:\n1.ntsd.exe(暴力杀进程,无需改键值)\t2.taskkill(在修改键值的的前提下)\n请选择:";
	cin>>a;
	cout<<"开始!\n";
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
