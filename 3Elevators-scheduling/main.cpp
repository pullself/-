#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include "elevator.h"
#include "ask.h"
using namespace std;
ifstream fin;

/* PS�����γ���������ǵ����������ı��ĵ�������д��յĺ�����(�ð������д��) */

ask info[500];//����������� 
elevator ele;//��ͨ���ݶ���
elevator_odd ele_odd;//�������ݶ���
elevator_even ele_even;//ż�����ݶ���
elevator* running = &ele;
int main() 
{
	int n, ask_num, m = 0, ele_a = 0, ele_odd_a = 0, ele_even_a = 0;//m->�Ѵ���������� ,a->��һ��ͣ��λ��
	int fi = -1;
	int fi_p = 0;
	ofstream f1("output1.txt",ios::trunc);
	ofstream f2("output2.txt", ios::trunc);
	ofstream f3("output3.txt", ios::trunc);
	f1.close();
	f2.close();
	f3.close();
    fin.open("input.txt");
	fin>>n;
	ask_num=n;
	for(int i = 0; i < n;i ++)
	{
		fin >> info[i].time >> info[i].floor >> info[i].des;
	} 
	fin.close();
	while(ask_num!=0)
	{   //�������� 
		for(int i = fi+1; i < n; i ++)//����ʱ�����㷨����������
		{
			if (ele.get_time() == info[i].time)
			{
				fi_p = i;
				if ((info[i].floor % 2)==0)//��ʼ����ż��
				{
					if ((info[i].des % 2)==0) ele_even.cre(i,info[i].floor, info[i].des);//Ŀ�Ĳ�Ҳ��ż��
					else if (info[i].des == 1) ele_even.cre(i, info[i].floor, info[i].des);//Ŀ�Ĳ�Ϊ1
					else ele.cre(i, info[i].floor, info[i].des);//Ŀ�Ĳ�Ϊ����
				}
				else//��ʼ��Ϊ����
				{
					if ((info[i].des % 2)==0) ele.cre(i, info[i].floor, info[i].des);//Ŀ�Ĳ�Ϊż��
					else ele_odd.cre(i, info[i].floor, info[i].des);//Ŀ�Ĳ�Ϊ����
				}
			}
		}
		if(fi!=-1) fi = fi_p;
        ele.sorting();
		ele_odd.sorting();
		ele_even.sorting();
        //��������
		running -> run(info, ask_num, n, ele_a);
		running = &ele_odd;
		running -> run(info, ask_num, n, ele_odd_a);
		running = &ele_even;
		running -> run(info, ask_num, n, ele_even_a);
		running = &ele;
    }
	//system("pause");
	return 0;
}
