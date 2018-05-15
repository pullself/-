#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include "elevator.h"
using namespace std;
ofstream fout;
elevator::elevator()
{
	time = 0;
	pos = 1;
	num = 0;
    sta = 0;
    pu.left = pu.right = pd.left = pd.right = pu_p.left = pu_p.right = pd_p.left = pd_p.right = 0;
}

bool cmpu(const queue &a,const queue &b)
{
	return a.floor < b.floor;
}

bool cmpd(const queue &a,const queue &b)
{
	return a.floor > b.floor; 
}

queue::queue()
{
	floor = 0;
	num_in = 0;
	num_out = 0;
}

flag::flag()
{
	left = 0;
	right = 0;
}

int elevator::get_time(void)
{
	return time;
}

int elevator::get_sta(void)
{
	return sta;
}

void elevator::sorting()
{
	sort(up+pu.left,up+pu.right,cmpu);
	sort(down+pd.left,down+pd.right,cmpd);
}

void elevator::cre_queue(int i,bool flag,int a,int b)/*a->info[i].floor,b->info[i].des*/
{                                                     
	int m=0,n=0;
	if(flag == true)//若是上行 
	{
		if(a >= pos)//如果请求的初始楼层在当前位置之上 
		{
			for(int j = pu.left ; j < pu.right ; j++)//bug1
			{
				if(a == up[j].floor)
				{
					up[j].num_in ++;
					up[j].in[i] ++;
					m=1;
				}
				if(b == up[j].floor)
				{
					up[j].num_out ++;
					up[j].out[i] ++;
					n=1;
 				}
 		    }
			if(m == 0)
			{
				up[pu.right].floor = a;
			    up[pu.right].num_in++;
			    up[pu.right++].in[i]++;
			}
			if(n == 0)
			{
				up[pu.right].floor = b;
			    up[pu.right].num_out++;
			    up[pu.right++].out[i]++;
			} 
		}
		if(a < pos)//如果请求小于当前位置，暂存
		{
			for(int j = pu_p.left ; j < pu_p.right ; j++)//bug1
			{
				if(a == up_p[j].floor)
				{
					up_p[j].num_in ++;
					up_p[j].in[i] ++;
					m=1;
				}
				if(b == up_p[j].floor)
				{
					up_p[j].num_out ++;
					up_p[j].out[i] ++;
					n=1;
 				}
 		    }
			if(m == 0)
			{
				up_p[pu_p.right].floor = a;
			    up_p[pu_p.right].num_in++;
			    up_p[pu_p.right++].in[i]++;
			}
			if(n == 0)
			{
				up_p[pu_p.right].floor = b;
			    up_p[pu_p.right].num_out++;
			    up_p[pu_p.right++].out[i]++;
			} 
		} 
	}
	else
	{
		if(a <= pos)//如果请求的初始楼层在当前位置之下 
		{
			for(int j = pd.left ; j < pd.right ; j++)//bug1
			{
				if(a == down[j].floor)
				{
					down[j].num_in ++;
					down[j].in[i] ++;
					m=1;
				}
				if(b == down[j].floor)
				{
					down[j].num_out ++;
					down[j].out[i] ++;
					n=1;
 				}
 		    }
			if(m == 0)
			{
				down[pd.right].floor = a;
			    down[pd.right].num_in++;
			    down[pd.right++].in[i]++;
			}
			if(n == 0)
			{
				down[pd.right].floor = b;
			    down[pd.right].num_out++;
			    down[pd.right++].out[i]++;
			} 
		}
		if(a > pos)//如果请求大于当前位置，暂存
		{
			for(int j = pd_p.left ; j < pd_p.right ; j++)//bug1
			{
				if(a == down_p[j].floor)
				{
					down_p[j].num_in ++;
					down_p[j].in[i] ++;
					m=1;
				}
				if(b == down_p[j].floor)
				{
					down_p[j].num_out ++;
					down_p[j].out[i] ++;
					n=1;
 				}
 		    }
			if(m == 0)
			{
				down_p[pd_p.right].floor = a;
			    down_p[pd_p.right].num_in++;
			    down_p[pd_p.right++].in[i]++;
			}
			if(n == 0)
			{
				down_p[pd_p.right].floor = b;
			    down_p[pd_p.right].num_out++;
			    down_p[pd_p.right++].out[i]++;
			} 
		} 
	} 
}

