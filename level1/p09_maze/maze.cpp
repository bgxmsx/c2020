#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define up 72
#define down 80
#define left 75
#define right 77
const int N=31,M=31;
int n,m,head,tail,nowx=1,nowy=1;
int maze[N][M],vis[N][M];
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct Point{
	int x,y;
}q[2*N*M];
int judge()//��BFS������ɵ��Թ��ܲ����ߵ��յ� 
{
	memset(vis,0,sizeof(vis));
	head=tail=0;
	vis[1][1]=1;
	q[0].x=1;q[0].y=1;
	while(head<=tail)
	{
		struct Point temp=q[head];
		head++;
		for(int i=0;i<4;i++)
		{
			int x=temp.x+dir[i][0],y=temp.y+dir[i][1];
			if(x<1||y<1||x>n||y>m) continue;
			if(maze[x][y]&&!vis[x][y])
			{
				if(x==n&&y==m) return 1;
				q[++tail].x=x;q[tail].y=y;
				vis[x][y]=1;
			}
		}
	}
	return 0;
}
void createMaze(int n,int m)//�������n��m�е��Թ� 
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(rand()%33<13) maze[i][j]=0;
			else maze[i][j]=1;
		}
	maze[1][1]=maze[n][m]=1;
}
void print()//��ӡ�Թ� 
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!maze[i][j]) printf("��");
			else if(i==nowx&&j==nowy) printf("��"); 
			else if(i==n&&j==m) printf("��");
			else printf("  ");
		}
		printf("\n");
	}
}
int main()
{
	srand((unsigned)time(NULL));
	n=m=25;
	do
	{
		createMaze(n,m);
	}while(!judge());
	print();
	int c1,c2;
	while(nowx!=n||nowy!=m)
	{
		c1=getch();c2=getch();
		if(c1!=224&&c2!=224) continue;
		if(c1!=224&&c2==224) c2=getch();//��֤��ʹ�ڰ�����������Ҳ���������� 
		int nextx,nexty;
		switch(c2)
		{
			case up:
				nextx=nowx-1;nexty=nowy;
				break;
			case down:
				nextx=nowx+1;nexty=nowy;
				break;
			case left:
				nextx=nowx;nexty=nowy-1;
				break;
			case right:
				nextx=nowx;nexty=nowy+1;
				break;
			default:
				continue;
		}
		if(nextx<1||nextx>n||nexty<1||nexty>m||!maze[nextx][nexty]) continue;
		nowx=nextx;nowy=nexty;
		system("cls");
		print();
	}
	printf("You win!\n");
	system("pause");
	return 0;
}
