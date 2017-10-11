#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string.h>
#include <cstring> 
#include <string>
using namespace std;
class Department;
class Student{
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
		vector<string> stu_tags;//兴趣标签，多个，字符                                  vector
		vector<string> free_time;//空闲时间段，多个，字符/日期									vector
	//	int free_time_times;//空闲时间个数 
	//	int tags_num;//兴趣标签个数 
		int applications_dep[5];    //学生志愿，未去重，原始 
	
        double hotAve;    //学生平均热度
        int left;    // 学生的志愿部门中还未被选满的部门数 
        int depid;	// 已经中选的个数 
		vector<int> stuChosen;    //学生志愿，去重，且动态删去匹配过程中被选满的部门 
		vector<int> ResChosen;    //中选的部门列表
		vector<int> OutChosen;
		bool chooseYN;    //是否中选
};
class Department{
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
        friend void PrintDep(Department *Dep, int stuSum ,int DepSum);
    private: 
		int dep_id;//编号
		int member_limit; //需学生数上限，单个，数值，0-15
		vector<string> dep_tags;//特点标签，多个，字符
		vector<string> event_schedules;//常规活动时间段，多个，字符/日期
	//	int free_time_times;
	//	int tags_num;
		
        int stuSums;    //选择该部门但还未中选的学生数
        int stuResult;    //中选该部门的学生数
        double hot;    //部门热度
        vector<int> DepStuCho;    //选择该部门但还未中选的学生列表
        vector<int> DepChosen;    //中选该部门的学生列表
        vector<int> OutChosen;
        bool visited;    //匹配过程中是否已经匹配过
};
Student::Student(){
    left = 0;
    hotAve = 0;    //平均热度初始化为0
    chooseYN = false;    //初始化为未中选
    stuChosen.clear(); 
    OutChosen.clear();
    ResChosen.clear();
    depid = 0;
}
Department::Department(){
    stuSums = 0;
    stuResult = 0;
    DepStuCho.clear();
    DepChosen.clear();
    OutChosen.clear();
    visited = false;    //初始化为未匹配
}
void StuInit(Student *stu, int stuSum){    //录入学生信息
	for(int i = 0; i < stuSum; i++)
	{
	//	scanf("%d %.5lf", &stu[i].stu_id, &stu[i].gpa);
		cin >> stu[i].stu_id >> stu[i].gpa;
		for(int j = 0; j < 5; j++)
		{
		//	scanf("%d ", &stu[i].applications_dep[j]);
			cin >> stu[i].applications_dep[j];
			stu[i].left++;
			for(int k = 0; k < stu[i].stuChosen.size(); k++){    //将当前录入的部门序号与已经录入的部门序号相比较，若相同则不重复录入
                if(stu[i].applications_dep[j] == stu[i].stuChosen[k]){
                    stu[i].left--;
                    break;
                }
            }
            if(stu[i].left > stu[i].stuChosen.size()){
                stu[i].stuChosen.push_back(stu[i].applications_dep[j]);
            }
		}
		string str1;
		string tmp;	
		getline(cin,str1);
		getline(cin,str1);
		int len=str1.length();
		int k=0;
		for(int h=0;h<len;h++){
			if(str1[h]!=' '){ 
				tmp.push_back(str1[h]);
			}
			else{
				stu[i].free_time.push_back(tmp);
				tmp.clear();
				while(str1[h]==' ') h++;
				tmp.push_back(str1[h]);
			}
	 	} 
	 	if(tmp.size()>0) stu[i].free_time.push_back(tmp);
	 	getline(cin,str1);
	}

}
void DepInit(Department *Dep, int DepSum){    //录入部门信息
    for(int i = 0; i < DepSum; i++){
        cin >> Dep[i].dep_id >> Dep[i].member_limit; 
      	string str1;
		string tmp;	
		getline(cin,str1);
		getline(cin,str1);
		int len=str1.length();
		int k=0;
		for(int h=0;h<len;h++){
			if(str1[h]!=' '){ 
				tmp.push_back(str1[h]);
			}
			else{
				Dep[i].event_schedules.push_back(tmp);
				tmp.clear();
				while(str1[h]==' ') h++;
				tmp.push_back(str1[h]);
			}
	 	} 
	 	if(tmp.size()>0) Dep[i].event_schedules.push_back(tmp);
	 	getline(cin,str1);
	}
}
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
}
int main()
{
	freopen("a.txt","r",stdin);
    freopen("b.txt","w",stdout);
    int stuSum, DepSum; 
    scanf("%d %d",&stuSum,&DepSum);
    Student *stu = new Student[stuSum];
    Department *Dep = new Department[DepSum];
	StuInit(stu, stuSum);
    DepInit(Dep, DepSum);
    printf("%d %d\n",stuSum,DepSum);
    PrintStu(stu, stuSum, DepSum); 
    PrintDep(Dep, stuSum ,DepSum);
    return 0;
}
