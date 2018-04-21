#ifndef __ELEVATOR_H__
#define __ELEVATOR_H__
#include "ask.h"
using namespace std; 
struct queue 
{
	int floor;
	int num_in;
	int num_out;
	int in[500];
	int out[500];
};

struct flag
{
	int left;
	int right;
};

class elevator
{
	private:
		int time;//����ʱ��
		int pos;//����λ��
		int num;//������������
		int sta;//��������״̬
		int weight;//���ݺ�����
		struct queue up[1000],down[1000],up_p[1000],down_p[1000];
		struct flag pu,pd,pu_p,pd_p;
		void cre_queue(int i,bool flag,int a,int b);
		void cre_queue2(int i,bool flag,int a,int b);
		void run(ask (&arr)[500],int &ask_num,int &a,const int &n);
	public: 
	    elevator();
	    int get_time(void); 
	    void sorting();
	    void cre(int i,int a,int b);
        void coo(int &ask_num,ask (&arr)[500],int &a,const int &n);
}; 
#endif
