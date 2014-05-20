#include <iostream>
#include <limits>
using namespace std;

typedef struct vertex{//点
	char value;//结点的值
	int distance;//结点的初始距离
	vertex *parent;//结点的父亲结点
	int color;//设置结点颜色,0表示结点尚未被访问，1表示结点正在被访问，2表示结点已经被访问
	int d;//结点访问的开始时间
	int f;//结点访问的结束时间
	int index;//结点索引，存储当前结点属于第几个结点
}vertex,*pVertex;

typedef struct adj_list{//邻接链表
	pVertex ver;
	adj_list *next;
}adj_list,*pAdj_list;

typedef struct edge{//边
	pVertex src,dst;
	int weight;
}edge,*pEdge;

typedef struct Graphic{//图
	pVertex *V;
	pEdge *E;
}Graphic,*pGraphic;

int partition(pVertex *&pv,int low,int high)//根据结点访问时间f，对结点进行快速排序
{
	if(low<high){
		int p=low-1;
		pVertex pt=pv[high];
		pVertex ptmp;
		for(int i=low;i<high;++i){
			if(pv[i]->f > pt->f){
				++p;
				ptmp=pv[i];
				pv[i]=pv[p];
				pv[p]=ptmp;
			}
		}
		ptmp=pv[p+1];
		pv[p+1]=pv[high];
		pv[high]=ptmp;
		return p+1;	
	}
	return 0;
}

void quick_sort(pVertex *&pv,int low,int high)//快速排序
{
	if(low<high){
		int index=partition(pv,low,high);
		quick_sort(pv,low,index-1);
		quick_sort(pv,index+1,high);
	}
}

void DFS_visit(pAdj_list *&pal,int u,int &time)//深度优先遍历算法
{
	pal[u]->ver->d=time++;
	pal[u]->ver->color=1;//结点正在被访问
	pAdj_list pat=pal[u]->next;
	while(pat){
		if(pat->ver->color==0){
			pat->ver->parent=pal[u]->ver;// 设置父亲结点
			DFS_visit(pal,pat->ver->index,time);
		}
		pat=pat->next;
	}
	pal[u]->ver->color=2;
	pal[u]->ver->f=time++;
}


void DFS(pGraphic pg,pAdj_list *&pal,int n)//深度优先遍历
{
	for(int i=0;i<n;++i){
		pg->V[i]->color=0;
		pg->V[i]->parent=NULL;
	}
	int time=0;
	for(int i=0;i<n;++i){
		if(pg->V[i]->color==0){
			DFS_visit(pal,i,time);
		}
	}	
}
pAdj_list * build_adjacent_link_list(pGraphic pg,int n,int m)//建立邻接链表
{
	pAdj_list *pal=new pAdj_list[n];//根据结点个数建立邻接链表
	for(int i=0;i<n;++i){
		pal[i]=new adj_list;
		pal[i]->ver=pg->V[i];
		pal[i]->next=NULL;
	}
	pAdj_list ptmp;
	for(int i=0;i<m;++i){//创建邻接链表
		ptmp=new adj_list;
		ptmp->ver=pg->V[pg->E[i]->dst->index];
		ptmp->next=pal[pg->E[i]->src->index]->next;
		pal[pg->E[i]->src->index]->next=ptmp;
	}
	return pal;
}
void topological_sort(pGraphic pg,pAdj_list *&pal,int n)//拓扑排序
{
	DFS(pg,pal,n);//深度遍历
	quick_sort(pg->V,0,n-1);//快速排序
}

void initialize_single_source(pVertex *&pv,pVertex &ps,int n)//初始化所有结点的信息
{
	for(int i=0;i<n;++i){
		pv[i]->distance=numeric_limits<int>::max();
		pv[i]->parent=NULL;
	}
	ps->distance=0;	//ps作为初始结点，其距离值设置为0
}

void relax(pVertex &pu,pVertex &pv,int w)//松弛操作
{
	if(pu->distance!=numeric_limits<int>::max()){
		if(pv->distance > pu->distance+w){
			pv->distance= pu->distance+w;
			pv->parent=pu;
		}
	}
}

