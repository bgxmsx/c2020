#include<cstdio> 
#include<iostream>
using namespace std;
const int N=3;
int step=0; 
void move(char from,char to)
{
	printf("step %d: %c -> %c\n",++step,from,to);
}
void hanoi(int n,char now,char target,char mid)
{
	if(n==1)
	{
		move(now,target);
		return;
	}
	hanoi(n-1,now,mid,target);
	move(now,target);
	hanoi(n-1,mid,target,now);
}
/*
��now�����ϵĳ�������Բ�̵�n-1��Բ�̽���target���ӣ��Ƶ�mid������ 
Ȼ��now������ʣ�µ��������Բ���ƶ���target������ 
���mid�����ϵ�n-1��Բ���ƶ���target������ 
���n==1����ֻ��Ҫ�����Ӵ�now�����ƶ���target�� 
*/ 
int main()
{
	hanoi(N,'1','3','2');
	return 0;
}
