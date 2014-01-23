#include <iostream>
#include <ctime>
using namespace std;

typedef struct stack{
	int a[10];
	int top;
}stack,*pstack;

void init(pstack s)
{
	s->top=-1;
}

bool full(pstack s)
{
	return s->top==9;
}

void push(pstack s,int elem)
{
	if(!full(s)){
		s->top++;
		s->a[s->top]=elem;		
	}
}

bool empty(pstack s)
{
	return s->top==-1; 
}

int pop(pstack s)
{
	int re=numeric_limits<int>::min();
	if(!empty(s)){			
		re=s->a[s->top];
		s->top--;		
	}
	return re;
}



int main()
{
	srand((unsigned)time(NULL));
	int count;
	while (count=rand()%10,count<3);
	count=10;
	stack s1;
	stack s2;
	init(&s1);
	init(&s2);
	int tmp;
	for(int i=0;i<count;++i){
		tmp=rand()%21-10;
		push(&s1,tmp);	
		cout<<tmp<<"\t";
	}
	cout<<endl;

	for(int i=0;i<count;++i){
		push(&s2,pop(&s1));
	}

	for(int i=0;i<count;++i){
		cout<<pop(&s2)<<"\t";
	}
	cout<<endl;

}
