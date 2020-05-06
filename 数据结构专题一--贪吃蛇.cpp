#include<iostream>
#include<cstdio>
#include<cstdlib>										//rand()函数头文件 
#include<ctime>											//clock()函数头文件 
#include<conio.h>										//kbhit()函数头文件 
#include<cmath>											//sqrt()函数头文件 
#include<windows.h>										//移动光标函数头文件 
#define H 20											//地图高 
#define W 60											//地图宽 
using namespace std;

HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void gotoxy(int x,int y)								//移动光标 
{	 
	coord.X=x;											//x坐标 
    coord.Y=y;											//y坐标 
	SetConsoleCursorPosition(handle,coord);
}

void hide()												//隐藏光标 
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(handle, &cursor_info);
}


class Map												//地图 
{
public:
	Map();												//构造函数 
	void Food();										//产生食物 
protected:
	int food_x,food_y;									//食物坐标 
};

Map::Map()												//构造函数---绘制地图 
{
	int i,j;
	for(j=0;j<=W;j++)									//第一行 
	{
		if(j==0||j==W)
			cout<<'+';
		else
			cout<<'-';
	}
	cout<<endl;											//转行 
    for(i=1;i<=H-1;i++)									//第二至倒数第二行 
    {
    	for(j=0;j<=W;j++)
    	{
    		if(j==0||j==W)
    			cout<<'|';
    		else
    			cout<<' ';
		}
		cout<<endl;
	}
    for(j=0;j<=W;j++)									//最后一行 
	{
		if(j==0||j==W)
			cout<<'+';
		else
			cout<<'-';
	}
	cout<<endl;											//转行 
	gotoxy(W+2,H/2+2);
	cout <<"按空格键暂停/继续"; 
    Food();												//产生初始食物 
}

void Map::Food()										//产生食物 
{
	srand(time(0));										//产生随机数种子 
	do
	{
		food_x=rand()%(W-1)+1;							//随机产生食物的x坐标 
		food_y=rand()%(H-1)+1;							//随机产生食物的y坐标 
	}
	while(food_x==0||food_x>=W||food_y==0||food_y>=H);	//循环产生随机食物坐标，直到食物位于地图中 
	gotoxy(food_x,food_y);								//将光标移至坐标处 
	cout<<'$';											//打印食物 
}


struct snakenode										//蛇结点，包含x,y坐标 
{
	int x,y;
};

class Snake:public Map									//蛇 
{
public:
	Snake(int x);										//构造函数 
	bool ifeat(snakenode node);							//判断是否吃到食物 
	bool ifcrash();										//判断是否撞墙或自撞 
	bool run();											//蛇的移动状态 
	void Rungame();										//运行 
	int score()											//获取得分 
	{
		return length-5;
	}
protected:
	snakenode snake[500];								//存储蛇结点的数组，表示蛇 
	int length;											//蛇长 
	int direction;										//移动方向 
	int hard;											//难度（体现为蛇的移动速度） 
	double speed;										//速度 
	char ch;											//按键 
	clock_t a,b;
};

Snake::Snake(int x)										//构造函数---绘制蛇的初始状态 
{
	hard=x;												//难度 
	direction=3;										//初始方向 
	length=5;											//初始长度 
	for (int i=0;i<=4;i++)								//每个结点的初始坐标 
	{
		snake[i].x=5-i;
		snake[i].y=1;
	}
	gotoxy(snake[0].x,snake[0].y);						//将光标移至蛇头坐标处 
    cout << "O";										//打印蛇头 
    for (int i=1;i<=length-1;i++)						//依次将光标移至每个蛇结点并打印蛇身 
	{
        gotoxy(snake[i].x,snake[i].y);
        cout << "*";
    }
    gotoxy(W+7,H/2);									//将光标移至地图右侧中间 
    cout <<"score:0";									//打印score，用来显示得分，初始分数为0 
}

bool Snake::ifeat(snakenode node)										//判断是否吃到食物 
{
	if(snake[0].x==food_x&&snake[0].y==food_y)			//如果吃到食物 
    {
        length++;										//蛇长+1 
        gotoxy(W+13,H/2);								//将光标移至分数坐标处 
    	cout <<length-5;								//打印此时分数（+1） 
        snake[length-1]=node;							//将新结点坐标赋值给蛇尾结点 
        return true;
    }
    return false;
}

bool Snake::ifcrash()									//判断是否撞墙或自撞 
{
	if (snake[0].x==0||snake[0].y==0||snake[0].x==W||snake[0].y==H)	//如果撞墙 
		return false;
    for (int i=1;i<=length-1;i++)									//如果自撞 
    {
        if (snake[0].x==snake[i].x && snake[0].y==snake[i].y)
			return false;
    }
    return true;
}

