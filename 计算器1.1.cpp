#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

class CStack								//ջ�� 
{
public:
	CStack(int i)							//���캯����������ջ��iΪջ�����߶� 
	{
		height=0;							//ջ�߳�ʼΪ0 
		top=-1;								//ջ��ָ���ʼΪ-1 
		maxsize=(i>10)?i:10;				//���ջ������Ϊ10 
		elements=new float[maxsize];		//Ԫ�����飨float���ͣ� 
	}
	void push(float x);						//��ջ���� 
	bool pop();								//��ջ���� 
	int pop(int f);
	bool full()								//�ж϶�ջ�Ƿ�Ϊ�� 
	{
		return (top==maxsize-1)?true:false;
	}
	bool empty()							//�ж϶�ջ�Ƿ�Ϊ�� 
	{
		return (height==0)?true:false;
	}
	float gettop()							//��ȡջ��Ԫ�� 
	{
		return elements[top];
	}
	int getheight()
	{
		return height;	
	}
protected:
	int height;								//ջ�� 
	int top;								//ջ��ָ�루�����±꣩
	int maxsize;							//ջ�����߶� 
	float* elements;						//һά����ָ�룬���ڴ��ջ��Ԫ�� 
};

void CStack::push(float x)					//��ջ���� 
{
	elements[++top]=x;						//ջ���±����һλ������ֵ 
	height++;								//ջ��+1 
}

bool CStack::pop()							//��ջ���� 
{
	if(empty())								//��ջΪ�գ�����false 
		return false;
	else									//��ջ�ǿ� 
	{
		top--;								//ջ��ָ��ǰ��һλ 
		height--;							//ջ��-1 
		return true;						//����true 
	}
}

int CStack::pop(int f)
{
	if(empty())								//��ջΪ�գ�����false 
		return 0;
	else									//��ջ�ǿ� 
	{
		int topelement;
		topelement=elements[top];
		top--;								//ջ��ָ��ǰ��һλ 
		height--;							//ջ��-1 
		return topelement;
	}
}

int getlevel(char ch)						//�ж����ȼ����� 
{
	int level;								//���ȼ� 
	switch(ch)
	{
		case'+':level=1;break;				//+-Ϊ1 
		case'-':level=1;break;
		case'*':level=2;break;				//*/Ϊ2 
		case'/':level=2;break;
		case'^':level=3;break;				//^%Ϊ3 
		case'%':level=3;break;
	}
	return level;							//�������ȼ� 
}

