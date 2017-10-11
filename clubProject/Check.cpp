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
		int stu_id;    //ѧ����� 
		double gpa;    //������Ϣ����������ֵ
		vector<string> stu_tags;//��Ȥ��ǩ��������ַ�                                  vector
		vector<string> free_time;//����ʱ��Σ�������ַ�/����									vector
	//	int free_time_times;//����ʱ����� 
	//	int tags_num;//��Ȥ��ǩ���� 
		int applications_dep[5];    //ѧ��־Ը��δȥ�أ�ԭʼ 
	
        double hotAve;    //ѧ��ƽ���ȶ�
        int left;    // ѧ����־Ը�����л�δ��ѡ���Ĳ����� 
        int depid;	// �Ѿ���ѡ�ĸ��� 
		vector<int> stuChosen;    //ѧ��־Ը��ȥ�أ��Ҷ�̬ɾȥƥ������б�ѡ���Ĳ��� 
		vector<int> ResChosen;    //��ѡ�Ĳ����б�
		vector<int> OutChosen;
		bool chooseYN;    //�Ƿ���ѡ
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
		int dep_id;//���
		int member_limit; //��ѧ�������ޣ���������ֵ��0-15
		vector<string> dep_tags;//�ص��ǩ��������ַ�
		vector<string> event_schedules;//����ʱ��Σ�������ַ�/����
	//	int free_time_times;
	//	int tags_num;
		
        int stuSums;    //ѡ��ò��ŵ���δ��ѡ��ѧ����
        int stuResult;    //��ѡ�ò��ŵ�ѧ����
        double hot;    //�����ȶ�
        vector<int> DepStuCho;    //ѡ��ò��ŵ���δ��ѡ��ѧ���б�
        vector<int> DepChosen;    //��ѡ�ò��ŵ�ѧ���б�
        vector<int> OutChosen;
        bool visited;    //ƥ��������Ƿ��Ѿ�ƥ���
};
Student::Student(){
    left = 0;
    hotAve = 0;    //ƽ���ȶȳ�ʼ��Ϊ0
    chooseYN = false;    //��ʼ��Ϊδ��ѡ
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
    visited = false;    //��ʼ��Ϊδƥ��
}
void StuInit(Student *stu, int stuSum){    //¼��ѧ����Ϣ
	for(int i = 0; i < stuSum; i++)
	{
	//	scanf("%d %.5lf", &stu[i].stu_id, &stu[i].gpa);
		cin >> stu[i].stu_id >> stu[i].gpa;
		for(int j = 0; j < 5; j++)
		{
		//	scanf("%d ", &stu[i].applications_dep[j]);
			cin >> stu[i].applications_dep[j];
			stu[i].left++;
			for(int k = 0; k < stu[i].stuChosen.size(); k++){    //����ǰ¼��Ĳ���������Ѿ�¼��Ĳ��������Ƚϣ�����ͬ���ظ�¼��
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
void DepInit(Department *Dep, int DepSum){    //¼�벿����Ϣ
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
			cout << stu[i].stuChosen[j]<< " "; //־Ը
		} 
		cout << endl;
		
		for(int j = 0; j < stu[i].free_time.size(); j++)    //����ʱ��
		{
		cout << stu[i].free_time[j] <<" ";
		}
		for(int j = 0; j < stu[i].stu_tags.size(); j++)    //��ǩ
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
		for(int j = 0; j < Dep[i].event_schedules.size(); j++)    //�̶��ʱ��
		{
			printf("%s ", Dep[i].event_schedules[j].c_str());
		}
		printf("\n");
		for(int j = 0; j < Dep[i].dep_tags.size(); j++)    //���ű�ǩ
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