void elevator::cre_queue2(int i,bool flag,int a,int b)/*a->info[i].floor,b->info[i].des*/
{
	int m = 0,n = 0;
	if(flag == true)
	{
	    for(int j = pu.left ; j < pu.right ; j++)//bug1
		{
			if(a == up[j].floor)
			{
				up[j].num_in ++;
				up[j].in[i] ++;
				m=1;
			}
			if(b == up[j].floor)
			{
				up[j].num_out ++;
				up[j].out[i] ++;
				n=1;
 			}
 		}
		if(m == 0)
		{
			up[pu.right].floor = a;
		    up[pu.right].num_in++;
		    up[pu.right++].in[i]++;
		}
		if(n == 0)
		{
			up[pu.right].floor = b;
		    up[pu.right].num_out++;
		    up[pu.right++].out[i]++;
		}
	}
	else
	{
		for(int j = pd.left ; j < pd.right ; j++)//bug1
		{
			if(a == down[j].floor)
			{
				down[j].num_in ++;
				down[j].in[i] ++;
				m = 1;
			}
			if(b == down[j].floor)
			{
				down[j].num_out ++;
				down[j].out[i] ++;
				n = 1;
			}
 		}
		if(m == 0)
		{
			down[pd.right].floor = a;
		    down[pd.right].num_in++;
		    down[pd.right++].in[i]++;
		}
		if(n == 0)
		{
			down[pd.right].floor = b;
		    down[pd.right].num_out++;
		    down[pd.right++].out[i]++;
		} 
	}
} 

void elevator::cre(int i,int a,int b)//a->info[i].floor,b->info[i].des
{
	if(sta == 0)
	{
		if((b-a) > 0) cre_queue(i,true,a,b);
		else cre_queue2(i,false,a,b);
	}
	else
	{
		if((b-a) < 0)  cre_queue(i,false,a,b);
		else cre_queue2(i,true,a,b);
	}
}

void elevator::run(ask (&arr)[500],int &ask_num,int &n,int &a)
{ 
	if((up[pu.left].floor == 0) && (down[pd.left].floor == 0))//bug2
	{
	    time ++;
	}
	else
	{
		if(sta == 0)//电梯模式为上行 
		{
			if(up[pu.left].floor == 0)
			{
			    a = up[pu.left-1].floor;//记录最后一个位置的楼层 
				sta = 1;//电梯模式变为下行 
				pu.left = 0;
				pu.right = pu_p.right;
				for(int k = 0 ; k < (n*2) ; k++)
				{
				    up[k] = up_p[k];
				}
				memset(up_p,0,sizeof(queue)*200);//初始化暂存队列 
				pu_p.left = 0;
				pu_p.right = 0;
			} 
			else
			{
				if(pos < up[pu.left].floor)
			    {
				    time ++;
				    pos ++;
				    a = 0;
			    }
			    else//bug3
			    {
			        if(pos == up[pu.left].floor)//输出与计算处理 
			        {
			            num = num + up[pu.left].num_in - up[pu.left].num_out;
			            for(int k = 0 ; k < n ; k++)
		                {
					        if(up[pu.left].in[k] == 1) arr[k].sta = 1;
					        if(up[pu.left].out[k] == 1) 
					        {
						        arr[k].sta = 2;
						        ask_num --;
						        //waitingtime += (ele.time - info[k].time);
					        }
				        }
				        if(a != up[pu.left].floor)//若另一队列最后元素与此队列元素相同不反复停靠 
				        {   
							if (time != arr[0].time)
							{
								fout.open("output2.txt", ios::app);
								fout << time << " " << pos << endl;
								fout.close();
							}
				            time ++;
						}
				        pu.left ++;//队列头向后移动 
			        }
			        else
					{
						if(pos > up[pu.left].floor)//如果一开始的上行队列中的还在电梯位置之下，将会向下移动去接 
			            {
				            time ++;
				            pos --;
				            a = 0;
			            }
					}
				} 
			} 
		}
		if (sta == 1)//电梯模式为下行
		{
			if(down[pd.left].floor == 0)
			{
			    a = down[pd.left-1].floor;
			    sta = 0;//电梯模式变为上行 
			    pd.left = 0;
			    pd.right = pd_p.right;
			    for(int k = 0 ; k < n*2 ; k++)
			    {
		    		down[k] = down_p[k];
		    	}
			    memset(down_p,0,sizeof(queue)*200);//初始化暂存队列 
		    	pd_p.left = 0;
		    	pd_p.right = 0;
		    } 
		    else
		    {
		    	if(pos > down[pd.left].floor)
		    	{
			    	time ++;
			    	pos --;
			    	a = 0;
			    }
			    else
			    {
			        if(pos == down[pd.left].floor)//输出与计算处理 
			        {
			    	    num = num + down[pd.left].num_in - down[pd.left].num_out;
				    	for(int k = 0 ; k < n ; k++)
				    	{
				    		if(down[pd.left].in[k] == 1) arr[k].sta = 1;
				    		if(down[pd.left].out[k] == 1) 
			    			{
			    				arr[k].sta = 2;
			    				ask_num --;
			    				//waitingtime += (ele.time - info[k].time);
			    			}
			    	   	}
			    	   	if(a != down[pd.left].floor)//bug4
			    	   	{
							if (time != arr[0].time && pos!=1)
							{
								fout.open("output2.txt", ios::app);
								fout << time << " " << pos << endl;
								fout.close();
							}
			    	    	time ++;
						}
			    	    pd.left ++;//队列头向后移动 
		    	    }
		    	    else
		    	    {
		    	    	if(pos < down[pd.left].floor)//如果一开始的上行队列中的还在电梯位置之上，将会向上移动去接 
		    	    	{
		    		        time ++;
		    		        pos ++;
		    		        a = 0;
		    	    	}
					}	
				}
		    } 
	    }
	}
} 

