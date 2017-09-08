#include "generator.h"
#include <stdio.h>
#include<iostream>
#include<fstream>
using namespace std;
extern int a;//所需的棋盘数
extern int count1;//已生成的棋盘数
extern int array1[9][9];
int flag[81][10] = {};//标记每个格子哪些数字试过了
bool temp = true;
void generator::setNum(int x, int y)
{
	ofstream out;
	if (temp)			 
	{
		if (x == 0 && y == 1)
		{
			out.open("sudoku.txt", ios::trunc);//第一次填第二格前清空文件
			temp = false;//避免回溯到第二格清空了
		}
	}
	else                            
	{
		out.open("sudoku.txt", ios::ate | ios::in);//接下来指向文件末尾接着写
	}
	if (count1 == a)
	{
		out.close();
		//cout << a << endl;
		//system("pause");
		return;
	}//a个数独输出完成后，结束 
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
		count1++;//计算有几个数独输出
	}//9*9格子全部填满，输出 
	int t = rand() % 10;//生成随机数t
	for (int count_t = 0; count_t < 9;)//在该格内试着填入t 
	{
		if (flag[x * 9 + y][t] == 1)
		{
			t++;//试数
			if (t > 9)
				t = 1;
		}
		array1[x][y] = t;
		flag[x * 9 + y][t] = 1;//标记第x*9+y+1格试过了t数
		count_t++;//该格试过了count_t个数字

		for (int i = 0; i < 9; i++)
		{
			if ((array1[x][y] == array1[x][i] && i != y) || (array1[x][y] == array1[i][y] && i != x))
				goto here;
		}//检查该格所处的同行同列是否重复 
		for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++)
			for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
			{
				if (array1[i][j] == array1[x][y] && (i != x && j != y))
					goto here;
			}//检查该格所处的九宫格内其他格中的数是否重复 
		if (y == 8)
		{
			y = 0;
			x += 1;
		}//如果y等于8则要换行继续填写
		else y += 1;//否则右移一格填写
		setNum(x, y);//填写下一格
		if (y == 0)
		{
			y = 8;
			x -= 1;
		}
		else y -= 1;//回溯法，回到上一层
	here:
		array1[x][y] = 0;//试的数不符合三个条件之一时该格就会被置零，尝试填入其他数字   
	}

}
