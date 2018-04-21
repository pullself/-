#ifndef __ELEVATOR_H__
#define __ELEVATOR_H__
#include "ask.h"
struct queue 
{
	int floor;
	int num_in;
	int num_out;
	int in[100];
	int out[100];
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
		struct queue up[200],down[200],up_p[200],down_p[200];
		struct flag pu,pd,pu_p,pd_p;
		void cre_queue(int i,bool flag,int a,int b);
		void cre_queue2(int i,bool flag,int a,int b);
	public: 
	    elevator();
	    int get_time(void); 
	    void sorting();
	    void cre(int i,int a,int b);
        void run(ask (&arr)[100],int &ask_num,int &a,int &n);
}; 
#endif
