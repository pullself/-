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
	int flag;//0:δ����1����������⣬2�������ڣ�3���ѳ� 
	int mark;
	int fore;
	node()
	{
		memset(this,0,sizeof(node));
	}
}info[10],ask[10];
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
}ele,elep;
struct nok
{
	int time;
	int pos;
	int num_1;
	int num_10;
	nok()
	{
		time=0;
		pos-0;
		num_1=0;
		num_10=0;
	}
}dect[15],de[15],defin[15];
void dfs(int n,int m);//��������
int cre();//�����������캯�� 
void move(int y);//�ƶ����� 
int n=0,l=0,m=0,u=0,amin=100000,x=0,ans=0,ask_num=5,wait=0;//lΪ��ͷ��� 
int main()
{
	bool flag=false;//����״̬�ı��� 
	ele.time=0;
	for(int i=0;i<5;i++)
	{
		cin>>info[i].time>>info[i].floor>>info[i].dest;
	}
	while((ask_num!=0)&&(ele.num_1!=0)&&(ele.num_10!=0))
	{
        if(ask_num!=0) 
        {
        	for(int j=0;j<5;j++)
		    {
			    if(ele.time==info[j].time)//����ʱ���������ʱ���ʱ�� 
			    {
				    info[j].flag=1;
				    flag=true; 
			    }
		    }
		    if(flag)
		    {
		    	m=0;
		    	u=0;
		    	wait=0;
		    	amin=100000;
			    elep=ele;//�ݴ�
			    for(int k=0;k<15;k++)//��ʼ�� 
			    {
				    dect[k].pos=0;
				    dect[k].time=0;
				    dect[k].num_1=0;
				    dect[k].num_10=0;
					defin[k].pos=0;
					defin[k].time=0;
					defin[k].num_1=0;
					defin[k].num_10=0; 
			    }
			    n=cre();
			    dfs(n,n);//������õ�ǰ����
			    for(int l=0;l<15;l++)//�������� 
	            {
		            for(int k=l+1;k<15;k++)
		            {
			            if(dect[l].time==dect[k].time) 
			            {
			            	dect[k].pos=0;
			            	dect[l].num_1+=dect[k].num_1;
			            	dect[l].num_10+=dect[k].num_10;
						}
		            }
	            }
				for(int p=0;p<15;p++)
	            {
		            if(dect[p].pos!=0)  defin[m++]=dect[p];
	            } 
			    flag=false; 
		    }
		}
		move(ele.pos-defin[x].pos);//�ƶ� 
	}
	return 0; 
}
void dfs(int n,int m)
{
	elep.time++;
	if((!elep.num_10)&&(!m)&&(!elep.num_1))//�߽磺������û�˲�������������Ӧ�� 
	{
		if(wait<amin)
		{
			amin=wait;
			for(int k=0;k<15;k++)//��ʼ�� 
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
		for(int i=0;i<n+2;i++)
		{
			if((i!=n)&&(i!=n+1)&&(ask[i].flag==0))
			{
				int t,l,flag=0;
				m--;//������������ 
				ask[i].flag=1;//��״̬����
				if(ask[i].floor==elep.pos)//ͬʱ������˵����ݴ��� 
				{
					elep.time--;
					flag=1;
				}
				if(ask[i].dest==0) elep.num_10++;//�˽������ 
				else elep.num_1++;
				t=abs(elep.pos-ask[i].floor);
				elep.time+=t;
				l=elep.pos;
				elep.pos=ask[i].floor;//����λ�ø��� 
				if(ask[i].dest==1) de[u].num_1++;
				else de[u].num_10++;
				de[u].time=elep.time;
				de[u++].pos=elep.pos;
				dfs(n,m);//������һ���ƶ� 
				elep.time--;
				if(flag==1) elep.time++;
				m++;
				if(ask[i].dest==0) elep.num_10--;
				else elep.num_1--; 
				elep.time-=t;//�ظ�
				ask[i].flag=0;
				elep.pos=l;
				de[--u].time=0;
				de[u].pos=0;
			}
			if((i==n)&&(elep.num_1!=0))
			{
				int p,l,t,a[5]={0},flag=0;
				p=elep.num_1;
				elep.num_1=0;//��յ�һ���� 
				if(ask[i].floor==elep.pos)//ͬʱ������˵����ݴ��� 
				{
					elep.time--;
					flag=1;
				}
				t=elep.time;
				elep.time+=abs(elep.pos-1);//����ʱ������ 
				l=elep.pos;
				elep.pos=1;//����λ�ø��� 
				de[u].time=elep.time;
				de[u++].pos=elep.pos;
				for(int j=0;j<5;j++)//�ȴ�ʱ����� 
				{
					if((ask[j].flag==1)&&(ask[j].dest==1))
					{
						ask[j].flag=2;
						a[j]=1;
						wait+=(elep.time-ask[j].time);
					}
				}
				dfs(n,m);//������һ���ƶ� 
				elep.time--;
				if(flag==1) elep.time++;
				elep.num_1=p;
				elep.pos=l;
				for(int j=0;j<5;j++)
				{
					if(a[j]==1) 
					{
						ask[j].flag=1;
						wait-=(elep.time-ask[j].time);
					}
				}
				elep.time=t;
				de[--u].time=0;
				de[u].pos=0;
			}
			if((i==n+1)&&(elep.num_10!=0))
			{
				int p,l,t,a[5]={0},flag=0;
				p=elep.num_10;
				elep.num_10=0;
				if(ask[i].floor==elep.pos)//ͬʱ������˵����ݴ��� 
				{
					elep.time--;
					flag=1;
				}
				t=elep.time;
				elep.time+=abs(elep.pos-10);
				l=elep.pos;
				elep.pos=10;
				de[u].time=elep.time;
				de[u++].pos=elep.pos;
				for(int j=0;j<5;j++)
				{
					if((ask[j].flag==1)&&(ask[j].dest==0))
					{
						ask[j].flag=2;
						a[j]=1;
						wait+=abs(elep.time-ask[j].time);
					}
				}
				dfs(n,m);
				elep.time--;
				if(flag==1) elep.time++;
				elep.num_10=p;
				elep.pos=l;
				for(int j=0;j<5;j++)
				{
					if(a[j]==1) 
					{
						ask[j].flag=1;
						wait-=(elep.time-ask[j].time);
					}
				}
				elep.time=t;
				de[--u].time=0;
				de[u].pos=0;
			}
		}
	} 
}
int cre()
{
	int n=0;
	memset(ask,0,sizeof(node)*10); 
	for(int i=0;i<5;i++)
	{
		if(info[i].flag==1) 
		{
			ask[n]=info[i];
			ask[n++].mark=i;
		}
	}
	return n;
}
void move(int y)
{
	if(y<0)
	{
		ele.pos++;
		ele.time++;
	}
	if(y==0)
	{
		if(defin[x].pos!=10&&defin[x].pos!=1)
		{
			ele.num_1+=defin[x].num_1;
			ele.num_10+=defin[x].num_10;
			for(int i=0;i<n;i++)
			{
				if(ask[i].floor==defin[x].pos) info[ask[i].mark].flag=2;
			}
			x++;
			ele.time++;
		}
		else
		{
			if(defin[x].pos==1)
			{
			    ele.num_10+=defin[x].num_10;
			    for(int i=0;i<n;i++)
			    {
				if(ask[i].floor==defin[x].pos) info[ask[i].mark].flag=2;
			    }
			    ele.num_1=0;
			    for(int j=0;j<5;j++)//�ȴ�ʱ����� 
				{
					if((info[j].flag==2)&&(info[j].dest==1))
					{
						info[j].flag=3;
						ans+=(ele.time-info[j].time);
					}
				}
				x++;
				ele.time++;
			}
			if(defin[x].pos==10)
			{
			    ele.num_1+=defin[x].num_1;
			    for(int i=0;i<n;i++)
			    {
				if(ask[i].floor==defin[x].pos) info[ask[i].mark].flag=2;
			    }
			    ele.num_10=0;
			    for(int j=0;j<5;j++)//�ȴ�ʱ����� 
				{
					if((info[j].flag==2)&&(info[j].dest==0))
					{
						info[j].flag=3;
						ans+=(ele.time-info[j].time);
					}
				}
				x++;
				ele.time++;
			}
		}
	}
	if(y>0)
	{
		ele.pos--;
		ele.time++;
	}
}
