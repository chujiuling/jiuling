// tmp.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string.h>
#include <cstring> 
#include <string>
using namespace std;
class Department;
class Student {
public:
	Student();
	bool YN(int tno);
	int Getid();
	friend void AddStu(Department *Dep, Student *stu, int stuSum);
	friend void StuInit(Student *stu, int stuSum);
	friend void AddDepHot(Department *Dep, Student *stu, int stuSum);
	friend int cmpgpa(const void *a, const void *b);
	friend int cmpid(const void *a, const void *b);
	friend void StuAdv(Department *Dep, int DepSum, Student *stu, int stuSum);
	friend void Optimize(Department *Dep, Student *stu, int stuSum);
	friend void Cut(Student *stu, int id, int tno);
	friend void PutOut(Department *Dep, int DepSum, Student *stu, int stuSum);
	friend void PrintStu(Student *stu, int stuSum, int depSum);
private:
	int stu_id;    //学生编号 
	double gpa;    //绩点信息，单个，数值
	vector<string> stu_tags;//兴趣标签，多个，字符                                 
	vector<string> free_time;//空闲时间段，多个，字符/日期								
	int applications_dep[5];    //学生志愿，未去重，原始 
	double hotAve;    //学生平均热度
	int left;    // 学生的志愿部门中还未被选满的部门数 
	vector<int> stuChosen;    //学生志愿，去重，且动态删去匹配过程中被选满的部门 
	vector<int> ResChosen;    //中选的部门列表
	vector<int> OutChosen;
	bool chooseYN;    //是否中选
};
class Department {
public:
	Department();
	void DepAddStu(int stuId);
	double GetHot();
	bool GetLeft(int id);
	void Cut(Student *stu, int id, int tno);
	friend void DepInit(Department *Dep, int DepSum);
	friend void CountDepHot(Department *Dep, int DepSum);
	friend void StuAdv(Department *Dep, int DepSum, Student *stu, int stuSum);
	friend void PutOut(Department *Dep, int DepSum, Student *stu, int stuSum);
	friend void PrintDep(Department *Dep, int stuSum, int DepSum);
private:
	int dep_id;//编号
	int member_limit; //需学生数上限，单个，数值，0-15
	vector<string> dep_tags;//特点标签，多个，字符
	vector<string> event_schedules;//常规活动时间段，多个，字符/日期
	int stuSums;    //选择该部门但还未中选的学生数
	int stuResult;    //中选该部门的学生数
	double hot;    //部门热度
	vector<int> DepStuCho;    //选择该部门但还未中选的学生列表
	vector<int> DepChosen;    //中选该部门的学生列表
	vector<int> OutChosen;
	bool visited;    //匹配过程中是否已经匹配过
};
Student::Student() {
	left = 0;
	hotAve = 0;    //平均热度初始化为0
	chooseYN = false;    //初始化为未中选
	stuChosen.clear();
	OutChosen.clear();
	ResChosen.clear();
	/* for(int i=0;i<20;i++)
	{
	ResChosen.push_back(0);
	} */
	//depid = 0;
}
Department::Department() {
	stuSums = 0;
	stuResult = 0;
	DepStuCho.clear();
	DepChosen.clear();
	OutChosen.clear();
	visited = false;    //初始化为未匹配
}
bool Student::YN(int a) {    //判断该学生是否已中选，若未中选，则匹配部门
	if (chooseYN == false) {
		chooseYN = true;
		//    ResChosen[depid] = a;
	}
	return chooseYN;
}

