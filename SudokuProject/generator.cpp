#include "generator.h"
#include <stdio.h>
#include<iostream>
#include<fstream>
using namespace std;
extern int a;//�����������
extern int count1;//�����ɵ�������
extern int array1[9][9];
int flag[81][10] = {};//���ÿ��������Щ�����Թ���
bool temp = true;
void generator::setNum(int x, int y)
{
	ofstream out;
	if (temp)			 
	{
		if (x == 0 && y == 1)
		{
			out.open("sudoku.txt", ios::trunc);//��һ����ڶ���ǰ����ļ�
			temp = false;//������ݵ��ڶ��������
		}
	}
	else                            
	{
		out.open("sudoku.txt", ios::ate | ios::in);//������ָ���ļ�ĩβ����д
	}
	if (count1 == a)
	{
		out.close();
		//cout << a << endl;
		//system("pause");
		return;
	}//a�����������ɺ󣬽��� 
	if (x == 9 && y == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				out << array1[i][j] << " ";
				//cout << array1[i][j] << " ";
			}
			out << endl;
			//cout << endl;
		}
		out << endl;
		//cout << endl;
		count1++;//�����м����������
	}//9*9����ȫ����������� 
	int t = rand() % 10;//���������t
	for (int count_t = 0; count_t < 9;)//�ڸø�����������t 
	{
		if (flag[x * 9 + y][t] == 1)
		{
			t++;//����
			if (t > 9)
				t = 1;
		}
		array1[x][y] = t;
		flag[x * 9 + y][t] = 1;//��ǵ�x*9+y+1���Թ���t��
		count_t++;//�ø��Թ���count_t������

		for (int i = 0; i < 9; i++)
		{
			if ((array1[x][y] == array1[x][i] && i != y) || (array1[x][y] == array1[i][y] && i != x))
				goto here;
		}//���ø�������ͬ��ͬ���Ƿ��ظ� 
		for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++)
			for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
			{
				if (array1[i][j] == array1[x][y] && (i != x && j != y))
					goto here;
			}//���ø������ľŹ������������е����Ƿ��ظ� 
		if (y == 8)
		{
			y = 0;
			x += 1;
		}//���y����8��Ҫ���м�����д
		else y += 1;//��������һ����д
		setNum(x, y);//��д��һ��
		if (y == 0)
		{
			y = 8;
			x -= 1;
		}
		else y -= 1;//���ݷ����ص���һ��
	here:
		array1[x][y] = 0;//�Ե�����������������֮һʱ�ø�ͻᱻ���㣬����������������   
	}

}
