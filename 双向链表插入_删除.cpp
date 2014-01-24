#include<iostream>
#include <limits>
#include <ctime>
using namespace std;

typedef struct dlist{//双向链表
	int value;
	dlist *next;
	dlist *prev;
}dlist, *pdlist;

void insert(pdlist &d,pdlist cur)//双链表插入元素
{
	if(!d){
		d=cur;
	}else{
		cur->next=d;
		d->prev=cur;
		d=cur;
		cur->prev=NULL;
	}
}
void del(pdlist &d,int elem)
{
	pdlist p=d,tmp;
	while (p){
		tmp=p->next;
		if(p->value==elem){
			if(p->prev!=NULL){//删除首结点，不执行该操作
				p->prev->next=p->next;
			}else{
				d=p->next;
			}
			if(p->next!=NULL)//删除尾结点，不执行该操作
				p->next->prev=p->prev;			
			delete p;//删除即将被删除的元素
		}
		p=tmp;
	}
}
int main()
{
	srand((unsigned)time(NULL));
	int count;
	while(count=rand()%6,count<5);
	count=20;
	pdlist pd=NULL,pl=NULL;
	int tmp;
	for(int i=0;i<count;++i){
		pd=new dlist;
		pd->next=NULL;
		pd->prev=NULL;
		tmp=rand()%3-1;
		pd->value=tmp;
		insert(pl,pd);
		cout<<tmp<<"\t";
	}
	cout<<endl;
	pd=pl;
	while (pd)
	{
		cout<<pd->value<<"\t";
		pd=pd->next;	
	}
	cout<<endl;
	pd=pl;
	int elem=rand()%3-1;
	cout<<"element "<<elem<<" is deleted"<<endl;
	del(pd,elem);	
	while (pd)
	{
		cout<<pd->value<<"\t";
		pd=pd->next;	
	}
	cout<<endl;
}