void Department::DepAddStu(int stuId) {    //加入选择该部门的学生序号
	stuSums++;
	DepStuCho.push_back(stuId );
}
double Department::GetHot() {    //返回该部门的热度
	return hot;
}
void AddStu(Department *Dep, Student *stu, int stuSum) {    //将学生序号加入到各志愿部门下的列表中
	for (int i = 0; i < stuSum; i++) {
		for (int j = 0; j < stu[i].left; j++) {
			Dep[stu[i].stuChosen[j]].DepAddStu(i);
		}
	}
}
void CountDepHot(Department *Dep, int DepSum) {    //计算部门热度
	for (int i = 0; i < DepSum; i++) {
		Dep[i].hot = (Dep[i].stuSums * 1.0) / (Dep[i].member_limit * 1.0);
	}
}
void AddDepHot(Department *Dep, Student *stu, int stuSum) {    //计算学生所选的未被选满的部门的平均热度
	for (int i = 0; i < stuSum; i++) {
		stu[i].hotAve = stu[i].gpa;
	}
}
void StuInit(Student *stu, int stuSum) {    //录入学生信息
	for (int i = 0; i < stuSum; i++)
	{
		cin >> stu[i].stu_id >> stu[i].gpa;
		for (int j = 0; j < 5; j++)
		{
			cin >> stu[i].applications_dep[j];
			stu[i].left++;
			for (int k = 0; k < (int)stu[i].stuChosen.size(); k++) {    //将当前录入的部门序号与已经录入的部门序号相比较，若相同则不重复录入
				if (stu[i].applications_dep[j] == stu[i].stuChosen[k]) {
					stu[i].left--;
					break;
				}
			}
			if (stu[i].left >(int) stu[i].stuChosen.size()) {
				stu[i].stuChosen.push_back(stu[i].applications_dep[j]);
			}
		}
		string str1;     //bug所在 读取多个以空格分隔的字符串  
		string tmp;
		getline(cin, str1);
		getline(cin, str1);
		int len = str1.length();
		int k = 0;
		for (int h = 0; h<len; h++) {
			if (str1[h] != ' ') {
				tmp.push_back(str1[h]);
			}
			else {
				stu[i].free_time.push_back(tmp);
				tmp.clear();
				while (str1[h] == ' ') h++;
				tmp.push_back(str1[h]);
			}
		}
		if (tmp.size()>0) stu[i].free_time.push_back(tmp);
		getline(cin, str1);
	}

}
void DepInit(Department *Dep, int DepSum) {    //录入部门信息
	for (int i = 0; i < DepSum; i++) {
		cin >> Dep[i].dep_id >> Dep[i].member_limit;
		string str1;
		string tmp;
		getline(cin, str1);
		getline(cin, str1);
		int len = str1.length();
		int k = 0;
		for (int h = 0; h<len; h++) {
			if (str1[h] != ' ') {
				tmp.push_back(str1[h]);
			}
			else {
				Dep[i].event_schedules.push_back(tmp);
				tmp.clear();
				while (str1[h] == ' ') h++;
				tmp.push_back(str1[h]);
			}
		}
		if (tmp.size()>0) Dep[i].event_schedules.push_back(tmp);
		getline(cin, str1);
	}
}/*
 void PrintStu(Student *stu, int stuSum, int depSum)
 {
 for(int i = 0; i < stuSum; i++)
 {
 cout << stu[i].stu_id <<" "<<  stu[i].gpa <<endl;
 for(int j = 0; j < stu[i].stuChosen.size(); j++)
 {
 cout << stu[i].stuChosen[j]<< " "; //志愿
 }
 cout << endl;

 for(int j = 0; j < stu[i].free_time.size(); j++)    //空闲时间
 {
 cout << stu[i].free_time[j] <<" ";
 }
 for(int j = 0; j < stu[i].stu_tags.size(); j++)    //标签
 {
 cout << stu[i].stu_tags[j] << " ";
 }
 cout << endl;
 }
 cout<< endl;
 return;
 }
 void PrintDep(Department *Dep, int stuSum, int DepSum)
 {
 for(int i = 0; i < DepSum; i++)
 {
 printf("%d %d\n", Dep[i].dep_id, Dep[i].member_limit);
 for(int j = 0; j < Dep[i].event_schedules.size(); j++)    //固定活动时间
 {
 printf("%s ", Dep[i].event_schedules[j].c_str());
 }
 printf("\n");
 for(int j = 0; j < Dep[i].dep_tags.size(); j++)    //部门标签
 {
 printf("%s ",Dep[i].dep_tags[j].c_str());
 }
 printf("\n");
 }
 }*/
void StuAdv(Department *Dep, int DepSum, Student *stu, int stuSum) {    //按低热度优先原则开始匹配
	int tmpDep = DepSum;
	while (tmpDep--) {    //循环轮数为部门总数
		int minHot = -1;    //查找并记录热度最低的部门的序号
		for (int i = 0; i < DepSum; i++) {
			if (Dep[i].visited == false && (minHot == -1 || Dep[i].hot < Dep[minHot].hot)) {
				minHot = i;
			}
		}
		Dep[minHot].visited = true;    //将该部门标记为已匹配
		int tmp = 0;
		if (Dep[minHot].member_limit > Dep[minHot].stuSums)
			 tmp = Dep[minHot].stuSums;
		else
			 tmp = Dep[minHot].member_limit;
		//int tmp = min(Dep[minHot].member_limit, Dep[minHot].stuSums);    //待选该部门的学生总数
		while (tmp--) {
			int maxId = 0;    //记录竞争力最强的同学的下标  
			double maxHotSum = stu[Dep[minHot].DepStuCho[maxId]].hotAve;    //最强竞争力 
			double  getHotSum;    //临时变量 
							  //高绩点优先  
			for (int i = 1; i <(int) Dep[minHot].DepStuCho.size(); i++) {
				getHotSum = stu[Dep[minHot].DepStuCho[i]].hotAve;
				if (getHotSum > maxHotSum) {
					maxHotSum = getHotSum;
					maxId = i;
				}
			}
			int maxHotStu = Dep[minHot].DepStuCho[maxId];    //最强竞争力下标 
															 //进行时间匹配判断
			bool flag = false;
			for (int t = 0; t < (int)stu[maxHotStu].free_time.size(); t++)
			{
				for (int k = 0; k <(int) Dep[minHot].event_schedules.size(); k++)
				{
					if (Dep[minHot].event_schedules[k] == stu[maxHotStu].free_time[t])
					{
						//		stu[maxHotStu].free_time.erase(stu[maxHotStu].free_time.begin() + t);
						flag = true; //合格了 
						Dep[minHot].stuResult++;    //部门中选个数 
						Dep[minHot].DepChosen.push_back(stu[maxHotStu].stu_id); // 部门的中选学生列表增加该学生的记录
						Dep[minHot].stuSums--;    //部门未中选学生个数 
						Dep[minHot].DepStuCho.erase(Dep[minHot].DepStuCho.begin() + maxId);//部门的未中选学生列表删除该学生的记录
						stu[maxHotStu].ResChosen.push_back(Dep[minHot].dep_id); //学生的中选部门列表增加该部门 
						stu[maxHotStu].hotAve -= 100; //竞争力分层 
						for (int j = 0; j < stu[maxHotStu].left; j++)//未中选部门列表 删除该部门 
						{
							if (stu[maxHotStu].stuChosen[j] == Dep[minHot].dep_id) {
								stu[maxHotStu].stuChosen.erase(stu[maxHotStu].stuChosen.begin() + j);
								break;
							}
						}
						stu[maxHotStu].left--;
						goto here;
					}
				}
			}
		here:
			if (!flag)  //匹配失败 
				tmp++;
		}
		//删除未中选同学记录
		for (int i = 1; i < Dep[minHot].stuSums; i++) {
			int tag = Dep[minHot].DepStuCho[i]; //未中选同学下标  
			for (int j = 0; j < stu[tag].left; j++) {  //初始stuChosen为所有部门，现删除匹配失败的部门  
				if (stu[tag].stuChosen[j] == minHot) {
					stu[tag].stuChosen.erase(stu[tag].stuChosen.begin() + j);
					break;
				}
			}
			stu[tag].left--;
		}
	}
}

