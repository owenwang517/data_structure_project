#include<iostream>
#include<cstdio>
#include<cstdlib>										//rand()����ͷ�ļ� 
#include<ctime>											//clock()����ͷ�ļ� 
#include<conio.h>										//kbhit()����ͷ�ļ� 
#include<cmath>											//sqrt()����ͷ�ļ� 
#include<windows.h>										//�ƶ���꺯��ͷ�ļ� 
#define H 20											//��ͼ�� 
#define W 60											//��ͼ�� 
using namespace std;

HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void gotoxy(int x,int y)								//�ƶ���� 
{	 
	coord.X=x;											//x���� 
    coord.Y=y;											//y���� 
	SetConsoleCursorPosition(handle,coord);
}

void hide()												//���ع�� 
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(handle, &cursor_info);
}


class Map												//��ͼ 
{
public:
	Map();												//���캯�� 
	void Food();										//����ʳ�� 
protected:
	int food_x,food_y;									//ʳ������ 
};

Map::Map()												//���캯��---���Ƶ�ͼ 
{
	int i,j;
	for(j=0;j<=W;j++)									//��һ�� 
	{
		if(j==0||j==W)
			cout<<'+';
		else
			cout<<'-';
	}
	cout<<endl;											//ת�� 
    for(i=1;i<=H-1;i++)									//�ڶ��������ڶ��� 
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
    for(j=0;j<=W;j++)									//���һ�� 
	{
		if(j==0||j==W)
			cout<<'+';
		else
			cout<<'-';
	}
	cout<<endl;											//ת�� 
	gotoxy(W+2,H/2+2);
	cout <<"���ո����ͣ/����"; 
    Food();												//������ʼʳ�� 
}

void Map::Food()										//����ʳ�� 
{
	srand(time(0));										//������������� 
	do
	{
		food_x=rand()%(W-1)+1;							//�������ʳ���x���� 
		food_y=rand()%(H-1)+1;							//�������ʳ���y���� 
	}
	while(food_x==0||food_x>=W||food_y==0||food_y>=H);	//ѭ���������ʳ�����ֱ꣬��ʳ��λ�ڵ�ͼ�� 
	gotoxy(food_x,food_y);								//������������괦 
	cout<<'$';											//��ӡʳ�� 
}


struct snakenode										//�߽�㣬����x,y���� 
{
	int x,y;
};

class Snake:public Map									//�� 
{
public:
	Snake(int x);										//���캯�� 
	bool ifeat(snakenode node);							//�ж��Ƿ�Ե�ʳ�� 
	bool ifcrash();										//�ж��Ƿ�ײǽ����ײ 
	bool run();											//�ߵ��ƶ�״̬ 
	void Rungame();										//���� 
	int score()											//��ȡ�÷� 
	{
		return length-5;
	}
protected:
	snakenode snake[500];								//�洢�߽������飬��ʾ�� 
	int length;											//�߳� 
	int direction;										//�ƶ����� 
	int hard;											//�Ѷȣ�����Ϊ�ߵ��ƶ��ٶȣ� 
	double speed;										//�ٶ� 
	char ch;											//���� 
	clock_t a,b;
};

Snake::Snake(int x)										//���캯��---�����ߵĳ�ʼ״̬ 
{
	hard=x;												//�Ѷ� 
	direction=3;										//��ʼ���� 
	length=5;											//��ʼ���� 
	for (int i=0;i<=4;i++)								//ÿ�����ĳ�ʼ���� 
	{
		snake[i].x=5-i;
		snake[i].y=1;
	}
	gotoxy(snake[0].x,snake[0].y);						//�����������ͷ���괦 
    cout << "O";										//��ӡ��ͷ 
    for (int i=1;i<=length-1;i++)						//���ν��������ÿ���߽�㲢��ӡ���� 
	{
        gotoxy(snake[i].x,snake[i].y);
        cout << "*";
    }
    gotoxy(W+7,H/2);									//�����������ͼ�Ҳ��м� 
    cout <<"score:0";									//��ӡscore��������ʾ�÷֣���ʼ����Ϊ0 
}

bool Snake::ifeat(snakenode node)										//�ж��Ƿ�Ե�ʳ�� 
{
	if(snake[0].x==food_x&&snake[0].y==food_y)			//����Ե�ʳ�� 
    {
        length++;										//�߳�+1 
        gotoxy(W+13,H/2);								//����������������괦 
    	cout <<length-5;								//��ӡ��ʱ������+1�� 
        snake[length-1]=node;							//���½�����긳ֵ����β��� 
        return true;
    }
    return false;
}

bool Snake::ifcrash()									//�ж��Ƿ�ײǽ����ײ 
{
	if (snake[0].x==0||snake[0].y==0||snake[0].x==W||snake[0].y==H)	//���ײǽ 
		return false;
    for (int i=1;i<=length-1;i++)									//�����ײ 
    {
        if (snake[0].x==snake[i].x && snake[0].y==snake[i].y)
			return false;
    }
    return true;
}