void DAG_shortest_paths(pGraphic pg,pAdj_list *&pal,pVertex ps,int **weight,int n)//有向无环图的单源最短路径问题
{
	topological_sort(pg,pal,n);//拓扑排序
	initialize_single_source(pg->V,ps,n);//结点初始化
	for(int i=0;i<n;++i){
		pAdj_list pt=pal[pg->V[i]->index]->next;
		while(pt){
			relax(pg->V[i],pg->V[pt->ver->index],weight[i][pt->ver->index]);
			pt=pt->next;
		}
	}
}


void print_edge_weight(pVertex pv)//打印最短路径信息
{
	if(pv){
		print_edge_weight(pv->parent);
		cout<<pv->value<<"-->";
	}
}
void print(pVertex *pv,int n)//打印最短路径信息
{
	for(int i=0;i<n;++i){
		print_edge_weight(pv[i]);
		cout<<pv[i]->distance<<endl;
	}
}

int main()
{
	int n=5;//5个顶点
	int m=8;//10条边
	char va[5]={'s','t','x','y','z'};//5个顶点
	pVertex *pv=new pVertex[n];
	for(int i=0;i<n;++i){//初始化结点
		pv[i]=new vertex;
		pv[i]->value=va[i];
		pv[i]->index=i;//结点索引值
	}
	pEdge *pe=new pEdge[m];
	for(int i=0;i<m;++i){//初始化边
		pe[i]=new edge;
	}
	pe[0]->src=pv[0],pe[0]->dst=pv[1],pe[0]->weight=2;
	pe[1]->src=pv[0],pe[1]->dst=pv[2],pe[1]->weight=6;
	pe[2]->src=pv[1],pe[2]->dst=pv[2],pe[2]->weight=7;
	pe[3]->src=pv[1],pe[3]->dst=pv[3],pe[3]->weight=4;
	pe[4]->src=pv[1],pe[4]->dst=pv[4],pe[4]->weight=2;
	pe[5]->src=pv[2],pe[5]->dst=pv[3],pe[5]->weight=-1;
	pe[6]->src=pv[2],pe[6]->dst=pv[4],pe[6]->weight=1;
	pe[7]->src=pv[3],pe[7]->dst=pv[4],pe[7]->weight=-2;

	int **weight=new int *[n];
	for(int i=0;i<n;++i){//结点权重
		weight[i]=new int [n];
		for(int j=0;j<n;++j){
			weight[i][j]=numeric_limits<int>::max();
		}
	}
	for(int i=0;i<m;++i){
		weight[pe[i]->src->index][pe[i]->dst->index]=pe[i]->weight;
	}

	pGraphic pg=new Graphic;
	pg->V=pv;
	pg->E=pe;
	
	pAdj_list *pal=build_adjacent_link_list(pg,n,m);//建立邻接链表
	cout<<"adjancent link list :"<<endl;
	for(int i=0;i<n;++i){
		pAdj_list pt=pal[i];
		while(pt){
			cout<<pt->ver->value<<"\t";
			pt=pt->next;
		}
		cout<<endl;
	}
	DAG_shortest_paths(pg,pal,pg->V[0],weight, n);

	cout<<"after topological sort :"<<endl;

	for(int i=0;i<n;++i){
		cout<<pv[i]->value<<"\t"<<pv[i]->d<<"\t"<<pv[i]->f<<endl;
	}
	
	cout<<"direct acyclic diagram shortest path : "<<endl;
	print(pg->V,n);

	for(int i=0;i<n;++i){//删除结点
		delete pv[i];
	}
	for(int i=0;i<m;++i){//删除边
		delete pe[i];
	}
	delete pg;
	for(int i=0;i<n;++i){//删除邻接链表		
		pAdj_list pt=pal[i];
		pAdj_list pnext=pt->next;
		while(pt){
			pnext=pt->next;
			delete pt;
			pt=pnext;
		}
	}
	for(int i=0;i<n;++i){
		delete weight[i];
	}
	delete weight;
}