void PutOut(Department *Dep, int DepSum, Student *stu, int stuSum) {    //输出函数
	vector<int> stuLeft;    //未中选学生列表
	vector<int> DepLeft;    //未分配部门列表
	printf("/*学生匹配结果*/\n");
	//printf("/*dfsfdsfs*/\n");
	for (int i = 0; i < stuSum; i++) {
		if (stu[i].ResChosen.size() != 0) {   //都选上  
			printf("学号为%d的学生的部门序号: \n", stu[i].stu_id);
			for (int j = 0; j <(int) stu[i].ResChosen.size(); j++) {
				printf("%d ", stu[i].ResChosen[j]);
			}
			printf("\n");
		}
		else {
			stuLeft.push_back(stu[i].stu_id);
		}
	}
	printf("\n/*部门匹配结果*/\n");
	for (int i = 0; i < DepSum; i++) {
		if (Dep[i].stuResult == 0) {
			DepLeft.push_back(Dep[i].dep_id);
		}
		else {
			printf("序号为%d的部门选中%d名学生:\n", i, Dep[i].stuResult);
			for (int j = 0; j < Dep[i].stuResult; j++) {
				printf("%d ", Dep[i].DepChosen[j]);
			}
			printf("\n");
		}
	}
	int limitSum = 0;
	int ResSum = 0;
	for (int k = 0; k < DepSum; k++)
	{
		limitSum += Dep[k].member_limit;
		ResSum += Dep[k].stuResult;
	}
	printf("\n部门期望招收人数：%d\n", limitSum);
	int a = 0;
	a = 300 - stuLeft.size();
	printf("部门实际招收人数：%d\n", a);
	if (stuLeft.size() == 0) printf("\n所有学生都已中选部门\n");
	else {
		printf("\n未被部门选中的学生: \n");                //未被分配到学生的部门 和 未被部门选中的学生
		for (int i = 0; i < (int)stuLeft.size(); i++) {
			printf("%d ", stuLeft[i]);
		}
		printf("\n");
	}
	if (DepLeft.size() == 0)printf("\n所有部门都已分配到学生\n");
	else {
		printf("\n未被分配到学生的部门:");
		for (int i = 0; i <(int) DepLeft.size(); i++) {
			printf("%d ", DepLeft[i]);
		}
		printf("\n");
	}
}
int main()
{
	FILE *stream;
	freopen_s(&stream, "import.txt", "r", stdin);
	freopen_s(&stream, "output_condition2.txt", "w", stdout);
	int stuSum, DepSum;
	scanf_s("%d %d", &stuSum, &DepSum);
	Student *stu = new Student[stuSum];
	Department *Dep = new Department[DepSum];
	StuInit(stu, stuSum);
	DepInit(Dep, DepSum);
	//printf("%d %d\n", stuSum, DepSum);
	/*  PrintStu(stu, stuSum, DepSum);
	PrintDep(Dep, stuSum ,DepSum);*/
	AddStu(Dep, stu, stuSum);
	CountDepHot(Dep, DepSum);
	AddDepHot(Dep, stu, stuSum);
	StuAdv(Dep, DepSum, stu, stuSum);
	PutOut(Dep, DepSum, stu, stuSum);
	return 0;
}

