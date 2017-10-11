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
//ѧ���ṹ��
struct Student
{
	int id; //���
	double gpa; //������Ϣ����������ֵ
	string stu_tags[10];//��Ȥ��ǩ��������ַ�
	string free_time[5];//����ʱ��Σ�������ַ�/����
	int applications_dep[5]; //������5���Ĳ�����Ը(���ܿ�ȱ)
	
	int times;
	int tags_num;
};
//���Žṹ��
struct Department
{
	int id;//���
	int member_limit; //��ѧ�������ޣ���������ֵ��0-15
	int depChosen[15]; //������ѡ���ѧ������
	string dep_tags[10];//�ص��ǩ��������ַ�
	string event_schedules[3];//����ʱ��Σ�������ַ�/����
	int times;
	int tags_num;
};
//�������ѧ����Ϣ
void Stu(Student *stu, int stuSum, int depSum)
{
	srand((int)time(0));
	for(int i = 0; i < stuSum; i++)
	{
		stu[i].id = i + 1000;                    //ѧ��id����
		stu[i].gpa = (rand() % 5000) / 1000.0;  //����
		//���־Ը�������ɣ������ظ�
		for(int j = 0; j < 5; j++)
		{
			stu[i].applications_dep[j] = rand() % depSum;
		}
		
		//��Ȥ��ǩ����
		stu[i].tags_num = rand() % 10 + 1;
		int t = rand() % 10;
		stu[i].stu_tags[0] = alltags[t];
		for(int j = 1; j < stu[i].tags_num; j++)
		{
			if(t == 9) t = 0;
			else t ++;
			stu[i].stu_tags[j] = alltags[t];
		}
		//����ʱ�������
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
//��ӡ���ɵ�ѧ����Ϣ
void PrintStu(Student *stu, int stuSum, int depSum)
{
	for(int i = 0; i < stuSum; i++)
	{
		printf("%d %.5lf\n", stu[i].id, stu[i].gpa);
		for(int j = 0; j < 5; j++)
		{
			printf("%d ", stu[i].applications_dep[j]); //־Ը
		}
		printf("\n"); 
		for(int j = 0; j < stu[i].times; j++)    //����ʱ��
		{
			printf("%s ", stu[i].free_time[j].c_str());
		}
		printf("\n");
		for(int j = 0; j < stu[i].tags_num; j++)    //��ǩ
		{
			printf("%s ", stu[i].stu_tags[j].c_str());
		}
		printf("\n");
	}
	printf("\n");
}
//������ɲ�����Ϣ
void Dep(Department *dep, int stuSum, int depSum)
{
	int count = 0;
	srand((int)time(0));
	for(int i = 0; i < depSum; i++)
	{
		dep[i].id = i;
		dep[i].member_limit = rand() % 15 + 1;    //������������
		dep[i].tags_num = rand() % 10 + 1;//��Ȥ��ǩ����
		int t = rand() % 10;
		dep[i].dep_tags[0] = alltags[t];
		for(int j = 1; j < dep[i].tags_num; j++)
		{
			if(t == 9) t = 0;
			else t ++;
			dep[i].dep_tags[j] = alltags[t];
		}
		//����ʱ�������
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
//��ӡ���ɵĲ�����Ϣ
void PrintDep(Department *dep, int stuSum, int depSum)
{
//	int limit =0;
	for(int i = 0; i < depSum; i++)
	{
		printf("%d %d\n", dep[i].id, dep[i].member_limit);
	//	limit +=dep[i].member_limit;
		for(int j = 0; j < dep[i].times; j++)    //�̶��ʱ��
		{
			printf("%s ", dep[i].event_schedules[j].c_str());
		}
		printf("\n");
		for(int j = 0; j < dep[i].tags_num-1; j++)    //���ű�ǩ
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
