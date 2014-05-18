#include <iostream>
#include <limits>
using namespace std;

typedef struct adj_list{//邻接链表
	char value;
	adj_list *next;
}adj_list,*pAdj_list;

typedef struct queue_list{//队列列表
	pAdj_list pal;
	queue_list *next;
}queue_list,*pQueue_list;
typedef struct queue{//队列
	queue_list *front;
	queue_list *tail;
}queue,*pQueue;

void init(pQueue &pq)
{
	pq=new queue;
	pq->front=NULL;
	pq->tail=NULL;
}
void enqueue(pQueue &pq,pAdj_list pal)//入队列
{
	pQueue_list ql=new queue_list;
	ql->pal=pal;
	if(pq->front==NULL){
		pq->front=ql;
	}else{
		pq->tail->next=ql;
	}
	pq->tail=ql;	
}

pAdj_list dequeue(pQueue &pq){
	pAdj_list pal=pq->front->pal;
	if(pq->front==pq->tail){
		pq->front=NULL;
		pq->tail=NULL;
	}else{
		pq->front=pq->front->next;
	}
	return pal;
}


void prim(int **matrix,int **edge_weight,int index,int *father,int n)//二维矩阵表示的prim算法
{
	int *weight=new int[n];
	for(int i=0;i<n;++i){
		weight[i]=edge_weight[index][i];
		father[i]=index;//父亲结点
	}
	weight[index]=0;
	int pos;
	for(int i=0;i<n-1;++i){
		int smallest=numeric_limits<int>::max();
		for(int j=0;j<n;++j){
			if(weight[j] && weight[j]<smallest){
				pos=j;
				smallest=weight[j];
			}			
		}
		weight[pos]=0;//将权重值设置为0，下次将以该结点作为初始结点
		for(int i=0;i<n;++i){//更新weight数组的值
			if(i!=pos && edge_weight[pos][i]<weight[i]){
				weight[i]=edge_weight[pos][i];
				father[i]=pos;//设置父亲结点
			}
		}
	}
	delete [] weight;
}

pAdj_list * build_adjancent_list(int *father,int root,char *data,int n)
{
	pAdj_list *pal=new pAdj_list[n];
	for(int i=0;i<n;++i){//初始化邻接链表
		pal[i]=new adj_list;
		pal[i]->value=data[i];
		pal[i]->next=NULL;
	}
	pAdj_list ptmp;
	for(int i=0;i<n;++i){//根据father数组构建邻接链表
		if(i!=root){
			ptmp=new adj_list;
			ptmp->value=data[i];
			ptmp->next=pal[father[i]]->next;
			pal[father[i]]->next=ptmp;

			ptmp=new adj_list;
			ptmp->value=data[father[i]];
			ptmp->next=pal[i]->next;
			pal[i]->next=ptmp;
		}
	}
	return pal;
}
void print_adj_list(pAdj_list *pal,int n)
{
	pAdj_list pt;
	for(int i=0;i<n;++i){
		pt=pal[i];
		cout<<pt->value<<" : ";
		pt=pt->next;
		while(pt){
			cout<<pt->value<<" ";
			pt=pt->next;
		}
		cout<<endl;
	}
}

