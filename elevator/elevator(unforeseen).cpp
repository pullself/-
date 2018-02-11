#include<cstdio>
#include<iostream>
#include<cmath> 
using namespace std;

struct setinfo{
	int asktime;
	int startfloor;
	int destination;
	int status;
};

struct seteleStat{
	int direction;
	int position;
	int timeworked;
	int arp;// Amount of Requestions for Picking up
	int requestion[5];
	int waitingtime;
};

struct setstimulation{
	int pos1or10[6];
	int sollutioncount;
	int sollution[17];
	int sollutionstorage[17];
	int sollutionmin[17];
	int minwaitingtime;
};

struct setinfo info[5] = {{0}};
struct seteleStat eleStat = {0};
struct setstimulation stimulation = {0};
 
void sorting0(int m);//全排列可执行请求 
void sorting1(int n);//在全排列中插空组成搜索全排列 
void caltime(void);//搜索中计算时间与请求状态更新 
void mintime(void);//记录最短值和策列 
int enter(void);// 判断有没有其他人计算， 
int exit0(void);//判断有没有人出去等待时间的计算 
int end(void);//判断所有人是不是都被扔出去了 
void sortrequest(void);//排序搜索序列 
void swap(int *a, int *b);

int main(void){
	int i = 0;
	int j = 0;
	int time0 = -1;
	int booleanew = 0;
	eleStat.position = 1;
	
	for(i = 0; i < 5; i++){
		cin>>info[i].asktime>>info[i].startfloor>>info[i].destination;
	}
	
	while(end() == 0){
		for(i = 0; i < 5; i++){
			if(info[i].asktime <= eleStat.timeworked && info[i].asktime > time0){
				eleStat.requestion[eleStat.arp] = info[i].startfloor;
				eleStat.arp ++;
				booleanew = 1;
			}
		}
		time0 = eleStat.timeworked;
		
		if(booleanew == 1){
			sortrequest();
			for(i = eleStat.arp - 1; i > 0; i--){
				if(eleStat.requestion[i] == eleStat.requestion[i - 1]){
					for(j = i; j < eleStat.arp - 1; j++){
						eleStat.requestion[j] = eleStat.requestion[j + 1];
					}
					eleStat.requestion[eleStat.arp - 1] = 0;
					eleStat.arp --;
				}
			}
			stimulation.minwaitingtime = 10000;
			sorting0(0);
			booleanew = 0;
			for(i = 0; i < 17; i++){
				stimulation.sollution[i] = stimulation.sollutionmin[i];
			}
		}
		
		if(eleStat.position != stimulation.sollution[0]){
			if(stimulation.sollution[0] == 0){
				eleStat.direction = 0;
			}
			else if(stimulation.sollution[0] > eleStat.position){
				eleStat.direction  = 1;
			}
			else{
				eleStat.direction = -1;
			}
			
			eleStat.position += eleStat.direction;
			eleStat.timeworked ++;
		}
		
		if(enter() + exit0() != 0){
			cout<<eleStat.timeworked<<"时，停靠在"<<eleStat.position<<"楼"<<endl;
			eleStat.timeworked ++;	
		}
		
		if(eleStat.position == stimulation.sollution[0]){
			for(i = 0; i < 16; i++){
				stimulation.sollution[i] = stimulation.sollution[i + 1];
			}
			stimulation.sollution[16] = 0;
		}
	}
	
	cout<<eleStat.waitingtime;
	
	return 0;
}


void sorting0(int m){
	int i = 0;
	
	if(m + 1 != eleStat.arp){
		for(i = m; i < eleStat.arp; i++){
			swap(&eleStat.requestion[i], &eleStat.requestion[m]);
			sorting0(m + 1);
			swap(&eleStat.requestion[i], &eleStat.requestion[m]);
		}
	}
	else{
		sorting1(0);
	}
}


