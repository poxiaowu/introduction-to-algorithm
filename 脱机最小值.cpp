#include <iostream>
#include <ctime>
#include <map>
using namespace std;

typedef struct list{//双向链表
	int key;//存储当前值
	list *next;//下一个结点指针
	list *prev;//前向指针
}list,*pList;

typedef struct queue{
	pList head;
	pList tail;
	queue *next;//下一个queue
	int rank;//记录该结点所指向的链表的顺序
	int num;
}queue,*pQueue;

void init(pQueue &pq)
{
	pq=new queue;
	pq->num=0;
	pq->head=NULL;
	pq->tail=NULL;
	pq->next=NULL;
}

pQueue make_set(int key)//创建新的集合
{
	pQueue pq=new queue;
	pList pl=new list;
	pl->key=key;
	pl->next=NULL;
	pl->prev=NULL;
	pq->head=pl;
	pq->tail=pl;
	pq->num=1;
	pq->next=NULL;
	return pq;
}

pQueue union_dis(pQueue &px,pQueue &py)//将两个链表按照大小合并
{
	if(px && py){
		if(px->num<py->num){//将元素个数少的插入到元素个数多的链表中
			pQueue ptmp=py;  //如果px中的元素个数少于py中元素个数，则交换两个链表
			py=px;
			px=ptmp;
			px->next=py->next;//更新指针，将px指向py的下一个指针
		}
		pList plx=px->head;
		pList ply=py->head;	
		pList plxpre=plx;
		pList plypre=ply;

		pList ptmp;
		while(plx && ply){//如果有一个链表已经结束，则结束
			if(plx->key>ply->key){
				ptmp=ply->next;

				ply->next=plx;
				plx->prev=ply;

				if(plx==plxpre){//如果是第一个结点,ply小于plx的第一个元素
					px->head=ply;
				}else{
					plxpre->next=ply;
					ply->prev=plxpre;
				}		
				plxpre=ply;
				ply=ptmp;
			}else{
				plxpre=plx;
				plx=plx->next;
			}
		}
		if(plx==NULL){
			if(ply){
				plxpre->next=ply;
				ply->prev=plxpre;
				px->tail=py->tail;
			}
		}
		px->num+=py->num;
		delete py;
		py=NULL;
		return px;
	}
	return (px==NULL)?(py):(px);
}

void random(int *a,int n)//生成随机数
{
	int index;
	int tmp;
	for(int i=0;i<n;++i){
		index=rand()%((n-i))+i;
		tmp=a[index];//交换元素
		a[index]=a[i];
		a[i]=tmp;
	}
}

pQueue find_set(map<int,pQueue>ma,int key)//操作元素key所在的集合
{
	return ma[key];
}

void off_line_minimum(pQueue phead,map<int,pQueue>ma,int *extracted,int m,int n)//脱机最小值
{
	pQueue pn;
	while(phead && phead->rank<m){
		pn=phead->next;
		int rank;
		if(pn){
			rank=pn->rank;
		}
		if(phead->num>0){
			pList ptmp=phead->head;
			extracted[phead->rank]=ptmp->key;
			phead->head=ptmp->next;
			if(ptmp->next)
				ptmp->next->prev=NULL;
			delete ptmp;
			--phead->num;
			if(pn){
				pn=union_dis(pn,phead);
			}
		}else{
			delete phead;
		}
		if(pn){
			pn->rank=rank;
		}
		phead=pn;
	}
}

int main()
{
	srand((unsigned)time(NULL));	
	int n=19;//元素个数
	int count=n;
	int rank=0;
	int key;
	pQueue pp=NULL,phead;
	pQueue pq=NULL,pq2=NULL;

	int *a=new int[n];
	for(int i=0;i<n;++i){//初始化
		a[i]=i;
	}
	random(a,n);//随机化
	int index=0;

	map<int,pQueue>ma;//元素与其链表地址的映射

	/*int d[9]={4,1,2,6,0,5,3,7,8};
	int tes[6]={1,2,2,1,2,1};
	int ind=0;*/

	while(count>0){
		int rnd=/*tes[ind++]*/rand()%(4);//生成一个随机数，确定每组内元素个数
		if(rnd>count){
			rnd=count;
		}
		cout<<"rank "<<rank<<" has "<<rnd<<" elments."<<endl;
		pq=NULL;pq2=NULL;
		for(int i=0;i<rnd;++i){
			key=/*d[index++]*/a[index++];
			cout<<key<<" ";
			pq=make_set(key);
			pq2=union_dis(pq2,pq);
			ma[key]=pq2;//将该值存入到map中
		}
		cout<<endl;
		if(rnd==0){
			init(pq2);
		}
		pq2->rank=rank++;	
		count-=rnd;

		if(pp==NULL){
			pp=pq2;
			phead=pq2;//头结点
		}else{
			pp->next=pq2;
			pp=pq2;
		}
	}
	int *extracted=new int[rank];
	off_line_minimum(phead,ma,extracted,rank,n);//脱机最小值
	for(int i=0;i<rank;++i){
		cout<<extracted[i]<<" ";
	}
	cout<<endl;
	delete[]a;
	delete[]extracted;
	return 0;
}
