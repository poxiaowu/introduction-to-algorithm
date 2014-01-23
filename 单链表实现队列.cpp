#include<iostream>
#include <limits>
#include <ctime>
using namespace std;

typedef struct list{//用链表实现队列
	int value;
	list *next;
}list, *plist;

typedef struct queue{//队列
	plist head;
	plist tail;
}queue,*pqueue;

void enqueue(pqueue &l,plist node)//队列-向链表中添加元素
{	
	l->tail->next=node;
	l->tail=node;
}
int dequeue(pqueue &l)
{
	int re=numeric_limits<int>::min();
	if(l->head==l->tail){
		cout<<"empty queue"<<endl;
		return re;
	}	
	plist p;
	re=l->head->next->value;
	p=l->head->next;//删除节点
	l->head->next=l->head->next->next;
	delete p;//删除节点
	if(l->head->next==NULL)//如果是最后一个节点，则修改tail的值
		l->tail=l->head;
	return re;
}

void init(pqueue &l,plist node)
{
	l->head=node;
	l->tail=node;
}

int main()
{
	srand((unsigned)time(NULL));
	list head;//队列头结点
	head.next=NULL;
	head.value=numeric_limits<int>::min();

	queue *q=new queue;
	init(q,&head);

	int count,count1,count2;
	while(count=rand()%20,count<5);
	count=4;
	for(int i=0;i<count;++i){
		while(count1=rand()%8,count1<3);
		while(count2=rand()%8,count2<3);
		//count1=5,count2=5;
		plist ls;
		int tmp;
		cout<<"count1 is :"<<count1<<endl;
		for(int i=0;i<count1;++i){
			ls=new list;//队列结点
			ls->next=NULL;
			tmp=rand()%21-10;
			ls->value=tmp;
			cout<<tmp<<"\t";
			enqueue(q,ls);		
		}
		cout<<endl;
		cout<<"count2 is :"<<count2<<endl;
		ls=&head;
		for(int i=0;i<count2;++i){		
			cout<<dequeue(q)<<"\t";
		}
		cout<<endl;
	}
}
