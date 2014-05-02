#include <iostream>
#include <map>
using namespace std;
struct queue;//声明

typedef struct disjoint_set_node{
	queue *represent;//指向该结点的代表
	char value;
	disjoint_set_node *next;//下一个结点指针
}disjoint_set_node,*pDisjoint_set_node;

typedef struct queue{
	disjoint_set_node *head;
	disjoint_set_node *tail;
	int size;
}queue,*pQueue;

pQueue make_set(char value)//创建结点集合
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

char find_set(pQueue *pq,map<char,int> ma,char c)//查找结点所属的集合
{
	return pq[ma[c]]->head->value;
}

void union_dis(pQueue &px,pQueue &py,map<char,int>& ma)//合并两个集合
{
	if(px && py && px!=py){
		int x_num=px->size,y_num=py->size;
		if(x_num<y_num){
			pQueue tmp=py;
			py=px;
			px=tmp;
		}
		px->size+=py->size;
		px->tail->next=py->head;//链接链表
		px->tail=py->tail;
		pDisjoint_set_node pd=py->head;
		for(int i=0;i<py->size;++i){			
			ma[pd->value]=ma[px->head->value];
			//cout<<ma[pd->value]<<endl;
			pd->represent=px;
			pd=pd->next;
		}		
		delete py;//将多余的头结点删除掉
		py=NULL;
		if(x_num<y_num){
			py=px;
			px=NULL;
		}
	}
}

void main()
{
	int n=7;
	pQueue *pq=new pQueue[n];
	map<char,int>ma;//存储结点所属集合索引
	char *c=new char[n];
	c[0]='f',c[1]='g',c[2]='d',c[3]='c',c[4]='h',c[5]='e',c[6]='b';
	for(int i=0;i<n;++i){
		pq[i]=make_set(c[i]);
		ma[c[i]]=i;
	}
	union_dis(pq[ma['f']],pq[ma['g']],ma);
	union_dis(pq[ma['d']],pq[ma['g']],ma);

	union_dis(pq[ma['c']],pq[ma['h']],ma);
	union_dis(pq[ma['e']],pq[ma['h']],ma);
	union_dis(pq[ma['e']],pq[ma['b']],ma);

	char tm=find_set(pq,ma,'g');
	cout<<tm<<endl;

	for(int i=0;i<n;++i){//删除结点信息
		if(pq[i]){
			pDisjoint_set_node pd=pq[i]->head;
			pDisjoint_set_node pt=pd;
			for(int j=0;j<pq[i]->size;++j){
				pt=pd;
				pd=pd->next;
				delete pt;
			}
			delete pq[i];
		}
	}
	delete[]c;
	map<char,int>().swap(ma);
	ma.clear();
}
