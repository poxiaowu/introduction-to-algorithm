#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

typedef struct queue{//队列
	int a[10];
	int head;
	int tail;
}queue,*pqueue;

void init(pqueue q)//初始化
{
	q->head=0;
	q->tail=0;
}

void enqueue(pqueue q,int elem)//进队列
{
	if((q->tail+1)%11==q->head){
		cout<<"overflow"<<endl;//队列上溢
		return;
	}
	if(q->tail==10){//到达数组的末尾
		q->tail=0;
	}
	q->a[q->tail]=elem;
	q->tail++;	
}

int dequeue(pqueue q)//出队列
{
	int elem=numeric_limits<int>::min();
	if(q->head==q->tail){
		cout<<"underflow"<<endl;
		return elem;
	}
	if(q->head==10)
		q->head=0;
	elem=q->a[q->head];
	q->head++;
	return elem;
}

void stack_init(pqueue q1,pqueue q2)
{
	init(q1);
	init(q2);
}

bool queue_empty(pqueue q)//队列为空
{
	return q->head==q->tail;
}

void push(pqueue q1,pqueue q2,int elem)//模拟入栈
{
	if(queue_empty(q1) && queue_empty(q2)){
		enqueue(q1,elem);
	}else if(queue_empty(q1)){
		enqueue(q2,elem);
	}else{
		enqueue(q1,elem);
	}
}

int pop(pqueue q1,pqueue q2)//模拟出栈
{
	int elem=numeric_limits<int>::min();
	if(queue_empty(q1) && queue_empty(q2)){
		cout<<"underflow"<<endl;
	}else if(queue_empty(q1)){
		int count=q2->tail-q2->head;
		if(count<0){
			count=10+count;
		}
		for(int i=0;i<count-1;++i){
			enqueue(q1,dequeue(q2));
		}
		elem=dequeue(q2);
	}else{
		int count=q1->tail-q1->head;
		if(count<0){
			count=10+count;
		}
		for(int i=0;i<count-1;++i){
			enqueue(q2,dequeue(q1));
		}
		elem=dequeue(q1);
	}
	return elem;
}



int main()
{
	srand((unsigned)time(NULL));
	int count;
	while (count=rand()%10,count<3);
	count=4;	
	queue q1,q2;
	stack_init(&q1,&q2);//队列初始化
	int tmp,count1,count2;

	for(int i=0;i<count;++i){
		count1=rand()%7+1;
		count2=rand()%7+1;
		cout<<"count1 is : "<<count1<<endl;
		for(int i=0;i<count1;++i){
			tmp=rand()%21-10;
			push(&q1,&q2,tmp);
			cout<<tmp<<"\t";
		}
		cout<<endl;
		cout<<"count2 is : "<<count2<<endl; 
		for(int i=0;i<count2;++i){
			tmp=pop(&q1,&q2);
			cout<<tmp<<"\t";
		}
		cout<<endl;
	}
}
