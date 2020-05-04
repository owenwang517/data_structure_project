#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;
const int H=20;
const int W=20;
class Map{
	public:
		Map();
		void Food();
		void Print();
	protected:
		char m[H][W];
		int food_x,food_y;
		int score;
		int speed;
		int interval;
}; 

Map::Map(){
	int i,j;
	speed=50;
	for(i=1;i<=H-2;i++)
        for(j=1;j<=W-2;j++)
            m[i][j]=' ';
    for(i=0;i<=H-1;i++)
        m[0][i]=m[H-1][i]='-';
    for(i=1;i<=H-2;i++)
        m[i][0]=m[i][W-1]='|';
    m[0][0]=m[0][W-1]=m[H-1][0]=m[W-1][H-1]='+';
    Food();
}
void Map::Print(){
	int i,j;
	system("cls");
	cout<<"SCORE:"<<score<<endl;
	for(i=0;i<H;i++){
		for(j=0;j<W;j++){
			cout<<m[i][j]<<' ';
		}
		cout<<"\n";
	}		
}
void Map::Food(){
	srand(time(0));
	do{
		food_x=rand()%H-1;
		food_y=rand()%W-1;
	}while(m[food_x][food_y]!=' ');
	m[food_x][food_y]='$';
}

class Snake:public Map{
	public:
		Snake();
		void Eat();
		void Rungame();
		void Render();
	protected:
		int body[2][100];
		int length;
		int direction;
		int head;
		int tail;
		int head_x,head_y; 
};

Snake::Snake(){            //³õÊ¼»¯ÉßÉí 
	length=3;
	head=3;
	tail=0;
	score=0;
	int i;
	for(i=1;i<=3;i++)
        m[1][i]='*';
    m[1][4]='@';
    
	for(i=0;i<4;i++){
		body[0][i] = 1;
        body[1][i] = i + 1;
	}
}

void Snake::Render(){
	m[head_x][head_y]='@';
	m[body[0][head]][body[1][head]]='*';
	head=(head+1)%100;
	body[0][head]=head_x;
	body[1][head]=head_y;
	m[body[0][tail]][body[1][tail]]=' ';
	tail=(tail+1)%100;
}

void Snake::Eat(){
	m[head_x][head_y]='@';
	m[body[0][head]][body[1][head]]='*';
	head=(head+1)%100;
	body[0][head]=head_x;
	body[1][head]=head_y;
	length++;
	score++;
}

void Snake::Rungame(){
	long start,timeleft;
	direction=77;
	while(1){
		timeleft=1;
        start=clock();
        while((timeleft=(clock()-start<=speed))&&!kbhit());
        if(timeleft)
        {
            getch();
            direction = getch();
        }
		switch(direction){
			case 72:head_x=body[0][head]-1;head_y=body[1][head];break;
			case 80:head_x=body[0][head]+1;head_y=body[1][head];break;
			case 75:head_x=body[0][head];head_y=body[1][head]-1;break;
			case 77:head_x=body[0][head];head_y=body[1][head]+1;break;
		}
		if(head_x==0||head_x==20||head_y==0||head_y==20){
			cout<<"GAMEOVER!"<<endl;
			break;
		}
		if(m[head_x][head_y]!=' '&&m[head_x][head_y]!='$'){
			cout<<"GAMEOVER!"<<endl;
			break;
		}
		
		if(head_x==food_x&&head_y==food_y){
			Eat();
			Food();
		} 
		else Render();
		Print();
	}
}
int main(){
	Map m1;
	Snake s1;
	s1.Rungame();
}