bool Snake::run()										//蛇的移动状态 
{
    snakenode temp;										//构造新的蛇身结点 
    bool e=false;
    temp=snake[length-1];								//将蛇尾结点（的坐标）赋值给新的蛇身结点 
    for(int i=length-1;i>=1;i--)						//依次将前一个结点（的坐标）赋值给后一个结点，使蛇向前移动 
        snake[i]=snake[i-1];
    if(direction==0)									//向上转向 
    	snake[0].y=snake[0].y-1;						//x坐标不变，y坐标-1 
    if(direction==1)									//向下转向 
    	snake[0].y=snake[0].y+1;						//x坐标不变，y坐标+1 
    if(direction==2)									//向左转向 
    	snake[0].x=snake[0].x-1;						//x坐标-1，y坐标不变 
    if(direction==3)									//向右转向 
    	snake[0].x=snake[0].x+1;						//x坐标+1，y坐标不变 
    gotoxy(snake[0].x,snake[0].y);						//将光标移至蛇头的新位置 
    cout <<"O";											//打印新的蛇头 
    gotoxy(snake[1].x,snake[1].y);						//将光标移动到第一个蛇身结点 
    cout <<"*";											//打印第一个蛇身（填补蛇头转向后的空白） 
	e=ifeat(temp); 
    if (!e)												//如果未吃到食物 
    {
        gotoxy(temp.x,temp.y);							//将光标移至新结点坐标处 
        cout << " ";									//在将原先的蛇尾结点位置打印空格，表示蛇向前移动而未增长 
    }
    else												//如果吃到食物---不在原先的蛇尾结点位置打印空格，表示蛇向前移动且增长 
    	Food();											//产生新的食物 
    e=ifcrash(); 
    if(!e)												//如果撞墙或自撞，返回false（游戏结束） 
        return false;
    return true;										//如果未撞墙或自撞，返回true（游戏继续） 
}

void Snake::Rungame()									//运行 
{
	while(1)											//死循环，通过判断是否撞墙或自撞决定是否结束循环 
	{
		speed=(double)15*length/(double)((W-1)*(H-1));	//随着游戏的进行不断增加难度（速度随蛇长的增加而增加） 
		a=clock();										//计算这段程序运行的时间（ms） 
		while(1)										//死循环，当进入此循环时，表现为蛇的短暂停顿 
		{
			b=clock();
			if(b-a>=(int)(400-30*hard)*(1-sqrt(speed)))	//由hard（难度）及speed（速度）确定周期，当时间超过此周期时，跳出循环，蛇向前运动 
				break;									//借此实现蛇的周期性运动，同时借助hard及speed调节蛇的运动速度 
		}
		if(kbhit())										//判断按键 
		{
		    ch=getch();									//读取按键 
		    if(ch==32)									//按空格键进入循环，游戏暂停 
		    	while(getch()!=32);						//再次按空格键退出循环，游戏继续 
			else if(ch==-32)							//方向键，判断方向 
			{
		    	ch=getch();
				switch(ch)
				{
					case 72:							//UP键 
						if(direction==2||direction==3)	//若原方向为水平 
							direction=0;				//向上转向 
						break;
					case 80:							//DOWN键 
						if(direction==2||direction==3)	//若原方向为水平 
							direction=1;				//向下转向 
						break;
					case 75:							//LEFT键 
						if(direction==0||direction==1)	//若原方向为竖直 
							direction=2;				//向左转向 
						break;
					case 77:							//RIGHT键 
						if(direction==0||direction==1)	//若原方向为竖直 
							direction=3;				//向右转向 
						break;
				}
			}
		}
		if(!run())										//判断移动状态 
			break;										//（是否撞墙或自撞，若是，则返回false，跳出循环，游戏结束；若否，则返回true，继续循环，游戏继续） 
	}
}

int main()
{
	cout <<"请选择难度(为确保游戏体验,请从1~10中选择):" <<endl;					//选择1~10中的一个数，表示初始难度（速度） 
	int h;												//难度 
	cin >>h;											//输入难度 
	system("cls");										//清屏 
	hide();												//隐藏光标 
	Snake snake0(h);									//建立蛇对象（由于继承关系，自动调用地图类的构造函数），调用蛇类的构造函数 
	snake0.Rungame();									//运行 
	system("cls");										//清屏 
	cout <<"SCORE:" <<snake0.score() <<endl;			//输出最终分数 
	cout <<"GAME OVER!" <<endl;							//game over 
	return 0;
}
