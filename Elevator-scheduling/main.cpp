#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include "elevator.h"
#include "ask.h"
using namespace std;
ifstream fin;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
ask info[500];//����������� 
elevator ele;//һ�����ݶ��� 
int main() 
{
	int n,ask_num,m = 0,a = 0;//m->�Ѵ����������
    int x,y,z;  
    fin.open("input.txt");
	fin>>n;
	ask_num=n;
	for(int i = 0; i < n;i ++)
	{
		fin >> x >> y >> z;
		info[i].time = x+1;
		info[i].floor = y+1;
		info[i].des = z+1;
	} 
	fin.close();
	ele.coo(ask_num,info,a,n);
	/*while(ask_num)
	{   //�������� 
		for(int i = 0; i < n; i ++)
		{
			if(ele.get_time() == info[i].time)
				ele.cre(i,info[i].floor,info[i].des);
		}
        ele.sorting();
        //��������
        ele.run(info,ask_num,a,n);
    }*/
	return 0;
}