bool Snake::run()										//�ߵ��ƶ�״̬ 
{
    snakenode temp;										//�����µ������� 
    bool e=false;
    temp=snake[length-1];								//����β��㣨�����꣩��ֵ���µ������� 
    for(int i=length-1;i>=1;i--)						//���ν�ǰһ����㣨�����꣩��ֵ����һ����㣬ʹ����ǰ�ƶ� 
        snake[i]=snake[i-1];
    if(direction==0)									//����ת�� 
    	snake[0].y=snake[0].y-1;						//x���겻�䣬y����-1 
    if(direction==1)									//����ת�� 
    	snake[0].y=snake[0].y+1;						//x���겻�䣬y����+1 
    if(direction==2)									//����ת�� 
    	snake[0].x=snake[0].x-1;						//x����-1��y���겻�� 
    if(direction==3)									//����ת�� 
    	snake[0].x=snake[0].x+1;						//x����+1��y���겻�� 
    gotoxy(snake[0].x,snake[0].y);						//�����������ͷ����λ�� 
    cout <<"O";											//��ӡ�µ���ͷ 
    gotoxy(snake[1].x,snake[1].y);						//������ƶ�����һ�������� 
    cout <<"*";											//��ӡ��һ���������ͷת���Ŀհף� 
	e=ifeat(temp); 
    if (!e)												//���δ�Ե�ʳ�� 
    {
        gotoxy(temp.x,temp.y);							//����������½�����괦 
        cout << " ";									//�ڽ�ԭ�ȵ���β���λ�ô�ӡ�ո񣬱�ʾ����ǰ�ƶ���δ���� 
    }
    else												//����Ե�ʳ��---����ԭ�ȵ���β���λ�ô�ӡ�ո񣬱�ʾ����ǰ�ƶ������� 
    	Food();											//�����µ�ʳ�� 
    e=ifcrash(); 
    if(!e)												//���ײǽ����ײ������false����Ϸ������ 
        return false;
    return true;										//���δײǽ����ײ������true����Ϸ������ 
}

void Snake::Rungame()									//���� 
{
	while(1)											//��ѭ����ͨ���ж��Ƿ�ײǽ����ײ�����Ƿ����ѭ�� 
	{
		speed=(double)15*length/(double)((W-1)*(H-1));	//������Ϸ�Ľ��в��������Ѷȣ��ٶ����߳������Ӷ����ӣ� 
		a=clock();										//������γ������е�ʱ�䣨ms�� 
		while(1)										//��ѭ�����������ѭ��ʱ������Ϊ�ߵĶ���ͣ�� 
		{
			b=clock();
			if(b-a>=(int)(400-30*hard)*(1-sqrt(speed)))	//��hard���Ѷȣ���speed���ٶȣ�ȷ�����ڣ���ʱ�䳬��������ʱ������ѭ��������ǰ�˶� 
				break;									//���ʵ���ߵ��������˶���ͬʱ����hard��speed�����ߵ��˶��ٶ� 
		}
		if(kbhit())										//�жϰ��� 
		{
		    ch=getch();									//��ȡ���� 
		    if(ch==32)									//���ո������ѭ������Ϸ��ͣ 
		    	while(getch()!=32);						//�ٴΰ��ո���˳�ѭ������Ϸ���� 
			else if(ch==-32)							//��������жϷ��� 
			{
		    	ch=getch();
				switch(ch)
				{
					case 72:							//UP�� 
						if(direction==2||direction==3)	//��ԭ����Ϊˮƽ 
							direction=0;				//����ת�� 
						break;
					case 80:							//DOWN�� 
						if(direction==2||direction==3)	//��ԭ����Ϊˮƽ 
							direction=1;				//����ת�� 
						break;
					case 75:							//LEFT�� 
						if(direction==0||direction==1)	//��ԭ����Ϊ��ֱ 
							direction=2;				//����ת�� 
						break;
					case 77:							//RIGHT�� 
						if(direction==0||direction==1)	//��ԭ����Ϊ��ֱ 
							direction=3;				//����ת�� 
						break;
				}
			}
		}
		if(!run())										//�ж��ƶ�״̬ 
			break;										//���Ƿ�ײǽ����ײ�����ǣ��򷵻�false������ѭ������Ϸ�����������򷵻�true������ѭ������Ϸ������ 
	}
}

int main()
{
	cout <<"��ѡ���Ѷ�(Ϊȷ����Ϸ����,���1~10��ѡ��):" <<endl;					//ѡ��1~10�е�һ��������ʾ��ʼ�Ѷȣ��ٶȣ� 
	int h;												//�Ѷ� 
	cin >>h;											//�����Ѷ� 
	system("cls");										//���� 
	hide();												//���ع�� 
	Snake snake0(h);									//�����߶������ڼ̳й�ϵ���Զ����õ�ͼ��Ĺ��캯��������������Ĺ��캯�� 
	snake0.Rungame();									//���� 
	system("cls");										//���� 
	cout <<"SCORE:" <<snake0.score() <<endl;			//������շ��� 
	cout <<"GAME OVER!" <<endl;							//game over 
	return 0;
}
