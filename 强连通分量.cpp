#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

typedef struct Link_graphic{//邻接表
	int value;
	Link_graphic *next;
}Link_graphic,*pLink_graphic;

typedef struct Queue{//队列
	Link_graphic *front,*tail;//头尾结点指针
}Queue;

void init(Queue *&queue)//队列初始化
{
	queue->front=NULL;
	queue->tail=NULL;
}
void enqueue(Queue *& queue,int value)//入队列操作
{
	if(queue->front==NULL && queue->tail==NULL){//当队列中还没有元素的时候
		pLink_graphic ls=new Link_graphic;
		ls->value=value;
		ls->next=NULL;
		queue->front=ls;
		queue->tail=ls;
	}else{
		pLink_graphic ls=new Link_graphic;
		ls->value=value;
		ls->next=NULL;
		queue->tail->next=ls;
		queue->tail=ls;
	}
}

void dequeue(Queue *&queue)//出队列操作
{
	if(queue->front){
		pLink_graphic pt=queue->front;
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

void dfs_visit(pLink_graphic *&plg,int value,int *visited)//深度优先遍历,创建有向无环图
{
	visited[value]=1;//将当前结点标记为正在访问
	pLink_graphic plgtmp=plg[value]->next;
	while(plgtmp){
		if(visited[plgtmp->value]==0){//该结点尚未被访问
			dfs_visit(plg,plgtmp->value,visited);
			plgtmp=plgtmp->next;
		}else if(visited[plgtmp->value]==1){//当前是一条后向边,应该删除该条边
			pLink_graphic plt=plg[value]->next;
			pLink_graphic pltpre=plg[value];
			while(plt->value!=plgtmp->value){
				pltpre=plt;
				plt=plt->next;
			}
			pltpre->next=plt->next;
			plgtmp=plt->next;//指向下一个结点
			delete plt;//删除该结点
		}else{//该结点已经被访问，前向边
			plgtmp=plgtmp->next;
		}		
	}
	visited[value]=2;//将当前边标记为已经访问结束
}

void directed_acyclic_graphs(pLink_graphic *&plg,int n)//有向无环图
{
	int *visited=new int[n];//标记数组
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			visited[j]=0;//将所有结点标记为尚未访问
		}
		dfs_visit(plg,i,visited);//深度优先遍历
	}	
}

void topologic_dfs_visit(pLink_graphic *&plg,int value,bool *visited,int *dist,int &depth)//深度优先遍历,拓扑排序
{
	visited[value]=true;	
	depth=depth+1;
	pLink_graphic plgtmp=plg[value]->next;
	while(plgtmp){
		if(visited[plgtmp->value]==false){
			topologic_dfs_visit(plg,plgtmp->value,visited,dist,depth);
		}
		plgtmp=plgtmp->next;
	}
	depth=depth+1;
	dist[value]=depth;//更新距离值
}
void topologic_depth_first_search(pLink_graphic *&plg,int *dist,int n)//深度优先搜索,并返回距离最大的结点的下标索引值，拓扑排序
{
	bool *visited=new bool[n];
	for(int i=0;i<n;++i){
		visited[i]=false;//标记为假
	}
	pLink_graphic plgtmp;
	int depth=0;//初始的深度值为0
	for(int i=0;i<n;++i){//对每个点都需要进行深度遍历
		plgtmp=plg[i];		
		if(visited[plgtmp->value]==false){
			topologic_dfs_visit(plg,i,visited,dist,depth);//深度优先遍历
		}
	}
}

