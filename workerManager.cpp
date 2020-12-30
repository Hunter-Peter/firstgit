#include "workerManager.h"
#include "Worker.h"
#include "Employee.h"
#include "Boss.h"
#include "Manager.h"
#include <fstream>
#define FILE "empfile.txt"
workerManager::workerManager()
{
	ifstream ifl;
	ifl.open(FILE, ios::in);
	//判断文件有没有创建
	if (!ifl.is_open())
	{
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_Emparray = NULL;
		this->my_Filesempty = true;
		ifl.close();
		return;
	}
	//文件创建了看看有没有数据
	char ch;
	ifl >> ch;
	if (ifl.eof())
	{
		cout << "文件为空！" << endl;
		int m_EmpNum = 0;
		this->m_Emparray = NULL;
		this->my_Filesempty = true;
		ifl.close();
		return;
	}
	////文件里面有数据
	int num = this->getEmpNum();
	this->m_EmpNum = num;
	//
	////开辟空间
	Worker** m_Emparray = new Worker*[this->m_EmpNum];
	////将数据存入数组
	getEmparray();
	this->my_Filesempty = true;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "员工的编号:" << this->m_Emparray[i]->w_ID
			<< "\t职工的姓名：" << this->m_Emparray[i]->w_Name
			<< "\t岗位编号：" << this->m_Emparray[i]->w_DeptId
			<< endl;
	}
}
//获取记录的职工人数
int workerManager::getEmpNum()
{
	ifstream ifl;
	ifl.open(FILE, ios::in);
	int id;
	string name;
	int pid;
	int num = 0;
	while (ifl>>id&&ifl>>name&&ifl>>pid)
	{
		num++;
	}
	ifl.close();
	return num;
}
//从硬盘输入数据到内存：获取记录的职工信息的数组
void workerManager::getEmparray()
{
	ifstream ifl;
	ifl.open(FILE, ios::in);
	int id;
	string name;
	int pid;
	int index = 0;
	while (ifl >> id && ifl >> name && ifl >> pid)
	{
		Worker* worker = NULL;
		if (pid == 1)
		{
			worker = new Employee(id, name, pid);
		}
		else if (pid == 2)
		{
			worker = new Employee(id, name, pid);
		}
		else
		{
			worker = new Employee(id, name, pid);
		}
		this->m_Emparray[index] = worker;
		index++;
	}
	ifl.close();
	
}
void workerManager::wMmuen()
{
	cout << "********************************** "<<endl;
	cout << "******欢迎使用职工管理系统******** " << endl;
	cout << "**********0.推出管理程序********** " << endl;
	cout << "**********1.增加员工信息********** " << endl;
	cout << "**********2.显示职工信息********** " << endl;
	cout << "**********3.删除离职职工********** " << endl;
	cout << "**********4.修改职工信息********** " << endl;
	cout << "**********5.查找职工信息********** " << endl;
	cout << "**********6.按照编号排序********** " << endl;
	cout << "**********7.清空所有文档********** " << endl;
	cout << "********************************** " << endl;
	cout <<  endl;

};
void workerManager::exitSystem()
{
	cout << "欢迎下次光临" << endl;
	system("pause");//这个函数是用来退出workerManager这个函数的
	exit(0);//这个函数是用来退出整个系统的
}
//从内存输出数据到硬盘，把数据写入到文件中
void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILE, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_Emparray[i]->w_ID << " "
			<< this->m_Emparray[i]->w_Name << " "
			<< this->m_Emparray[i]->w_DeptId << endl;
	}
	ofs.close();
}
void workerManager::addWorker()
{
	cout << "请输入添加的员工个数" << endl;
	int add_Num = 0;
	cin >> add_Num;
	//计算需要多大空间
	int newSpacesize = this->m_EmpNum + add_Num;
	//开辟新空间
	Worker** newSpace = new Worker* [newSpacesize];
	//原数据拷贝到新空间下
	if (m_Emparray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			newSpace[i] = this->m_Emparray[i];
		}
	}
	//批量添加新数据
	for (int i = 0; i < add_Num; i++)
	{
		int wID;
		string w_Name;
		int w_DeptId;
		cout << "请输入需要添加的第" << i+1 << "位员工的编号：" << endl;
		cin >> wID;
		cout << "请输入需要添加的第" << i + 1 << "位员工的姓名：" << endl;
		cin >> w_Name;
		cout << "请输入需要添加的第" << i + 1 << "位员工的岗位编号：" << endl;
		cout << "1.普通员工\t" << "2.经理\t" << "3.老板" << endl;
		cin >> w_DeptId;
		Worker* worker = NULL;
		switch (w_DeptId)
		{
		case 1:
			worker = new Employee(wID, w_Name, 1);
			break;
		case 2:
			worker = new Manager(wID, w_Name, 2);
			break;
		case 3:
			worker = new Boss(wID, w_Name, 3);
			break;
		default:
			break;
		}
		newSpace[m_EmpNum+i] = worker;
	}
	//释放原有空间
	delete[] this->m_Emparray;
	//更新一下m_EmpNum
	m_EmpNum += add_Num;

	//更新一下m_Emparray
	m_Emparray = newSpace;
	//提示添加成功
	cout << "添加成功" << add_Num << "名员工" << endl;
	this->save();
	system("pause");
	system("cls");

}
//显示员工的信息
void workerManager::showInfo()
{
	if (my_Filesempty)
	{
		cout << "文件不存在" << endl;
		return;
	}
	for (int i = 0; i < m_EmpNum; i++)
	{
		this -> m_Emparray[i]->showInfo();
	}
	system("pause");
	system("cls");
}
//判断员工存不存在
int workerManager::isExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (id==this->m_Emparray[i]->w_ID)
		{
			index = 1;
			break;
		}
	}
	return  index;
}
//删除员工
void workerManager::delWorker()
{
	//判断文件存不存在
	if (my_Filesempty)
	{
		cout << "文件为空" << endl;
		return;
	}
	else
	{
		int index = 0;
		cin >> index;
		//判断员工存不存在
		if (isExist(index) !=-1)
		{
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_Emparray[i] = this->m_Emparray[i + 1];
			}
			//跟新一下数组
			this->m_EmpNum--;
			//更新一下硬盘文件
			this->save();
			cout << "删除员工成功"<<endl;
		}
		else
		{
			cout << "查无此人" << endl;
		}
		
	}
	system("pause");
	system("cls");
}
workerManager::~workerManager()
{

}