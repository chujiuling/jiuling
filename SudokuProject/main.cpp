#include<iostream>
#include <stdlib.h>
#include"generator.h"
#include<fstream>
#include<string.h>
using namespace std;
int a;
int count1 = 0;
int array1[9][9];
int main(int argc, char *argv[])
{
	generator in;
	if (argc < 3)
	{
		cout << "对不起，您输入参数格式有误" << endl;
		return 0;
	}
	if (argv[1][0] != '-' || argv[1][1] != 'c' || argv[1][2] != '\0')
	{
		cout << "第一个参数输入应为 -c !" << endl;
		return 0;//如果输入第一个参数不是-c 不输出
	}
	for (int i=0;argv[2][i]!='\0';i++) 
	{
		if (argv[2][i] < 48 || argv[2][i]>57)
		{
			cout << "请输入所需数独的数目。" << endl;
			return 0;//如果输入第二个参数不是数字 不输出
		}
		a = argv[2][i] - '0' + a * 10;//a为数独数目
	}												 
	
	//cin >> a;
	array1[0][0] = 4;  //学号运算=4 
	in.setNum(0, 1);//从第二格开始试数
}