void topological_sort(pLink_graphic *& plg,int *dist,int n)//拓扑排序
{
	//int *dist=new int[n];//记录拓扑长度
	for(int i=0;i<n;++i){
		dist[i]=0;
	}
	topologic_depth_first_search(plg,dist,n);//深度优先遍历	
	for(int i=0;i<n;++i){
		cout<<dist[i]<<" ";
	}
	cout<<endl;
	//delete [] dist;
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
void topologic_sort_iterator(pLink_graphic *&plg,int n)//另一种，迭代方式的拓扑排序
{
	int *indegree=new int[n];//in_degree数组
	Queue *queue=new Queue;
	init(queue);
	for(int i=0;i<n;++i){
		indegree[i]=in_degree(plg,i,n);//计算每个点的入度
		if(indegree[i]==0){
			enqueue(queue,i);//如果该点的入度为0，则将其加入队列
		}
	}
	while(queue->front){//队列非空,将front元素出队列，并将与其想连的元素的入度减少1
		pLink_graphic plt=plg[queue->front->value]->next;
		while (plt){//与queue->front想连的元素的入度值都要减少1
			indegree[plt->value]--;
			if(indegree[plt->value]==0){
				enqueue(queue,plt->value);
			}
			plt=plt->next;
		}
		cout<<queue->front->value<<" ";
		dequeue(queue);// 弹出队列首元素
	}
	for(int i=0;i<n;++i){
		if(indegree[i]!=0){
			cout<<"there is a cycle..."<<endl;
			return;
		}
	}
	delete []indegree;
	delete queue;
}

void Link_graphic_transpose(pLink_graphic *& plg,pLink_graphic *&plgtrans,int n)//图的转置，邻接链表
{
	pLink_graphic plgt;//临时存储
	pLink_graphic plgtmp;
	for(int i=0;i<n;++i){
		plgt=plg[i]->next;
		while (plgt){
			plgtmp=new Link_graphic;
			plgtmp->value=i;
			plgtmp->next=NULL;
			add_vertex(plgtrans[plgt->value],plgtmp);//添加结点到转置的邻接链表
			plgt=plgt->next;//下一个元素
		}
	}
}

void strongly_connected_components(pLink_graphic *&plg,int n)//强连通分量
{
	int *dist=new int[n];
	topological_sort(plg,dist,n);
	pLink_graphic *plgtranspose=new pLink_graphic[n];//转置的邻接链表初始化
	for(int i=0;i<n;++i){
		plgtranspose[i]=new Link_graphic;
		plgtranspose[i]->value=i;
		plgtranspose[i]->next=NULL;
	}
	Link_graphic_transpose(plg,plgtranspose,n);//转置
	int *dec=new int[2*n+1];//深度优先遍历的时间数组会使用2*n+1个空间来存储
	for(int i=0;i<2*n+1;i++){
		dec[i]=-1;//初始值为-1
	}
	for(int i=0;i<n;++i){
		dec[dist[i]]=i;//值和下标对调
	}
	bool *visited=new bool[n];
	for(int i=0;i<n;++i){
		visited[i]=false;//初始都未访问
	}
	pLink_graphic plgtmp;
	for(int i=2*n;i>=0;--i){
		if(dec[i]>=0 && visited[dec[i]]==false){//该元素尚未访问，
			plgtmp=plgtranspose[dec[i]];//该连通分量的第一个元素，也是该连通分量里时间最大的元素
			cout<<"( ";//打印一个括号
			while (plgtmp && visited[plgtmp->value]==false){
				cout<<plgtmp->value<<" ";
				visited[plgtmp->value]=true;//重置访问标记
				plgtmp=plgtmp->next;
			}
			cout<<") ";			
		}
	}
	cout<<endl;
	delete []dist;	
	delete []dec;
	delete [] visited;
	for(int i=0;i<n;++i){
		delete[]plgtranspose[i];
	}
	delete[]plgtranspose;
}

int main()
{
	srand((unsigned)time(NULL));
	int n=50;
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
	cout<<"initial values"<<endl;
	for(int i=0;i<n;++i){
		plgtmp=plg[i];
		while(plgtmp){
			cout<<plgtmp->value<<" ";
			plgtmp=plgtmp->next;
		}
		cout<<endl;
	}
	delete_redundance(plg,n);
	cout<<"after delete redundant"<<endl;
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
	cout<<"after break isolated"<<endl;
	for(int i=0;i<n;++i){
		plgtmp=plg[i];
		while(plgtmp){
			cout<<plgtmp->value<<" ";
			plgtmp=plgtmp->next;
		}
		cout<<endl;
	}
	//强连通分量图需要有向有环图，所以，不需要生成有向无环图
	/*directed_acyclic_graphs(plg,n);
	cout<<endl;
	cout<<"directed acyclic graphs"<<endl;
	for(int i=0;i<n;++i){
		plgtmp=plg[i];
		while(plgtmp){
			cout<<plgtmp->value<<" ";
			plgtmp=plgtmp->next;
		}
		cout<<endl;
	}*/
	cout<<"after recursive topological sort"<<endl;
	int *dist=new int[n];
	topological_sort(plg,dist,n);
	delete []dist;
	cout<<endl;

	cout<<"after iterator topological sort"<<endl;
	topologic_sort_iterator(plg,n);
	cout<<endl;
	strongly_connected_components(plg,n);//强连通分量	

	for(int i=0;i<n;++i){
		delete[]plg[i];
	}
	delete[]plg;
}
