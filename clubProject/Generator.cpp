#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#pragma warning(disable : 4996)
using namespace std;
string alltags[10] = {"reading","programming","film","English","music","dance","basketball","chess","running","swimming"};
string week[7] = {"Mon.","Tues.","Wed.","Thurs.","Fri.","Sat.","Sun."};
string ttime[3] = {"15:00~17:00","18:00~20:00","20:00~22:00"};
//学生结构体
struct Student
{
	int id; //编号
	double gpa; //绩点信息，单个，数值
	string stu_tags[10];//兴趣标签，多个，字符
	string free_time[5];//空闲时间段，多个，字符/日期
	int applications_dep[5]; //不多于5个的部门意愿(不能空缺)
	
	int times;
	int tags_num;
};
//部门结构体
struct Department
{
	int id;//编号
	int member_limit; //需学生数上限，单个，数值，0-15
	int depChosen[15]; //最终所选择的学生数组
	string dep_tags[10];//特点标签，多个，字符
	string event_schedules[3];//常规活动时间段，多个，字符/日期
	int times;
	int tags_num;
};
//随机生成学生信息
void Stu(Student *stu, int stuSum, int depSum)
{
	srand((int)time(0));
	for(int i = 0; i < stuSum; i++)
	{
		stu[i].id = i + 1000;                    //学生id生成
		stu[i].gpa = (rand() % 5000) / 1000.0;  //绩点
		//五个志愿部门生成，可能重复
		for(int j = 0; j < 5; j++)
		{
			stu[i].applications_dep[j] = rand() % depSum;
		}
		
		//兴趣标签生成
		stu[i].tags_num = rand() % 10 + 1;
		int t = rand() % 10;
		stu[i].stu_tags[0] = alltags[t];
		for(int j = 1; j < stu[i].tags_num; j++)
		{
			if(t == 9) t = 0;
			else t ++;
			stu[i].stu_tags[j] = alltags[t];
		}
		//空闲时间段生成
		stu[i].times = rand() % 5 + 1;
		int r = rand() % 7;
		for(int j = 0; j < stu[i].times; j++)
		{
			int r2 = r + j;
			int r3 = rand() % 3;
			if (r2 >= 7) r2 -= 7;
			stu[i].free_time[j] = week[r2] + ttime[r3];
		}
	}
}
//打印生成的学生信息
void PrintStu(Student *stu, int stuSum, int depSum)
{
	for(int i = 0; i < stuSum; i++)
	{
		printf("%d %.5lf\n", stu[i].id, stu[i].gpa);
		for(int j = 0; j < 5; j++)
		{
			printf("%d ", stu[i].applications_dep[j]); //志愿
		}
		printf("\n"); 
		for(int j = 0; j < stu[i].times; j++)    //空闲时间
		{
			printf("%s ", stu[i].free_time[j].c_str());
		}
		printf("\n");
		for(int j = 0; j < stu[i].tags_num; j++)    //标签
		{
			printf("%s ", stu[i].stu_tags[j].c_str());
		}
		printf("\n");
	}
	printf("\n");
}
//随机生成部门信息
void Dep(Department *dep, int stuSum, int depSum)
{
	int count = 0;
	srand((int)time(0));
	for(int i = 0; i < depSum; i++)
	{
		dep[i].id = i;
		dep[i].member_limit = rand() % 15 + 1;    //部门纳新人数
		dep[i].tags_num = rand() % 10 + 1;//兴趣标签生成
		int t = rand() % 10;
		dep[i].dep_tags[0] = alltags[t];
		for(int j = 1; j < dep[i].tags_num; j++)
		{
			if(t == 9) t = 0;
			else t ++;
			dep[i].dep_tags[j] = alltags[t];
		}
		//空闲时间段生成
		dep[i].times = rand() % 3 + 1;
		int r = rand() % 7;
		for(int j = 0; j < dep[i].times; j++)
		{
			int r2 = r + j;
			int r3 = rand() % 3;
			if (r2 >= 7) r2 -= 7;
            dep[i].event_schedules[j] = week[r2] + ttime[r3];
		}
	}
}
//打印生成的部门信息
void PrintDep(Department *dep, int stuSum, int depSum)
{
//	int limit =0;
	for(int i = 0; i < depSum; i++)
	{
		printf("%d %d\n", dep[i].id, dep[i].member_limit);
	//	limit +=dep[i].member_limit;
		for(int j = 0; j < dep[i].times; j++)    //固定活动时间
		{
			printf("%s ", dep[i].event_schedules[j].c_str());
		}
		printf("\n");
		for(int j = 0; j < dep[i].tags_num-1; j++)    //部门标签
		{
			printf("%s ",dep[i].dep_tags[j].c_str());
		}
		printf("\n");
	}
//	printf("%d",limit);
}
int main()
{
	Student stu[300];
	Department dep[20];
	freopen("import.txt", "w", stdout);
	printf("300 20\n");
	Stu(stu,300,20);
	PrintStu(stu,300,20);
	Dep(dep,300,20); 
	PrintDep(dep,300,20);
	return 0;
}
