#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#define up 72
#define down 80
#define left 75
#define right 77
#define blank 0
#define wall 1
#define box 2
#define you 3 
#define goal 4
const int N=31,M=31,maxnum_maps=21;//��ͼ�������+1���������+1����ͼ�������+1
int totmaps=20,nowlevel=1;//�ܹ���ͼ�������ڵĵȼ� 
int nowx,nowy,cnt;//������������λ�ã����������� 
char str[105];//¼���ͼʱ�� 
int map[maxnum_maps][N][M],size[maxnum_maps][2],totgoals[maxnum_maps];//�����ȼ��ĵ�ͼ��ÿ�ŵ�ͼ�ĳߴ� ,ÿ�ŵ�ͼ��Ŀ���� 
int isgoal[maxnum_maps][N][M];//��¼ÿ�ŵ�ͼ����λ���Ƿ���Ŀ��� 
FILE *fp1,*fp2;//��ͼ�ļ����ȼ��ļ� 
void getmap()//�����ͼ 
{
	int nowrow=0;
	while(fgets(str,105,fp1)!=NULL&&strlen(str)>1)
	{
		nowrow++;//++��Ϊ���ڵ����±� 
		int len=strlen(str);len--;//ȥ�����һ��'\n' 
		size[nowlevel][1]=len;
		for(int i=0;i<len;i++)
		{
			switch(str[i])
			{
				case ' ':
					map[nowlevel][nowrow][i+1]=blank;break;
				case '*':
					map[nowlevel][nowrow][i+1]=wall;break;
				case 'G':
					map[nowlevel][nowrow][i+1]=goal;isgoal[nowlevel][nowrow][i+1]=1;totgoals[nowlevel]++;break;//ͬʱ��¼�õ��Ƿ���Ŀ��� 
				case 'B':
					map[nowlevel][nowrow][i+1]=box;break;
				case 'H':
					map[nowlevel][nowrow][i+1]=you;nowx=nowrow;nowy=i+1;break;//ͬʱ��ȡ�˵���ʼλ�� 
				case 'h'://��ʼ�˲���һ��goal��
					map[nowlevel][nowrow][i+1]=you;nowx=nowrow;nowy=i+1;
					isgoal[nowlevel][nowrow][i+1]=1;totgoals[nowlevel]++;
					break;
				case 'b'://��ʼ����ѹ��һ��goal�� 
					map[nowlevel][nowrow][i+1]=box;isgoal[nowlevel][nowrow][i+1]=1;totgoals[nowlevel]++;break;
			}
		}
	}
	size[nowlevel][0]=nowrow;
}
void print()
{
	for(int i=1;i<=size[nowlevel][0];i++)
	{
		for(int j=1;j<=size[nowlevel][1];j++)
		{
			int nowpos=map[nowlevel][i][j];
			if(nowpos==blank) printf("  ");
			else if(nowpos==wall) printf("��");
			else if(nowpos==box) printf("��");
			else if(nowpos==goal) printf("!!");
			else printf("��");
		}
		printf("\n");
	}
	printf("\n��ʹ�÷��������\n��ǰ������%d\n\n�ɼ���\"your socre.txt\"��",cnt);
}
void play_game()
{
	while(nowlevel<=totmaps)//������ڵĵȼ��������ܵ�ͼ��������е�ǰ�ȼ��ĵ�ͼ����Ϸ 
	{
		getmap();//��ȡ��ǰ�ȼ��ĵ�ͼ
		cnt=0;//��ʼ������ 
		print();
		int c1,c2,goalsdown=0;//goalsdown��ʾ��ǰ��ɵ�Ŀ���� 
		while(goalsdown<totgoals[nowlevel])
		{
			c1=getch();c2=getch();
			if(c1!=224&&c2!=224) continue;
			if(c1!=224&&c2==224) c2=getch();//��֤��ʹ�ڰ�����������Ҳ���������� 
			int nextx,nexty;
			switch(c2)
			{
				case up:
					nextx=nowx-1;nexty=nowy;break;
				case down:
					nextx=nowx+1;nexty=nowy;break;
				case left:
					nextx=nowx;nexty=nowy-1;break;
				case right:
					nextx=nowx;nexty=nowy+1;break;
				default:
					continue;
			}
			int nextpos=map[nowlevel][nextx][nexty];
			if(nextpos==wall) continue;//�����ߵ�ǽ��ȥ����Ϊ��ͼ����ǽΧ�����ģ����Բ��õ����ߵ���ͼ����ȥ 
			if(nextpos==box)//���Ҫ��һ������ 
			{
				int nnextx=2*nextx-nowx,nnexty=2*nexty-nowy;
				int nnextpos=map[nowlevel][nnextx][nnexty];//����������ӣ����ӵ�λ��
				if(nnextpos==wall||nnextpos==box) continue;//���ܽ������Ƶ�ǽ�ϻ���һ�������� 
				//�ɹ��Ƴ����� 
				map[nowlevel][nnextx][nnexty]=box;
				if(isgoal[nowlevel][nnextx][nnexty]) goalsdown++;//���������������һ��Ŀ�� ����goalsdown++ 
				if(isgoal[nowlevel][nextx][nexty]) goalsdown--;//���������������һ��Ŀ�꣬��goalsdown-- 
			}
			//�Լ����ƶ� 
			map[nowlevel][nextx][nexty]=you;
			map[nowlevel][nowx][nowy]=isgoal[nowlevel][nowx][nowy]?goal:blank;
			nowx=nextx;nowy=nexty;
			cnt++;
			system("cls");
			print();
		}
		system("cls");
		fprintf(fp2,"level %d���ܲ�����%d\n\n",nowlevel,cnt);
		nowlevel++;
	}
	printf("\nORZ!!\n\n"); 
}
int main()
{
	fp1=fopen("map.txt","r");
	fp2=fopen("your score.txt","w");
	if(fp1==NULL) printf("��ȡ��ͼʧ�ܣ��뽫\"map.txt\"���ڳ��򴦣�Ȼ���������г���");
	else play_game();
	return 0;
}
