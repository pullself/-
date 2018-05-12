#ifndef __ELEVATOR_H__
#define __ELEVATOR_H__
#include "ask.h"
using namespace std;
/*��һ���ƻ����������е����з�������Ϊһ�������࣬�������Ϊ��Ԫ��ϵ*/

class queue//������
{
public:
	int floor;//¥��
	int num_in;//������
	int num_out;//������
	int in[500];//��������
	int out[500];//��������
	queue();
};

class flag//�����
{
public:
	int left;//��ͷ
	int right;//��β
	flag();
};

class elevator//����������
{
protected:
	int time;//����ʱ��
	int pos;//����λ��
	int num;//������������
	int sta;//��������״̬
	int weight;//���ݺ�����
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

class elevator_odd :public elevator//����������
{
public:
	virtual void run(ask(&arr)[500], int &ask_num, int &n, int &a);
};

class elevator_even :public elevator//ż��������
{
public:
	virtual void run(ask(&arr)[500], int &ask_num, int &n, int &a);
};
#endif