void elevator_odd::run(ask(&arr)[500], int &ask_num, int &n, int &a)
{
	if ((up[pu.left].floor == 0) && (down[pd.left].floor == 0))//bug2
	{
		time++;
	}
	else
	{
		if (sta == 0)//电梯模式为上行 
		{
			if (up[pu.left].floor == 0)
			{
				a = up[pu.left - 1].floor;//记录最后一个位置的楼层 
				sta = 1;//电梯模式变为下行 
				pu.left = 0;
				pu.right = pu_p.right;
				for (int k = 0; k < (n * 2); k++)
				{
					up[k] = up_p[k];
				}
				memset(up_p, 0, sizeof(queue) * 200);//初始化暂存队列 
				pu_p.left = 0;
				pu_p.right = 0;
			}
			else
			{
				if (pos < up[pu.left].floor)
				{
					time++;
					pos++;
					a = 0;
				}
				else//bug3
				{
					if (pos == up[pu.left].floor)//输出与计算处理 
					{
						num = num + up[pu.left].num_in - up[pu.left].num_out;
						for (int k = 0; k < n; k++)
						{
							if (up[pu.left].in[k] == 1) arr[k].sta = 1;
							if (up[pu.left].out[k] == 1)
							{
								arr[k].sta = 2;
								ask_num--;
								//waitingtime += (ele.time - info[k].time);
							}
						}
						if (a != up[pu.left].floor)//若另一队列最后元素与此队列元素相同不反复停靠 
						{
							if (time != arr[0].time)
							{
								fout.open("output1.txt", ios::app);
								fout << time << " " << pos << endl;
								fout.close();
							}
							time++;
						}
						pu.left++;//队列头向后移动 
					}
					else
					{
						if (pos > up[pu.left].floor)//如果一开始的上行队列中的还在电梯位置之下，将会向下移动去接 
						{
							time++;
							pos--;
							a = 0;
						}
					}
				}
			}
		}
		if (sta == 1)//电梯模式为下行
		{
			if (down[pd.left].floor == 0)
			{
				a = down[pd.left - 1].floor;
				sta = 0;//电梯模式变为上行 
				pd.left = 0;
				pd.right = pd_p.right;
				for (int k = 0; k < n * 2; k++)
				{
					down[k] = down_p[k];
				}
				memset(down_p, 0, sizeof(queue) * 200);//初始化暂存队列 
				pd_p.left = 0;
				pd_p.right = 0;
			}
			else
			{
				if (pos > down[pd.left].floor)
				{
					time++;
					pos--;
					a = 0;
				}
				else
				{
					if (pos == down[pd.left].floor)//输出与计算处理 
					{
						num = num + down[pd.left].num_in - down[pd.left].num_out;
						for (int k = 0; k < n; k++)
						{
							if (down[pd.left].in[k] == 1) arr[k].sta = 1;
							if (down[pd.left].out[k] == 1)
							{
								arr[k].sta = 2;
								ask_num--;
								//waitingtime += (ele.time - info[k].time);
							}
						}
						if (a != down[pd.left].floor)//bug4
						{
							if (time != arr[0].time)
							{
								fout.open("output1.txt", ios::app);
								fout << time << " " << pos << endl;
								fout.close();
							}
							time++;
						}
						pd.left++;//队列头向后移动 
					}
					else
					{
						if (pos < down[pd.left].floor)//如果一开始的上行队列中的还在电梯位置之上，将会向上移动去接 
						{
							time++;
							pos++;
							a = 0;
						}
					}
				}
			}
		}
	}
}

