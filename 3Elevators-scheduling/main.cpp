#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include "elevator.h"
#include "ask.h"
using namespace std;
ifstream fin;

/* PS：单次程序运行完记得清空输出的文本文档，懒得写清空的函数了(好吧最后还是写了) */

ask info[500];//请求对象数组 
elevator ele;//普通电梯对象
elevator_odd ele_odd;//奇数电梯对象
elevator_even ele_even;//偶数电梯对象
elevator* running = &ele;
int main() 
{
	int n, ask_num, m = 0, ele_a = 0, ele_odd_a = 0, ele_even_a = 0;//m->已处理请求个数 ,a->上一次停靠位置
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
	{   //构建队列 
		for(int i = fi+1; i < n; i ++)//迫于时间无算法的垃圾调度
		{
			if (ele.get_time() == info[i].time)
			{
				fi_p = i;
				if ((info[i].floor % 2)==0)//起始层是偶数
				{
					if ((info[i].des % 2)==0) ele_even.cre(i,info[i].floor, info[i].des);//目的层也是偶数
					else if (info[i].des == 1) ele_even.cre(i, info[i].floor, info[i].des);//目的层为1
					else ele.cre(i, info[i].floor, info[i].des);//目的层为奇数
				}
				else//起始层为奇数
				{
					if ((info[i].des % 2)==0) ele.cre(i, info[i].floor, info[i].des);//目的层为偶数
					else ele_odd.cre(i, info[i].floor, info[i].des);//目的层为奇数
				}
			}
		}
		if(fi!=-1) fi = fi_p;
        ele.sorting();
		ele_odd.sorting();
		ele_even.sorting();
        //电梯运行
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
