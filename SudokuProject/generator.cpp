#include "stdafx.h"
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
int ii, jj;
ofstream out(".//sudoku.txt", ios::out);//�����txt
void generator::print()
{
	if (out.is_open())
	{
		for (ii = 0; ii < 9; ii++)
		{
			for (jj = 0; jj < 8; jj++)
			{
				out << (char)(array1[ii][jj]+48) << ' ';
				//cout << array1[ii][jj] << " ";
			}
			out << (char)(array1[ii][jj] + 48);//������һ��
			//cout << array1[ii][jj];
			out << endl;
			//cout << endl;
		}
		out << endl;
		//cout << endl;
		count1++;//�����м����������
	}//9*9����ȫ�����������
}
void generator::setNum(int x, int y)
{
	if (count1 == a)
	{
		out.close();
		//cout << a << endl;
		//system("pause");
		return;
	}//a�����������ɺ󣬽���
	if (x == 9 && y == 0)
	{
		print();
		return;
	}
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


generator::generator()
{
}


generator::~generator()
{
}
