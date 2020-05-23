#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

class CStack								//栈类 
{
public:
	CStack(int i)							//构造函数，构建空栈，i为栈的最大高度 
	{
		height=0;							//栈高初始为0 
		top=-1;								//栈顶指针初始为-1 
		maxsize=(i>10)?i:10;				//最大栈高至少为10 
		elements=new float[maxsize];		//元素数组（float类型） 
	}
	void push(float x);						//入栈函数 
	bool pop();								//出栈函数 
	int pop(int f);
	bool full()								//判断堆栈是否为满 
	{
		return (top==maxsize-1)?true:false;
	}
	bool empty()							//判断堆栈是否为空 
	{
		return (height==0)?true:false;
	}
	float gettop()							//获取栈顶元素 
	{
		return elements[top];
	}
protected:
	int height;								//栈高 
	int top;								//栈顶指针（数组下标）
	int maxsize;							//栈的最大高度 
	float* elements;						//一维数组指针，用于存放栈中元素 
};

void CStack::push(float x)					//入栈函数 
{
	elements[++top]=x;						//栈顶下标后移一位，并赋值 
	height++;								//栈高+1 
}

bool CStack::pop()							//出栈函数 
{
	if(empty())								//若栈为空，返回false 
		return false;
	else									//若栈非空 
	{
		top--;								//栈顶指针前移一位 
		height--;							//栈高-1 
		return true;						//返回true 
	}
}

int CStack::pop(int f)
{
	if(empty())								//若栈为空，返回false 
		return 0;
	else									//若栈非空 
	{
		int topelement;
		topelement=elements[top];
		top--;								//栈顶指针前移一位 
		height--;							//栈高-1 
		return topelement;
	}
}

int getlevel(char ch)						//判断优先级函数 
{
	int level;								//优先级 
	switch(ch)
	{
		case'+':level=1;break;				//+-为1 
		case'-':level=1;break;
		case'*':level=2;break;				//*/为2 
		case'/':level=2;break;
		case'^':level=3;break;				//^%为3 
		case'%':level=3;break;
	}
	return level;							//返回优先级 
}

int main()
{	
	char ch[50];							//待输入的中缀表达式（char类型的数组） 
	cin >>ch;								//输入中缀表达式 
	int s=strlen(ch);						//计算数组元素个数 
	int f=1;
	CStack stack(50);
	char ch0;
	for(int i=0;i<s;i++)
		{
			if(ch[i]=='{'||ch[i]=='['||ch[i]=='(')
				stack.push(ch[i]);
			if(ch[i]=='}'||ch[i]==']'||ch[i]==')')
			{
				if(ch[i]=='}')
				{
					ch0=stack.pop(1);
					if(ch0!='{')
					{
						f=0;break;
					}
				}
				if(ch[i]==']')
				{
					ch0=stack.pop(1);
					if(ch0!='[')
					{
						f=0;break;
					}
				}
				if(ch[i]==')')
				{
					ch0=stack.pop(1);
					if(ch0!='(')
					{
						f=0;break;
					}
				}
			}
		}
	if(!stack.empty())
		f=0;
	if(f==0)
		cout <<"表达式不正确" <<endl;
	else if(f==1)
	{
		CStack stack1(20);						//栈1，用于临时存放优先级较低的运算符 
		CStack stack2(50);						//栈2，用于存放后缀表达式（运算符以ascll码形式存放） 
		float num;								//用于存放字符转化成的数字 
		int n;									//用来记录数字小数部分的位数 
		for(int i=0;i<s;i++)					//遍历中缀表达式字符串 
		{
			if(isdigit(ch[i]))					//若为数字 
			{
				num=0;
				n=1;
				do								//从此数字开始向后检索，直到最近的一个非数字元素为止, 
				{								//将该非数字元素之前的数字通过计算化为数字的整数部分 
					num=num*10+(ch[i]-'0');
					i++;
				}
				while(isdigit(ch[i]));
				if(ch[i]=='.')					//若该非数字元素为小数点 
				{
					i++;
					do							//从小数点后面的数字开始向后检索,直到最近的一个运算符为止, 
					{							//将该运算符之前的数字通过计算化为数字的小数部分,并与之前的整数部分相加 
						num=num+((float)(ch[i]-'0')/(float)(pow(10,n)));
						n++;
						i++;
					}
					while(isdigit(ch[i]));
				}
				i--;							//由于跳出循环时,ch[i]为最后一位数字后面的未处理的运算符,与for循环的i++重复,所以i-- 
				stack2.push(num);				//将计算所得的整形数字存入stack2中 
			}
			else if(ch[i]=='+'||ch[i]=='-'||ch[i]=='*'||ch[i]=='/'||ch[i]=='^'||ch[i]=='%')	//若为运算符 
			{
				while(1)						//死循环，直到有运算符被暂存入stack1为止 
				{
					if(stack1.empty()||stack1.gettop()=='(')				//若stack1栈空或栈顶元素为左括号 
					{
						stack1.push(ch[i]);break;							//将ch[i]暂存入stack1 
					}
					else if(getlevel(ch[i])>getlevel(stack1.gettop()))		//若ch[i]优先级>stack1栈顶元素 
					{
						stack1.push(ch[i]);break;							//将ch[i]暂存入stack1 
					}
					else													//若ch[i]优先级<stack1栈顶元素 
					{
						char ch1=stack1.gettop();							//将stack1栈顶元素存入变量ch1 
						stack1.pop();										//stack1栈顶元素出栈 
						stack2.push(ch1);									//将ch1存入stack2 
					}
				}
			}
			else															//若ch[i]为括号 
			{
				if(ch[i]=='(')												//若为左括号 
					stack1.push(ch[i]);										//将ch[i]暂存入stack1 
				else														//若为右括号 
				{
					while(stack1.gettop()!='(')								//循环直至stack1栈顶元素为左括号 
					{
						char ch2=stack1.gettop();							//将stack1栈顶元素存入变量ch2 
						stack1.pop();										//stack1栈顶元素出栈 
						stack2.push(ch2);									//将ch2存入stack2 
					}
					stack1.pop();											//将stack1中的左括号出栈 
				}
			}
		}
		while(!stack1.empty())												//循环直至stack1为空 
		{
			char ch3=stack1.gettop();										//将stack1栈顶元素存入ch3 
			stack2.push(ch3);												//将ch3存入stack2 
			stack1.pop();													//stack1栈顶元素出栈 
		}
		for(;!stack2.empty();)	//输出stack2,测试中缀转后缀是否正确 
		{
			cout <<stack2.gettop() <<' ';
			stack2.pop();
		}
	}
	return 0;
}