void elevator_even::run(ask(&arr)[500], int &ask_num, int &n, int &a)
{
	if ((up[pu.left].floor == 0) && (down[pd.left].floor == 0))//bug2
	{
		time++;
	}
	else
	{
		if (sta == 0)//电梯模式为上行 
		{
			if (up[pu.left].floor == 0)
			{
				a = up[pu.left - 1].floor;//记录最后一个位置的楼层 
				sta = 1;//电梯模式变为下行 
				pu.left = 0;
				pu.right = pu_p.right;
				for (int k = 0; k < (n * 2); k++)
				{
					up[k] = up_p[k];
				}
				memset(up_p, 0, sizeof(queue) * 200);//初始化暂存队列 
				pu_p.left = 0;
				pu_p.right = 0;
			}
			else
			{
				if (pos < up[pu.left].floor)
				{
					time++;
					pos++;
					a = 0;
				}
				else//bug3
				{
					if (pos == up[pu.left].floor)//输出与计算处理 
					{
						num = num + up[pu.left].num_in - up[pu.left].num_out;
						for (int k = 0; k < n; k++)
						{
							if (up[pu.left].in[k] == 1) arr[k].sta = 1;
							if (up[pu.left].out[k] == 1)
							{
								arr[k].sta = 2;
								ask_num--;
								//waitingtime += (ele.time - info[k].time);
							}
						}
						if (a != up[pu.left].floor)//若另一队列最后元素与此队列元素相同不反复停靠 
						{
							if (time != arr[0].time)
							{
								fout.open("output3.txt", ios::app);
								fout << time << " " << pos << endl;
								fout.close();
							}
							time++;
						}
						pu.left++;//队列头向后移动 
					}
					else
					{
						if (pos > up[pu.left].floor)//如果一开始的上行队列中的还在电梯位置之下，将会向下移动去接 
						{
							time++;
							pos--;
							a = 0;
						}
					}
				}
			}
		}
		if (sta == 1)//电梯模式为下行
		{
			if (down[pd.left].floor == 0)
			{
				a = down[pd.left - 1].floor;
				sta = 0;//电梯模式变为上行 
				pd.left = 0;
				pd.right = pd_p.right;
				for (int k = 0; k < n * 2; k++)
				{
					down[k] = down_p[k];
				}
				memset(down_p, 0, sizeof(queue) * 200);//初始化暂存队列 
				pd_p.left = 0;
				pd_p.right = 0;
			}
			else
			{
				if (pos > down[pd.left].floor)
				{
					time++;
					pos--;
					a = 0;
				}
				else
				{
					if (pos == down[pd.left].floor)//输出与计算处理 
					{
						num = num + down[pd.left].num_in - down[pd.left].num_out;
						for (int k = 0; k < n; k++)
						{
							if (down[pd.left].in[k] == 1) arr[k].sta = 1;
							if (down[pd.left].out[k] == 1)
							{
								arr[k].sta = 2;
								ask_num--;
								//waitingtime += (ele.time - info[k].time);
							}
						}
						if (a != down[pd.left].floor)//bug4
						{
							if (time != arr[0].time)
							{
								fout.open("output3.txt", ios::app);
								fout << time << " " << pos << endl;
								fout.close();
							}
							time++;
						}
						pd.left++;//队列头向后移动 
					}
					else
					{
						if (pos < down[pd.left].floor)//如果一开始的上行队列中的还在电梯位置之上，将会向上移动去接 
						{
							time++;
							pos++;
							a = 0;
						}
					}
				}
			}
		}
	}
}