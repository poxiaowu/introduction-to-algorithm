#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

typedef struct deque{//队列
	int a[10];
	int head;
	int tail;
}deque,*pdeque;

void init(pdeque q)//初始化
{
	q->head=0;
	q->tail=0;
}

void endeque(pdeque q,int elem)//进队列，从后端插入元素
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

void fwendeque(pdeque q,int elem)//从前端插入元素
{
	if((q->head+9)%10==q->tail){
		cout<<"overflow"<<endl;//队列上溢
		return;
	}	
	q->head--;
	if(q->head==-1)
		q->head=9;
	q->a[q->head]=elem;	
	
}

int tadedeque(pdeque q)//从后端出队列
{
	int elem=numeric_limits<int>::min();
	if(q->head==q->tail){
		cout<<"underflow"<<endl;
		return elem;
	}	
	q->tail--;
	if(q->tail==-1)
		q->tail=9;
	elem=q->a[q->tail];	
	
	return elem;
}

int dedeque(pdeque q)//出队列
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
	count=2;
	deque q;
	init(&q);

	int count1,count2;
	int flag;
	for(int i=0;i<count;i++){
		count1=rand()%6+1;
		cout<<"count1 is : "<<count1<<endl; 
		for(int i=0;i<count1;++i){
			flag=rand()%2;
			if(flag){
				cout<<"endeque:"<<endl;
				endeque(&q,rand()%21-10);	
			}else{
				cout<<"fwendeque:"<<endl;
				fwendeque(&q,rand()%21-10);	
			}
		}

		for(int i=0;i<10;++i){
			cout<<q.a[i]<<"\t";	
		}
		cout<<endl;

		int elem;
		count2=rand()%6+1;
		cout<<"count2 is : "<<count2<<endl; 
		for(int i=0;i<count2;++i){
			flag=rand()%2;
			if(flag){
				cout<<"dedeque:"<<endl;
				elem=dedeque(&q);	
			}else{
				cout<<"tadedeque:"<<endl;
				elem=tadedeque(&q);	
			}
			cout<<elem<<"\t";
		}
		cout<<endl;
	}
}
