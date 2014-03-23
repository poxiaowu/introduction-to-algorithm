#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

typedef struct Link_graphic{//邻接表
	int value;
	Link_graphic *next;
}Link_graphic,*pLink_graphic;

typedef struct Link_list{//链表
	int value;
	Link_list *next;
}Link_list,*pLink_list;

typedef struct Queue{//队列
	Link_list *front,*tail;//头尾结点指针
}Queue;

void init(Queue *&queue)//队列初始化
{
	queue->front=NULL;
	queue->tail=NULL;
}
void enqueue(Queue *& queue,int value)//入队列操作
{
	if(queue->front==NULL && queue->tail==NULL){//当队列中还没有元素的时候
		pLink_list ls=new Link_list;
		ls->value=value;
		ls->next=NULL;
		queue->front=ls;
		queue->tail=ls;
	}else{
		pLink_list ls=new Link_list;
		ls->value=value;
		ls->next=NULL;
		queue->tail->next=ls;
		queue->tail=ls;
	}
}

void dequeue(Queue *&queue)//出队列操作
{
	if(queue->front){
		pLink_list pt=queue->front;
		queue->front=queue->front->next;
		delete pt;
	}
}

void add_vertex(pLink_graphic &plg,pLink_graphic plgtmp)//添加结点
{
	pLink_graphic tmp=plg->next;
	plg->next=plgtmp;
	plgtmp->next=tmp;
}
void delete_redundance(pLink_graphic *&plg,int n)//删除冗余边和自循环边
{
	bool *visited=new bool[n];
	pLink_graphic plgtmp;
	pLink_graphic plgpre;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			visited[j]=false;
		}
		visited[i]=true;

		plgtmp=plg[i]->next;
		plgpre=plg[i];
		while(plgtmp){
			if(visited[plgtmp->value]){//如果该元素已经存在,
				plgpre->next=plgtmp->next;
				delete plgtmp;
				plgtmp=plgpre->next;
			}else{
				visited[plgtmp->value]=true;
				plgpre=plgtmp;
				plgtmp=plgtmp->next;
			}
		}
	}
	delete [] visited;
}

void breadth_first_search(pLink_graphic *&plg,int value,int n)//广度优先搜索
{
	bool * visited=new bool[n];//设置数组标记
	for(int i=0;i<n;++i){
		visited[i]=false;
	}
	Queue *queue=new Queue;
	init(queue);//初始化队列
	enqueue(queue,value);//源结点如队列
	visited[value]=true;//已访问
	pLink_graphic pt;
	while (queue->front){//队列中存在元素
		pt=plg[queue->front->value]->next;
		while(pt){
			if(visited[pt->value]==false){//未访问则添加到队列
				enqueue(queue,pt->value);
				visited[pt->value]=true;
			}
			pt=pt->next;
		}
		cout<<queue->front->value<<" ";
		dequeue(queue);//父节点出队列		
	}	
	cout<<endl;
	delete[]visited;
}

int main()
{
	srand((unsigned)time(NULL));
	int n=10;
	pLink_graphic *plg=new pLink_graphic[n];
	pLink_graphic plgtmp;//临时存放
	for(int i=0;i<n;++i){
		plg[i]=new Link_graphic;
		plg[i]->value=i;
		plg[i]->next=NULL;
		for(int j=0;j<rand()%n;++j){
			plgtmp=new Link_graphic;
			plgtmp->value=rand()%n;
			plgtmp->next=NULL;
			add_vertex(plg[i],plgtmp);//添加结点
		}
	}
	for(int i=0;i<n;++i){
		plgtmp=plg[i];
		while(plgtmp){
			cout<<plgtmp->value<<" ";
			plgtmp=plgtmp->next;
		}
		cout<<endl;
	}
	delete_redundance(plg,n);
	cout<<endl<<endl;
	for(int i=0;i<n;++i){
		plgtmp=plg[i];
		while(plgtmp){
			cout<<plgtmp->value<<" ";
			plgtmp=plgtmp->next;
		}
		cout<<endl;
	}

	breadth_first_search(plg,4,n);//广度优先搜索

	for(int i=0;i<n;++i){
		delete[]plg[i];
	}
	delete[]plg;;
}
