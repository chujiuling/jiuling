// project4.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
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
	//cout << argv[0] << endl;
	generator in;
	if (argc != 3)
	{
		cout << "please input two parameters."<< endl;
		return 0;
	}
	if (argv[1][0] != '-' || argv[1][1] != 'c' || argv[1][2] != '\0')
	{
		cout << "please input -c as the first parameter." << endl;
		return 0;//如果输入第二个参数不是-c 不输出
	}
	for (int i = 0; argv[2][i] != '\0'; i++)
	{
		if (argv[2][i] < 48 || argv[2][i]>57)
		{
			cout << "please input number as the second parameter." << endl;
			return 0;//如果输入第三个参数不是数字 不输出
		}
		a = argv[2][i] - '0' + a * 10;//a为数独数目
	}
	//cin >> a;
	array1[0][0] = 4;  //学号运算=4 
	in.setNum(0, 1);//从第二格开始试数
}
