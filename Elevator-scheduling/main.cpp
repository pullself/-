#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "elevator.h"
#include "ask.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
ask info[100];//����������� 
elevator ele;//һ�����ݶ��� 
int main() 
{
	int n,ask_num,m = 0,a = 0;//m->�Ѵ����������
    int x,y,z;  
	cin>>n;
	if(n>100) 
	{
		cout<<"error:Ask too much,be busy"<<endl;
	    return 0;
    }
	ask_num=n;
	for(int i = 0; i < n;i ++)
	{
		cin >> x >> y >> z;
		info[i].time = x+1;
		info[i].floor = y+1;
		info[i].des = z+1;
	} 
	while(ask_num)
	{   //�������� 
		for(int i = 0; i < n; i ++)
		{
			if(ele.get_time() == info[i].time)
				ele.cre(i,info[i].floor,info[i].des);
		}
        ele.sorting();
        //��������
        ele.run(info,n,ask_num,a);
    }
    system("pause");
	return 0;
}
