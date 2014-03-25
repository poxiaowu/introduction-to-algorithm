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

int breadth_first_search(pLink_graphic *&plg,int value,int n)//广度优先搜索,并返回距离最大的结点的下标索引值
{
	bool * visited=new bool[n];//设置数组标记
	int *dist=new int[n];//存储广度优先中的距离值
	for(int i=0;i<n;++i){
		visited[i]=false;
	}
	Queue *queue=new Queue;
	init(queue);//初始化队列
	enqueue(queue,value);//源结点如队列
	visited[value]=true;//已访问
	dist[value]=0;//初始的距离为0
	pLink_graphic pt;
	while (queue->front){//队列中存在元素
		pt=plg[queue->front->value]->next;
		while(pt){
			if(visited[pt->value]==false){//未访问则添加到队列
				enqueue(queue,pt->value);
				visited[pt->value]=true;
				dist[pt->value]=dist[queue->front->value]+1;//距离值加1
			}
			pt=pt->next;
		}
		cout<<queue->front->value<<" ";
		dequeue(queue);//父节点出队列		
	}	
	cout<<endl;
	delete[]visited;
	int max=0;
	int index=value;
	for(int i=0;i<n;++i){
		if(dist[i]>max){
			max=dist[i];
			index=i;
		}
	}
	delete[]dist;//删除距离矩阵
	return index;
}

int in_degree(pLink_graphic *&plg,int value,int n)//入度
{
	pLink_graphic plgtmp;
	int count=0;
	for(int i=0;i<n;++i){
		if(i!=value){
			plgtmp=plg[i]->next;
			while(plgtmp){
				if(plgtmp->value==value){
					count++;
				}
				plgtmp=plgtmp->next;
			}
		}
	}
	return count;
}
int out_degree(pLink_graphic *&plg,int value,int n)//出度
{
	pLink_graphic plgtmp=plg[value]->next;
	int count=0;
	while(plgtmp){
		++count;
		plgtmp=plgtmp->next;
	}
	return count;
}
bool vertify_isolated(pLink_graphic *&plg,int value,int n)//检查是否有孤立的点
{
	int count_out=out_degree(plg,value,n);
	int count_in=in_degree(plg,value,n);
	if(count_out+count_in==0)//孤立的点
		return true;
	return false;
}
void break_isolated(pLink_graphic *&plg,int n)//打破孤立的点
{
	int tmp1;//随机点
	pLink_graphic plgtmp;
	for (int i=0;i<n;++i){
		if(vertify_isolated(plg,i,n)){//检测是否有孤立的点
			while((tmp1=rand()%n)==i);//产生一个随机的点
			//增加出度
			if(rand()%2){
				plgtmp=new Link_graphic;
				plgtmp->value=tmp1;
				plgtmp->next=NULL;
				add_vertex(plg[i],plgtmp);
			}else{//添加入度
				plgtmp=new Link_graphic;
				plgtmp->value=i;
				plgtmp->next=NULL;
				add_vertex(plg[tmp1],plgtmp);
			}
			
		}
	}
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
	cout<<endl<<endl;
	break_isolated(plg,n);//检查是否有孤立点
	for(int i=0;i<n;++i){
		plgtmp=plg[i];
		while(plgtmp){
			cout<<plgtmp->value<<" ";
			plgtmp=plgtmp->next;
		}
		cout<<endl;
	}
	int value=rand()%n;//随机产生一个源结点
	int index1=breadth_first_search(plg,value,n);//广度优先搜索
	int index2=breadth_first_search(plg,index1,n);//第二次广度优先搜索，找出图的直径
	cout<<"the graphic's diameter is from "<<index1<<" to "<<index2<<endl;
	for(int i=0;i<n;++i){
		delete[]plg[i];
	}
	delete[]plg;;
}
