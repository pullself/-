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

int n, ask_num, m = 0, ele_a = 0, ele_odd_a = 0, ele_even_a = 0;//m->已处理请求个数 ,a->上一次停靠位置
int fi = -1;
int fi_p = 0;
char address[5][100];//文件地址

void address_change(char* aft, char* bef);
void address_copy(char* aft, char* bef,int num);
void run_fun(void);
void out_change(char* str);

int main(int argc,char** argv)
{
	memset(address, '\0', sizeof(address));//初始化
	char order[100];
	int error = 0;
	if (argc == 2)
	{
		if (strcmp(argv[1], "run") == 0)
		{
			cout << "   错误：缺少input文件地址" << endl;
			cout << "   需要更多帮助请输入help" << endl;
			error = 1;
		}
		else if (strcmp(argv[1], "help") == 0)
		{
			cout << "   *:\\****\\input.txt：输入input文件地址" << endl;
			cout << "   *:\\****\\outputi.txt：输入output文件地址，i=1,2,3，若不给出默认为input文件目录" << endl;
			cout << "   run：运行程序" << endl;
			cout << "   view：查看文件地址" << endl;
			cout << "   end：中止程序" << endl;
			error = 1;
		}
		else if (strcmp(argv[1], "view") == 0)
		{
			cout << "   input:缺失" << endl;
			cout << "   output1:当前目录" << endl;
			cout << "   output2:当前目录" << endl;
			cout << "   output3:当前目录" << endl;
			error = 1;
		}
		else if (strcmp(argv[1], "end") == 0)
		{
			cout << "   运行终止" << endl;
			return 0;
		}
		else if (strstr(argv[1], "input") != NULL)
		{
			address_change(address[1], argv[1]);
			for (int i = 2; i < 5; i++)
			{
				address_copy(address[i], address[1], i - 1);
			}
			run_fun();
			cout << "   运行结束" << endl;
			return 0;
		}
		else if (strstr(argv[1], "output") != NULL)
		{
			cout << "   错误：缺少input文件地址" << endl;
			out_change(argv[1]);
			cout << "   output地址已存储" << endl;
			cout << "   需要更多帮助请输入help" << endl;
			error = 1;
		}
		else
		{
			cout << "   错误：非法输入" << endl;
			cout << "   需要更多帮助请输入help" << endl;
			error = 1;
		}
	}
	else
	{
		if (argc == 1)
		{
			strcpy_s(address[1], "input.txt");
			strcpy_s(address[2], "output1.txt");
			strcpy_s(address[3], "output2.txt");
			strcpy_s(address[4], "output3.txt");
			run_fun();
			cout << "   运行结束" << endl;
			return 0;
		}
		else if (argc > 2)
		{
			if (strstr(argv[1], "input") == NULL)
			{
				cout << "   错误：非法输入" << endl;
				cout << "   需要更多帮助请输入help" << endl;
				error = 1;
			}
			else
			{
				address_change(address[1], argv[1]);
				for (int i = 2; i < 5; i++)
				{
					address_copy(address[i], address[1], i - 1);
				}
				for (int i = 2; i < argc; i++)
				{
					out_change(argv[i]);
				}
				run_fun();
				cout << "   运行结束" << endl;
				return 0;
			}
		}
	}
	while (error == 1)
	{
		cin >> order;
		if (strcmp(order, "run") == 0)
		{
			if (address[1][0] == '\0')
			{
				cout << "   错误：缺少input文件地址" << endl;
				cout << "   需要更多帮助请输入help" << endl;
			}
			else
			{
				for (int i = 2; i < 5; i++)
				{
					if (address[i][0] == '\0') address_copy(address[i], address[1], i - 1);
				}
				run_fun();
				cout << "   运行结束" << endl;
				return 0;
			}
		}
		else if (strcmp(order, "help") == 0)
		{
			cout << "   *:\\****\\input.txt：输入input文件地址" << endl;
			cout << "   *:\\****\\outputi.txt：输入output文件地址，i=1,2,3，若不给出默认为input文件目录" << endl;
			cout << "   run：运行程序" << endl;
			cout << "   view：查看文件地址" << endl;
			cout << "   end：中止程序" << endl;
		}
		else if (strcmp(order, "view") == 0)
		{
			if (address[1][0] == '\0') cout << "   input:缺失" << endl;
			else cout << "   input:" << address[1] << endl;
			for (int i = 2; i < 5; i++)
			{
				if (address[i][0] == '\0') cout << "   output" << i - 1 << ":当前目录" << endl;
				else cout << "   output" << i - 1 << ":" << address[i] << endl;
			}
		}
		else if (strcmp(order, "end") == 0)
		{
			cout << "   运行终止" << endl;
			return 0;
		}
		else if (strstr(order, "input") != NULL)
		{
			address_change(address[1], order);
			for (int i = 2; i < 5; i++)
			{
				if (address[i][0] == '\0')
				{
					address_copy(address[i], address[1], i - 1);
				}
			}
			cout << "   已获取input地址，程序可运行" << endl;
		}
		else if (strstr(order, "output") != NULL)
		{
			out_change(order);
			cout << "   output地址已存储" << endl;
			if (address[1][0] == '\0') cout << "   警告：缺少input文件地址" << endl;
		}
		else
		{
			cout << "   错误：非法输入" << endl;
			cout << "   需要更多帮助请输入help" << endl;
		}
	}
	return 0;
}