void sorting1(int n){
	int i = 0;
	int j = 0;
	
	if(n != eleStat.arp + 1){
		for(i = 0; i < 5; i++){
			stimulation.pos1or10[n] = i;
			if( (n < eleStat.arp && ( ( eleStat.requestion[n] == 1 && ( i == 1 || i == 4 ) ) || ( eleStat.requestion[n] == 10 && ( i == 2 || i == 3 ) ) ) ) || ( n > 0 && ( ( eleStat.requestion[n - 1] == 1 && ( i == 1 || i == 3 ) ) || eleStat.requestion[n - 1] == 10 && ( i == 2 || i == 4 ) ) ) ){
				continue;
			}
			sorting1(n + 1);
		}
	}
	else{
		for(i = 0; i < stimulation.sollutioncount; i++){
			stimulation.sollution[i] = 0;
		}
		stimulation.sollutioncount = 0;
		for(i = 0; i < 2 * eleStat.arp + 1; i++){
			if(i % 2 == 0){
				switch(stimulation.pos1or10[i / 2]){
					case 1:
						stimulation.sollution[stimulation.sollutioncount] = 1;
						stimulation.sollutioncount ++;
						break;
					case 2:
						stimulation.sollution[stimulation.sollutioncount] = 10;
						stimulation.sollutioncount ++;
						break;
					case 3:
						stimulation.sollution[stimulation.sollutioncount] = 1;
						stimulation.sollutioncount ++;
						stimulation.sollution[stimulation.sollutioncount] = 10;
						stimulation.sollutioncount ++;
						break;
					case 4:
						stimulation.sollution[stimulation.sollutioncount] = 10;
						stimulation.sollutioncount ++;
						stimulation.sollution[stimulation.sollutioncount] = 1;
						stimulation.sollutioncount ++;
						break;
				}
			}
			else{
				stimulation.sollution[stimulation.sollutioncount] = eleStat.requestion[(i - 1) / 2];
				stimulation.sollutioncount ++;
			}
		}
		caltime();
	}
}


void caltime(void){
	struct seteleStat aeleStat = {0};
	struct setinfo ainfo[5] = {{0}};
	int i = 0;
	aeleStat = eleStat;
	
	for(i = 0; i < 5; i++){
		ainfo[i] = info[i];
		
		if(info[i].asktime > eleStat.timeworked){
			info[i].status = 2;
		}
	}
	
	for(i = 0; i < 17; i++){
		stimulation.sollutionstorage[i] = stimulation.sollution[i];
	}
	
	while(stimulation.sollutioncount != 0){
		eleStat.timeworked += abs(eleStat.position - stimulation.sollution[0]);
		eleStat.position = stimulation.sollution[0];
		
		if(enter() + exit0() != 0){
			eleStat.timeworked ++;
		}
		
		for(i = 0; i < 16; i++){
			stimulation.sollution[i] = stimulation.sollution[i + 1];
		}
		
		stimulation.sollution[16] = 0;
		stimulation.sollutioncount --;
	}
	
	if(end() == 1){
		mintime();
	}
	
	eleStat = aeleStat;
	for(i = 0; i < 5; i++){
		info[i] = ainfo[i];
	}
}


void mintime(void){
	int i = 0;
	
	if(eleStat.waitingtime < stimulation.minwaitingtime){
		stimulation.minwaitingtime = eleStat.waitingtime;
		for(i = 0; i < 17; i++){
			stimulation.sollutionmin[i] = stimulation.sollutionstorage[i];
		}
	}
}


void swap(int *a, int *b){
	int t = *a;
	
	*a = *b;
	*b = t;
}


void sortrequest(void){
	int i = 0;
	int j = 0;
	
	for(i = eleStat.arp; i > 0; i--){
		for(j = i; j > 0; j--){
			if(eleStat.requestion[j - 1] < eleStat.requestion[j]){
				swap(&eleStat.requestion[j - 1], &eleStat.requestion[j]);////////////////////////////////////////Is "&" required?
			}
		}
	}
}


int enter(void){
	int i = 0;
	int j = 0;
	int boolean = 0;
	
	for(i = 0; i < 5; i++){
		if(stimulation.sollution[0] == eleStat.position && eleStat.position == info[i].startfloor && eleStat.timeworked >= info[i].asktime && info[i].status == 0){
			info[i].status = 1;
			boolean = 1;
		}
		
		if(eleStat.requestion[i] == eleStat.position && eleStat.position == stimulation.sollution[0]){
			for(j = i; j < eleStat.arp - 1; j++){
				eleStat.requestion[j] = eleStat.requestion[j + 1];
			}
			eleStat.requestion[eleStat.arp - 1] = 0;
			eleStat.arp --;
		}
	}
	
	return boolean;
}


int exit0(void){
	int i = 0;
	int x = 0;
	int boolean = 0;
	
	if(eleStat.position == 1){
		x = 1;
	}
	for(i = 0; i < 5 && (eleStat.position == 1 || eleStat.position == 10); i++){
		if(info[i].status == 1 && info[i].destination == x){
			info[i].status = 2;
			eleStat.waitingtime += eleStat.timeworked - info[i].asktime;
			boolean = 1;
		}
	}
	
	return boolean;
}


int end(){
	int i = 0;
	int boolean = 1;
	
	for(i = 0; i < 5; i++){
		if(info[i].status != 2){
			boolean = 0;
			break;
		}
	}
	
	return boolean;
}

