#ifndef __ELEVATOR_H__
#define __ELEVATOR_H__
#include "ask.h"
using namespace std;
/*下一步计划将电梯类中的运行方法独立为一个运行类，与电梯类为友元关系*/

class queue//队列类
{
public:
	int floor;//楼层
	int num_in;//进人数
	int num_out;//出人数
	int in[500];//进具体列
	int out[500];//出具体列
	queue();
};

class flag//标记类
{
public:
	int left;//队头
	int right;//对尾
	flag();
};

class elevator//基础电梯类
{
protected:
	int time;//运行时间
	int pos;//电梯位置
	int num;//电梯内人数；
	int sta;//电梯运行状态
	int weight;//电梯核载重
	queue up[1000],down[1000],up_p[1000],down_p[1000];
	flag pu,pd,pu_p,pd_p;
private:
	void cre_queue(int i,bool flag,int a,int b);
	void cre_queue2(int i,bool flag,int a,int b);
public: 
	elevator();
	int get_time(void);
	int get_sta(void);
	void sorting(void);
	void cre(int i,int a,int b);
	virtual void run(ask (&arr)[500],int &ask_num,int &n,int &a);
}; 

class elevator_odd :public elevator//奇数电梯类
{
public:
	virtual void run(ask(&arr)[500], int &ask_num, int &n, int &a);
};

class elevator_even :public elevator//偶数电梯类
{
public:
	virtual void run(ask(&arr)[500], int &ask_num, int &n, int &a);
};
#endif
