#include<iostream>
#include <limits>
#include <ctime>
using namespace std;

typedef struct list{//用链表实现堆栈
	int value;
	list *next;
}list, *plist;

void insert_s_n(plist &l,plist node)//向链表中添加元素-堆栈顺序-不带头结点
{
	if(!l){
		l=node;
	}else{
		node->next=l;
		l=node;
	}
}

void inverse(plist &l)
{
	plist cur,pre,next;
	pre=l;
	cur=l->next;
	next=cur->next;
	pre->next=NULL;//第一个元素变为最后一个
	while (next){
		cur->next=pre;
		pre=cur;
		cur=next;
		next=next->next;
	}
	cur->next=pre;
	l=cur;//将最后结果赋值给l;
}


int main()
{
	srand((unsigned)time(NULL));
	plist head_s_n=NULL;

	int count,count2;
	while(count=rand()%20,count<10);
	list *lsn;//存放堆栈顺序指针和队列顺序指针
	int tmp;
	count=30;
	for(int i=0;i<count;++i){
		tmp=rand()%11-5;
		lsn=new list;
		lsn->next=NULL;
		lsn->value=tmp;
		insert_s_n(head_s_n,lsn);
		cout<<tmp<<"\t";
	}
	cout<<endl;
	lsn=head_s_n;
	for(int i=0;i<count;++i){
		cout<<lsn->value<<"\t";
		lsn=lsn->next;
	}
	cout<<endl;
	inverse(head_s_n);//链表反转

	lsn=head_s_n;
	for(int i=0;i<count;++i){
		cout<<lsn->value<<"\t";
		lsn=lsn->next;
	}
	cout<<endl;

}