int main()
{	
	char ch[50];							//���������׺���ʽ��char���͵����飩 
	cin >>ch;								//������׺���ʽ 
	int s=strlen(ch);						//��������Ԫ�ظ��� 
	int f=1;
	CStack stack(50);						//������ţ����ڼ��������Ƿ�ƥ�� 
	char ch0;
	int sign[50]={0};
	int k=0,flag=1;
	for(int i=0;i<s;i++)							//������ʽ�Ƿ�����(�����Ƿ�ƥ��) 
		{
			if(ch[i]=='{'||ch[i]=='['||ch[i]=='(')	//���������ţ�����stack 
				stack.push(ch[i]);
			if(ch[i]=='}'||ch[i]==']'||ch[i]==')')	//���������ţ�ȡ��stack���topԪ��(������)�������Ƿ�ƥ�� 
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
	if(!stack.empty())								//ֻ�������ŵ���� 
		f=0;
	if(f==0)										//��f=0�����ʽ���� 
		cout <<"���Ų�ƥ��" <<endl;
	else if(f==1)									//��f=1��������׺ת��׺�Լ����� 
	{
		CStack stack1(20);						//ջ1��������ʱ������ȼ��ϵ͵������ 
		CStack stack2(50);						//ջ2�����ڴ�ź�׺���ʽ���������ascll����ʽ��ţ� 
		CStack stack3(20);
		float num;								//���ڴ���ַ�ת���ɵ����� 
		int n;									//������¼����С�����ֵ�λ�� 
		for(int i=0;i<s;i++)					//������׺���ʽ�ַ��� 
		{
			if(isdigit(ch[i]))					//��Ϊ���� 
			{
				num=0;
				n=1;
				do								//�Ӵ����ֿ�ʼ��������ֱ�������һ��������Ԫ��Ϊֹ, 
				{								//���÷�����Ԫ��֮ǰ������ͨ�����㻯Ϊ���ֵ��������� 
					num=num*10+(ch[i]-'0');
					i++;
				}
				while(isdigit(ch[i]));
				if(ch[i]=='.')					//���÷�����Ԫ��ΪС���� 
				{
					i++;
					do							//��С�����������ֿ�ʼ������,ֱ�������һ�������Ϊֹ, 
					{							//���������֮ǰ������ͨ�����㻯Ϊ���ֵ�С������,����֮ǰ������������� 
						num=num+((float)(ch[i]-'0')/(float)(pow(10,n)));
						n++;
						i++;
					}
					while(isdigit(ch[i]));
				}
				i--;							//��������ѭ��ʱ,ch[i]Ϊ���һλ���ֺ����δ����������,��forѭ����i++�ظ�,����i-- 
				stack2.push(num);				//���������õ��������ִ���stack2�� 
				sign[k++]=1;
			}
			else if(ch[i]=='-'&&i==0||ch[i]=='-'&&ch[i-1]=='('){
				i++;
				num=0;
				n=1;
				do								//�Ӵ����ֿ�ʼ��������ֱ�������һ��������Ԫ��Ϊֹ, 
				{								//���÷�����Ԫ��֮ǰ������ͨ�����㻯Ϊ���ֵ��������� 
					num=num*10+(ch[i]-'0');
					i++;
				}
				while(isdigit(ch[i]));
				if(ch[i]=='.')					//���÷�����Ԫ��ΪС���� 
				{
					i++;
					do							//��С�����������ֿ�ʼ������,ֱ�������һ�������Ϊֹ, 
					{							//���������֮ǰ������ͨ�����㻯Ϊ���ֵ�С������,����֮ǰ������������� 
						num=num+((float)(ch[i]-'0')/(float)(pow(10,n)));
						n++;
						i++;
					}
					while(isdigit(ch[i]));
				}
				i--;
				stack2.push(-num);
				sign[k++]=1;
			}
			else if(ch[i]=='+'||ch[i]=='-'||ch[i]=='*'||ch[i]=='/'||ch[i]=='^'||ch[i]=='%')	//��Ϊ����� 
			{
				while(1)						//��ѭ����ֱ������������ݴ���stack1Ϊֹ 
				{
					if(stack1.empty()||stack1.gettop()=='(')				//��stack1ջ�ջ�ջ��Ԫ��Ϊ������ 
					{
						stack1.push(ch[i]);break;							//��ch[i]�ݴ���stack1 
					}
					else if(getlevel(ch[i])>getlevel(stack1.gettop()))		//��ch[i]���ȼ�>stack1ջ��Ԫ�� 
					{
						stack1.push(ch[i]);break;							//��ch[i]�ݴ���stack1 
					}
					else													//��ch[i]���ȼ�<stack1ջ��Ԫ�� 
					{
						char ch1=stack1.gettop();							//��stack1ջ��Ԫ�ش������ch1 
						stack1.pop();										//stack1ջ��Ԫ�س�ջ 
						stack2.push(ch1);									//��ch1����stack2 
						k++;
					}
				}
			}
			else															//��ch[i]Ϊ���� 
			{
				if(ch[i]=='(')												//��Ϊ������ 
					stack1.push(ch[i]);										//��ch[i]�ݴ���stack1 
				else														//��Ϊ������ 
				{
					while(stack1.gettop()!='(')								//ѭ��ֱ��stack1ջ��Ԫ��Ϊ������ 
					{
						char ch2=stack1.gettop();							//��stack1ջ��Ԫ�ش������ch2 
						stack1.pop();										//stack1ջ��Ԫ�س�ջ 
						stack2.push(ch2);									//��ch2����stack2 
						k++;
					}
					stack1.pop();											//��stack1�е������ų�ջ 
				}
			}
		}
		while(!stack1.empty())												//ѭ��ֱ��stack1Ϊ�� 
		{
			char ch3=stack1.gettop();										//��stack1ջ��Ԫ�ش���ch3 
			stack2.push(ch3);												//��ch3����stack2 
			stack1.pop();													//stack1ջ��Ԫ�س�ջ 
		}
//		for(;!stack2.empty();)	//���stack2,������׺ת��׺�Ƿ���ȷ 
//		{
//			cout <<stack2.gettop() <<' ';
//			stack2.pop();
//		}
		float element[50];
		float first,second;													//�������ͱ������� 
		int h=stack2.getheight();
		for(int i=h-1;!stack2.empty();i--)									//��stack2�е���������������� 
		{
			element[i]=stack2.gettop();
			stack2.pop();
		}
		for(int i=0;i<h;i++)												//��ͷ��ʼ��������Ԫ�� 
		{
			if((element[i]=='+'||element[i]=='-'||element[i]=='*'||element[i]=='/'||element[i]=='^'||element[i]=='%')&&(sign[i]==0))	//���������(ascll��) 
			{
				second=stack3.gettop();										//ȡ��stack3��topԪ����Ϊ��������second  
				stack3.pop();												//����pop������topָ��ǰ��  
				first=stack3.gettop();										//��ȡtopԪ����Ϊ������first 
				flag=stack3.pop();												//����pop������topָ��ǰ�� 
				if(flag==0){
					cout<<"���Ŵ���";
					return 0;
				}
				if(element[i]=='+')											//���������������Ӧ���� 
				{
					stack3.push(first+second);
				}
				if(element[i]=='-')
				{
					stack3.push(first-second); 
				}
				if(element[i]=='*')
				{
					stack3.push(first*second);
				}
				if(element[i]=='/')
				{
					if(second==0){
						cout<<"��ĸ����Ϊ��"<<endl;
						return 0;
					}
					stack3.push(first/second);
				}
				if(element[i]=='^')
				{
					stack3.push(pow(first,second));
				}
				if(element[i]=='%')
				{
					stack3.push((int)first%(int)second);
				}
			}
			else															//����������������stack3�� 
			{
				stack3.push(element[i]);
			}
		}
		cout <<stack3.gettop() <<endl;										//stack3���������µ����ּ�Ϊ����������� 
	}
	return 0;
}
