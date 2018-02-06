#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
struct node
{
	int time;
	int floor;
	int dest;
    int flag;
    node()
    {
    	memset(this,0,sizeof(node));
	}
}ask[10];
struct nod
{
	int time;
	int num_10;
	int num_1;
	int pos;
	nod()
	{
		time=-1;
		num_10=0;
		num_1=0;
		pos=1;
	}
}ele;
struct nok
{
	int time;
	int pos;
	nok()
	{
		memset(this,0,sizeof(nok));
	}
}dect[15],de[15];
int ask_num=5,amin=1000000,wait=0,ans,u=0,x;
void dfs()
{
	ele.time++;
	if((!ele.num_10)&&(!ask_num)&&(!ele.num_1))//边界：电梯内没人并且所有请求已应答。 
	{
		//cout<<wait<<" "<<ele.time<<endl;
		if(wait<amin)
		{
			amin=wait;
			ans=ele.time;
			for(int k=0;k<15;k++)//初始化 
			{
				dect[k].pos=0;
				dect[k].time=0;
			}
			for(int j=0;j<15;j++)
			{
				dect[j].pos=de[j].pos;
				dect[j].time=de[j].time;
			}
			return;
		}
		return;
	}
	else
	{
		for(int i=0;i<7;i++)
		{
			if((i!=5)&&(i!=6)&&(ask[i].flag==0))
			{
				int t,l,flag=0;
				ask_num--;//请求数量更新 
				ask[i].flag=1;//人状态更新
				if(ask[i].floor==ele.pos)//同时进多个人的数据处理 
				{
					ele.time--;
					flag=1;
				}
				if(ask[i].dest==0) ele.num_10++;//人进入电梯 
				else ele.num_1++;
				if((ele.time+abs(ele.pos-ask[i].floor))>=ask[i].time)//运行时间大于等于这次请求的的时候的电梯运行时间增加。 
				{
					t=abs(ele.pos-ask[i].floor);
				    ele.time+=t;
				}
				else
				{
					t=abs(ele.pos-ask[i].floor)+(ask[i].time-(ele.time+abs(ele.pos-ask[i].floor)));
				    ele.time+=t;
				}
				l=ele.pos;
				ele.pos=ask[i].floor;//电梯位置更新 
				de[u].time=ele.time;
				de[u++].pos=ele.pos;
				dfs();//进入下一次移动 
				ele.time--;
				if(flag==1) ele.time++;
				ask_num++;
				if(ask[i].dest==0) ele.num_10--;
				else ele.num_1--; 
				ele.time-=t;//回复
				ask[i].flag=0;
				ele.pos=l;
				de[--u].time=0;
				de[u].pos=0;
			}
			if((i==5)&&(ele.num_1!=0))
			{
				int p,l,t,a[5]={0};
				p=ele.num_1;
				ele.num_1=0;//清空第一层人 
				t=ele.time;
				ele.time+=abs(ele.pos-1);//运行时间增加 
				l=ele.pos;
				ele.pos=1;//电梯位置更新 
				de[u].time=ele.time;
				de[u++].pos=ele.pos;
				for(int j=0;j<5;j++)//等待时间计算 
				{
					if((ask[j].flag==1)&&(ask[j].dest==1))
					{
						ask[j].flag=2;
						a[j]=1;
						wait+=(ele.time-ask[j].time);
					}
				}
				dfs();//进入下一次移动 
				ele.time--;
				ele.num_1=p;
				ele.pos=l;
				for(int j=0;j<5;j++)
				{
					if(a[j]==1) 
					{
						ask[j].flag=1;
						wait-=(ele.time-ask[j].time);
					}
				}
				ele.time=t;
				de[--u].time=0;
				de[u].pos=0;
			}
			if((i==6)&&(ele.num_10!=0))
			{
				int p,l,t,a[5]={0};
				p=ele.num_10;
				ele.num_10=0;
				t=ele.time;
				ele.time+=abs(ele.pos-10);
				l=ele.pos;
				ele.pos=10;
				de[u].time=ele.time;
				de[u++].pos=ele.pos;
				for(int j=0;j<5;j++)
				{
					if((ask[j].flag==1)&&(ask[j].dest==0))
					{
						ask[j].flag=2;
						a[j]=1;
						wait+=abs(ele.time-ask[j].time);
					}
				}
				dfs();
				ele.time--;
				ele.num_10=p;
				ele.pos=l;
				for(int j=0;j<5;j++)
				{
					if(a[j]==1) 
					{
						ask[j].flag=1;
						wait-=(ele.time-ask[j].time);
					}
				}
				ele.time=t;
				de[--u].time=0;
				de[u].pos=0;
			}
		}
	} 
}
int main() 
{
	for(int i=0;i<5;i++)
	{
		cin>>ask[i].time>>ask[i].floor>>ask[i].dest;
	}
	dfs();
	for(int l=0;l<15;l++)//输出队列整理 
	{
		for(int k=l+1;k<15;k++)
		{
			if(dect[l].time==dect[k].time) dect[k].pos=0;
		}
	}
	for(int j=0;j<15;j++)
	{
		if(dect[j].pos!=0)  cout<<dect[j].time<<"时，停靠在"<<dect[j].pos<<"楼"<<endl; 
	}
	cout<<amin;
}
