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
	//�ж��ļ���û�д���
	if (!ifl.is_open())
	{
		cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_Emparray = NULL;
		this->my_Filesempty = true;
		ifl.close();
		return;
	}
	//�ļ������˿�����û������
	char ch;
	ifl >> ch;
	if (ifl.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		int m_EmpNum = 0;
		this->m_Emparray = NULL;
		this->my_Filesempty = true;
		ifl.close();
		return;
	}
	////�ļ�����������
	int num = this->getEmpNum();
	this->m_EmpNum = num;
	//
	////���ٿռ�
	Worker** m_Emparray = new Worker*[this->m_EmpNum];
	////�����ݴ�������
	getEmparray();
	this->my_Filesempty = true;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "Ա���ı��:" << this->m_Emparray[i]->w_ID
			<< "\tְ����������" << this->m_Emparray[i]->w_Name
			<< "\t��λ��ţ�" << this->m_Emparray[i]->w_DeptId
			<< endl;
	}
}
//��ȡ��¼��ְ������
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
//��Ӳ���������ݵ��ڴ棺��ȡ��¼��ְ����Ϣ������
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
	cout << "******��ӭʹ��ְ������ϵͳ******** " << endl;
	cout << "**********0.�Ƴ��������********** " << endl;
	cout << "**********1.����Ա����Ϣ********** " << endl;
	cout << "**********2.��ʾְ����Ϣ********** " << endl;
	cout << "**********3.ɾ����ְְ��********** " << endl;
	cout << "**********4.�޸�ְ����Ϣ********** " << endl;
	cout << "**********5.����ְ����Ϣ********** " << endl;
	cout << "**********6.���ձ������********** " << endl;
	cout << "**********7.��������ĵ�********** " << endl;
	cout << "********************************** " << endl;
	cout <<  endl;

};
void workerManager::exitSystem()
{
	cout << "��ӭ�´ι���" << endl;
	system("pause");//��������������˳�workerManager���������
	exit(0);//��������������˳�����ϵͳ��
}
//���ڴ�������ݵ�Ӳ�̣�������д�뵽�ļ���
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
	cout << "��������ӵ�Ա������" << endl;
	int add_Num = 0;
	cin >> add_Num;
	//������Ҫ���ռ�
	int newSpacesize = this->m_EmpNum + add_Num;
	//�����¿ռ�
	Worker** newSpace = new Worker* [newSpacesize];
	//ԭ���ݿ������¿ռ���
	if (m_Emparray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			newSpace[i] = this->m_Emparray[i];
		}
	}
	//�������������
	for (int i = 0; i < add_Num; i++)
	{
		int wID;
		string w_Name;
		int w_DeptId;
		cout << "��������Ҫ��ӵĵ�" << i+1 << "λԱ���ı�ţ�" << endl;
		cin >> wID;
		cout << "��������Ҫ��ӵĵ�" << i + 1 << "λԱ����������" << endl;
		cin >> w_Name;
		cout << "��������Ҫ��ӵĵ�" << i + 1 << "λԱ���ĸ�λ��ţ�" << endl;
		cout << "1.��ͨԱ��\t" << "2.����\t" << "3.�ϰ�" << endl;
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
	//�ͷ�ԭ�пռ�
	delete[] this->m_Emparray;
	//����һ��m_EmpNum
	m_EmpNum += add_Num;

	//����һ��m_Emparray
	m_Emparray = newSpace;
	//��ʾ��ӳɹ�
	cout << "��ӳɹ�" << add_Num << "��Ա��" << endl;
	this->save();
	system("pause");
	system("cls");

}
//��ʾԱ������Ϣ
void workerManager::showInfo()
{
	if (my_Filesempty)
	{
		cout << "�ļ�������" << endl;
		return;
	}
	for (int i = 0; i < m_EmpNum; i++)
	{
		this -> m_Emparray[i]->showInfo();
	}
	system("pause");
	system("cls");
}
//�ж�Ա���治����
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
//ɾ��Ա��
void workerManager::delWorker()
{
	//�ж��ļ��治����
	if (my_Filesempty)
	{
		cout << "�ļ�Ϊ��" << endl;
		return;
	}
	else
	{
		int index = 0;
		cin >> index;
		//�ж�Ա���治����
		if (isExist(index) !=-1)
		{
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_Emparray[i] = this->m_Emparray[i + 1];
			}
			//����һ������
			this->m_EmpNum--;
			//����һ��Ӳ���ļ�
			this->save();
			cout << "ɾ��Ա���ɹ�"<<endl;
		}
		else
		{
			cout << "���޴���" << endl;
		}
		
	}
	system("pause");
	system("cls");
}
workerManager::~workerManager()
{

}