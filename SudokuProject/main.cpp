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
		cout << "�Բ��������������ʽ����" << endl;
		return 0;
	}
	if (argv[1][0] != '-' || argv[1][1] != 'c' || argv[1][2] != '\0')
	{
		cout << "��һ����������ӦΪ -c !" << endl;
		return 0;//��������һ����������-c �����
	}
	for (int i=0;argv[2][i]!='\0';i++) 
	{
		if (argv[2][i] < 48 || argv[2][i]>57)
		{
			cout << "������������������Ŀ��" << endl;
			return 0;//�������ڶ��������������� �����
		}
		a = argv[2][i] - '0' + a * 10;//aΪ������Ŀ
	}												 
	
	//cin >> a;
	array1[0][0] = 4;  //ѧ������=4 
	in.setNum(0, 1);//�ӵڶ���ʼ����
}