void run_fun(void)
{
	ofstream f1(address[2], ios::trunc);
	ofstream f2(address[3], ios::trunc);
	ofstream f3(address[4], ios::trunc);
	f1.close();
	f2.close();
	f3.close();
	fin.open(address[1]);
	fin >> n;
	ask_num = n;
	for (int i = 0; i < n; i++)
	{
		fin >> info[i].time >> info[i].floor >> info[i].des;
	}
	fin.close();
	while (ask_num != 0)
	{   //构建队列 
		for (int i = fi + 1; i < n; i++)//迫于时间无算法的垃圾调度
		{
			if (ele.get_time() == info[i].time)
			{
				fi_p = i;
				if ((info[i].floor % 2) == 0)//起始层是偶数
				{
					if ((info[i].des % 2) == 0) ele_even.cre(i, info[i].floor, info[i].des);//目的层也是偶数
					else if (info[i].des == 1) ele_even.cre(i, info[i].floor, info[i].des);//目的层为1
					else ele.cre(i, info[i].floor, info[i].des);//目的层为奇数
				}
				else//起始层为奇数
				{
					if ((info[i].des % 2) == 0) ele.cre(i, info[i].floor, info[i].des);//目的层为偶数
					else ele_odd.cre(i, info[i].floor, info[i].des);//目的层为奇数
				}
			}
		}
		if (fi_p != 0) fi = fi_p;//the new bug
		ele.sorting();
		ele_odd.sorting();
		ele_even.sorting();
		//电梯运行
		running->run(info, ask_num, n, ele_a, address[3]);
		running = &ele_odd;
		running->run(info, ask_num, n, ele_odd_a, address[2]);
		running = &ele_even;
		running->run(info, ask_num, n, ele_even_a, address[4]);
		running = &ele;
	}
}

void address_change(char* aft, char* bef)
{
	int len = strlen(bef);
	int fl(0);
	for (int i = 0; i < len; i++)
	{
		if (bef[i] != '\\') aft[fl++] = bef[i];
		else
		{
			aft[fl++] = '\\';
			aft[fl++] = '\\';
		}
	}
}

void address_copy(char* aft, char* bef,int num)
{
	int len = strlen(bef);
	int i;
	for (i = 0; i < (len - 9); i++) aft[i] = bef[i];
	aft[i++] = 'o';
	aft[i++] = 'u';
	aft[i++] = 't';
	aft[i++] = 'p';
	aft[i++] = 'u';
	aft[i++] = 't';
	aft[i++] = (num + 48);
	aft[i++] = '.';
	aft[i++] = 't';
	aft[i++] = 'x';
	aft[i++] = 't';
}

void out_change(char* str)
{
	if (strstr(str, "output1") != NULL) address_change(address[2], str);
	else if (strstr(str, "output2") != NULL) address_change(address[3], str);
	else if (strstr(str, "output3") != NULL) address_change(address[4], str);
}