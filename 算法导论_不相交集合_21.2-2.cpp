#include <iostream>

using namespace std;
struct queue;//声明

typedef struct disjoint_set_node{
	queue *represent;//指向该结点的代表
	int value;
	disjoint_set_node *next;//下一个结点指针
}disjoint_set_node,*pDisjoint_set_node;

typedef struct queue{
	disjoint_set_node *head;
	disjoint_set_node *tail;
	int size;
}queue,*pQueue;

pQueue make_set(int value)//创建结点集合
{
	pQueue qu=new queue;
	pDisjoint_set_node pd=new disjoint_set_node;
	pd->value=value;
	pd->next=NULL;
	pd->represent=qu;
	qu->head=pd;
	qu->tail=pd;
	qu->size=1;
	return qu;
}

int find_set(pQueue *&pq,int *in,int n,int x)//查找结点所属的集合
{
	return in[x];
}

void union_dis(pQueue &px,pQueue &py,int * in)//合并两个集合
{
	if(px && py){
		if(px->size<py->size){
			pQueue tmp=py;
			py=px;
			px=tmp;
		}
		px->size+=py->size;
		px->tail->next=py->head;//链接链表
		px->tail=py->tail;
		pDisjoint_set_node pd=py->head;
		for(int i=0;i<py->size;++i){
			in[pd->value]=px->head->value;
			pd->represent=px;
			pd=pd->next;
		}
		delete py;//将多余的头结点删除掉
		py=NULL;
	}
}

void main()
{
	int n=16;
	pQueue *pq=new pQueue[n];
	int *in=new int[n];//存储结点所属集合索引
	for(int i=0;i<n;++i){
		pq[i]=make_set(i);
		in[i]=i;
	}
	for(int i=0;i<n-1;i+=2){
		union_dis(pq[in[i]],pq[in[i+1]],in);
	}
	for(int i=0;i<n-3;i+=4){
		union_dis(pq[in[i]],pq[in[i+2]],in);
	}
	for(int i=0;i<n;++i){
		if(pq[i]){
			pDisjoint_set_node pd=pq[i]->head;
			for(int j=0;j<pq[i]->size;++j){
				cout<<pd->value<<" ";
				pd=pd->next;
			}
			cout<<endl;
		}
	}

	union_dis(pq[in[0]],pq[in[4]],in);
	union_dis(pq[in[10]],pq[in[12]],in);
	union_dis(pq[in[0]],pq[in[9]],in);

	for(int i=0;i<n;++i){
		if(pq[i]){
			pDisjoint_set_node pd=pq[i]->head;
			for(int j=0;j<pq[i]->size;++j){
				cout<<pd->value<<" ";
				pd=pd->next;
			}
			cout<<endl;
		}
	}

	int index=find_set(pq,in,n,2);
	cout<<index<<endl;

	index=find_set(pq,in,n,9);
	cout<<index<<endl;

	for(int i=0;i<n;++i){//删除结点信息
		if(pq[i]){
			delete pq[i];
			pDisjoint_set_node pd=pq[i]->head;
			pDisjoint_set_node pt=pd;
			for(int j=0;j<pq[i]->size;++j){
				pd=pd->next;
				delete pt;
			}
		}
	}
	delete []in;
}