int **BFS_fill_max(pAdj_list *pal,int **edge_weight,int n)//广度优先求取最小生成树中边的最大权重边
{
	int **maxtable=new int *[n];
	int **edge=new int*[n];
	pQueue pq=new queue;
	init(pq);//初始化队列
	for(int i=0;i<n;++i){
		maxtable[i]=new int [n];
		edge[i]=new int [n];
		for(int j=0;j<n;++j){
			edge[i][j]=0;
		}
	}
	pAdj_list ptmp,px;
	int v,t;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			maxtable[i][j]=numeric_limits<int>::min();
		}
		enqueue(pq,pal[i]);
		while(pq->front){//队列非空
			px=dequeue(pq);
			ptmp=px->next;
			t=px->value-'a';
			while(ptmp){
				v=ptmp->value-'a';
				if(maxtable[i][v]==numeric_limits<int>::min() && i<v){
					if(t==i || edge_weight[t][v] > maxtable[i][t]){
						maxtable[i][v]=edge_weight[t][v];
						edge[i][v]=v;

						maxtable[v][i]=edge_weight[t][v];//反向的时候也具有相同的权重和边
						edge[v][i]=edge[i][v];
					}else{
						maxtable[i][v]=maxtable[i][t];
						edge[i][v]=edge[i][t];

						maxtable[v][i]=edge_weight[i][t];//反向的时候也具有相同的权重和边
						edge[v][i]=edge[i][v];
					}
					enqueue(pq,pal[ptmp->value-'a']);
				}	
				ptmp=ptmp->next;
			}
		}
	}
	return edge;
}

void print_max_edge(char*data,int *father,int **edge,int n)//打印最大边
{
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(edge[i][j]){
				cout<<"the max edge of edge "<<data[i]<<"->"<<data[j]<<" is : "<<data[father[edge[i][j]]]<<"->"<<data[edge[i][j]]<<endl;
			}
		}
	}
}

int main()
{
	int n=9;
	int **matrix=new int *[n];//存放结点之间的链接关系
	int **edge_weight=new int*[n];
	for(int i=0;i<n;++i){
		matrix[i]=new int [n];
		edge_weight[i]=new int [n];
		for(int j=0;j<n;++j){
			matrix[i][j]=0;
			edge_weight[i][j]=numeric_limits<int>::max();
		}
	}
	char *data=new char[n];//存放数据值
	for(int i=0;i<n;++i){
		data[i]='a'+i;
	}
	matrix[0][1]=1,matrix[0][7]=1,
	matrix[1][7]=1,matrix[1][2]=1,
	matrix[2][8]=1,matrix[7][8]=1,
	matrix[2][5]=1,matrix[6][7]=1,
	matrix[6][8]=1,matrix[2][3]=1,
	matrix[3][4]=1,matrix[3][5]=1,
	matrix[4][5]=1,matrix[5][6]=1;

	edge_weight[0][1]=4,edge_weight[0][7]=8,
	edge_weight[1][7]=11,edge_weight[1][2]=8,
	edge_weight[2][8]=2,edge_weight[7][8]=7,
	edge_weight[2][5]=4,edge_weight[6][7]=1,
	edge_weight[6][8]=6,edge_weight[2][3]=7,
	edge_weight[3][4]=9,edge_weight[3][5]=14,
	edge_weight[4][5]=10,edge_weight[5][6]=2;

	for(int i=0;i<n;++i){//创建无向图
		for(int j=0;j<n;++j){
			if(matrix[i][j]){
				matrix[j][i]=1;
				edge_weight[j][i]=edge_weight[i][j];
			}
		}
	}

	int *father=new int[n];//存放父亲结点的索引
	for(int i=0;i<n;++i){
		father[i]=i;
	}
	prim(matrix,edge_weight,0,father,n);//0表示最小生成树的开始结点

	for(int i=0;i<n;++i){
		if(father[i]!=i){
			cout<<data[i]<<"\t"<<data[father[i]]<<"\t"<<edge_weight[i][father[i]]<<endl;
		}
	}
	pAdj_list *pal=build_adjancent_list(father,0,data,n);//建立最小生成树的邻接链表
	print_adj_list(pal,n);//输出邻接链表
	int **edge=BFS_fill_max(pal,edge_weight,n);
	print_max_edge(data,father,edge,n);	

	for(int i=0;i<n;++i){
		delete[]matrix[i];
		delete[]edge_weight[i];
		pAdj_list pa=pal[i];
		pAdj_list ptm;
		while(pa){
			ptm=pa;
			pa=pa->next;
			delete ptm;
		}
		delete [] edge[i];
	}
	delete []matrix;
	delete [] edge_weight;
	delete []data;
	delete [] father;
	delete [] edge;
}
