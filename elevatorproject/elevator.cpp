#include<cstdio>
#include<cmath>
#include<iostream>
#include<fstream> 
using namespace std;

ifstream fin;
ofstream fout;

struct setinfo{
	int asktime;
	int startfloor;
	int destination;
	int status;
};
struct seteleStat{
	int position;
	int direction;
	int timeworked;
	int arp;
	int are;
	int requestion[5];// "5" is required to be changed when wishing a new amount of requestions.
	int reexit[5];// "5" is required to be changed when wishing a new amount of requestions.
	int waitingtime;
	int sollutioncount;
	int sollution[5 * 2];// "5" is required to be changed when wishing a new amount of requestions.
};
struct setstimulation{
	int minwaitingtime;
	int bestsollution[5 * 2];// "5" is required to be changed when wishing a new amount of requestions.
};



const int requestionamount = 5;// "5" is required to be changed when wishing a new amount of requestions.
struct setinfo info[5] = {0};// "5" is required to be changed when wishing a new amount of requestions.
struct seteleStat eleStat = {1};
struct setstimulation stimulation = {0};



void findsollution(int x);
void mintime(void);
void sortrequest(void);
void swap(int *a, int *b);
int enter(int floor);
int exit0(void);
int end(void);




int main(void){
	int i = 0;
	int j = 0;
	int booleanew = 0;
	eleStat.position = 1;
	
	fin.open("input.txt");
	for(i = 0; i < requestionamount; i++){
		fin>>info[i].asktime>>info[i].startfloor>>info[i].destination;
	}
	fin.close();
	fout.open("output.txt");
	while(end() == 0){
		for(i = 0; i < requestionamount; i++){
			if(info[i].asktime == eleStat.timeworked){
				eleStat.requestion[eleStat.arp] = info[i].startfloor;
				eleStat.arp ++;
				booleanew = 1;
			}
		}
		
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
			stimulation.minwaitingtime = 2147000000;
			findsollution(0);
			booleanew = 0;
		}
		
		if(eleStat.position != stimulation.bestsollution[0]){
			if(stimulation.bestsollution[0] == 0){
				eleStat.direction = 0;
			}
			else if(stimulation.bestsollution[0] > eleStat.position){
				eleStat.direction  = 1;
			}
			else{
				eleStat.direction = -1;
			}
			
			eleStat.position += eleStat.direction;
			eleStat.timeworked ++;
			continue;
		}
		
		if(enter(stimulation.bestsollution[0]) + exit0() != 0){
			fout<<eleStat.timeworked<<"Ê±£¬Í£¿¿ÔÚ"<<eleStat.position<<"Â¥"<<endl;
			eleStat.timeworked ++;
		}
		
		if(eleStat.position == stimulation.bestsollution[0]){
			for(i = 0; i < (requestionamount * 2 - 1); i++){
				stimulation.bestsollution[i] = stimulation.bestsollution[i + 1];
			}
			stimulation.bestsollution[requestionamount * 2] = 0;
		}
	}
	
	fout<<eleStat.waitingtime;
	fout.close();
}



void findsollution(int x){
	int i = 0;
	int j = 0;
	int boolean = 1;
	int statusbackup[5] = {0};// "5" is required to be changed when wishing a new amount of requestions.
	struct seteleStat eleStatBackup = {1};
	
	if(x == 0){
		for(i = 0; i < requestionamount; i++){
			if(info[i].asktime > eleStat.timeworked){
				info[i].status = 2;
			}
		}
	}
	
	if(eleStat.arp + eleStat.are != 0){
		for(i = 0; i < eleStat.arp + eleStat.are; i++){
			int floor = 0;
			
			eleStatBackup = eleStat;
			for(j = 0; j < requestionamount; j++){
				statusbackup[j] = info[j].status;
			}
			
			if(i < eleStat.arp){
				floor = eleStat.requestion[i];
			} 
			else{
				floor = eleStat.reexit[i - eleStat.arp];
			}
			
			eleStat.timeworked += abs(eleStat.position - floor);
			eleStat.position = floor;
			eleStat.sollution[eleStat.sollutioncount] = eleStat.position;
			eleStat.sollutioncount ++;
			if(enter(eleStat.sollution[eleStat.sollutioncount - 1]) + exit0() != 0){
				eleStat.timeworked ++;
			}
			findsollution(1);
			
			eleStat = eleStatBackup;
			for(j = 0; j < requestionamount; j++){
				info[j].status = statusbackup[j];
			}
		}
	}
	else{
		if(end() == 1){
			mintime();
		}
	}
	
	if(x == 0){
		for(i = 0; i < requestionamount; i++){
			if(info[i].asktime > eleStat.timeworked){
				info[i].status = 0;
			}
		}
	}
}



int enter(int floor){
	int i = 0;
	int j = 0;
	int boolean = 0;
	int booleanexit = 1;
	
	for(i = 0; i < requestionamount; i++){
		if(floor == eleStat.position && eleStat.position == info[i].startfloor && eleStat.timeworked >= info[i].asktime && info[i].status == 0){
			info[i].status = 1;
			
			booleanexit = 1;
			for(j = 0; j < eleStat.are; j++){
				if(info[i].destination == eleStat.reexit[j]){
					booleanexit = 0;
					break;
				}
			}
			if(booleanexit == 1){
				eleStat.reexit[eleStat.are] = info[i].destination;
				eleStat.are ++;
			}
			
			boolean = 1;
		}
		
		if(eleStat.requestion[i] == eleStat.position && eleStat.position == floor){
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
	int j = 0;
	int boolean = 0;
	
	for(i = 0; i < requestionamount; i++){
		if(info[i].status == 1 && info[i].destination == eleStat.position){
			info[i].status = 2;
			eleStat.waitingtime += eleStat.timeworked - info[i].asktime;
			boolean = 1;
		}
	}
	
	if(boolean == 1){
		for(i = 0; i < eleStat.are; i++){
			if(eleStat.reexit[i] == eleStat.position){
				for(j = i; j < eleStat.are - 1; j++){
					eleStat.reexit[j] = eleStat.reexit[j + 1];
				}
				eleStat.reexit[eleStat.are - 1] = 0;
				eleStat.are --;
				break;
			}
		}
	}
	
	return boolean;
}



void mintime(){
	int i = 0;
	
	if(eleStat.waitingtime < stimulation.minwaitingtime){
		stimulation.minwaitingtime = eleStat.waitingtime;
		
		for(i = 0; i < 10; i++){
			stimulation.bestsollution[i] = eleStat.sollution[i];
		}
	}
}



void sortrequest(void){
	int i = 0;
	int j = 0;
	
	for(i = eleStat.arp; i > 0; i--){
		for(j = i; j > 0; j--){
			if(eleStat.requestion[j - 1] < eleStat.requestion[j]){
				swap(&eleStat.requestion[j - 1], &eleStat.requestion[j]);//Is "&" required?
			}
		}
	}
}



int end(){
	int i = 0;
	int boolean = 1;
	
	for(i = 0; i < requestionamount; i++){
		if(info[i].status != 2){
			boolean = 0;
			break;
		}
	}
	
	return boolean;
}



void swap(int *a, int *b){
	int t = *a;
	
	*a = *b;
	*b = t;
}
