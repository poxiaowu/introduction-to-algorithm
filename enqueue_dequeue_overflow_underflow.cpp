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

int main()
{
	srand((unsigned)time(NULL));
	int count;
	while (count=rand()%10,count<3);
	count=4;
	queue q;
	init(&q);

	int count1,count2;

	for(int i=0;i<count;i++){
		count1=rand()%6+1;
		cout<<"count1 is : "<<count1<<endl; 
		for(int i=0;i<count1;++i){
			enqueue(&q,rand()%21-10);	
		}

		for(int i=0;i<10;++i){
			cout<<q.a[i]<<"\t";	
		}
		cout<<endl;

		int elem;
		count2=rand()%6+1;
		cout<<"count2 is : "<<count2<<endl; 
		for(int i=0;i<count2;++i){
			elem=dequeue(&q);	
			cout<<elem<<"\t";
		}
		cout<<endl;
	}
}
