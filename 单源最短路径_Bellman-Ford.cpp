#include <iostream>
#include <limits>
using namespace std;

typedef struct vertex{//点
	char value;//结点的值
	int distance;//结点的初始距离
	vertex *parent;//结点的父亲结点
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

void initialize_single_source(pVertex *&pv,pVertex &ps,int n)//初始化所有结点的信息
{
	for(int i=0;i<n;++i){
		pv[i]->distance=numeric_limits<int>::max();
		pv[i]->parent=NULL;
	}
	ps->distance=0;	//ps作为初始结点，其距离值设置为0
}

void relax(pEdge &pe)//松弛操作
{
	if(pe->src->distance!=numeric_limits<int>::max()){
		if(pe->dst->distance > pe->src->distance+pe->weight){
			pe->dst->distance=pe->src->distance+pe->weight;
			pe->dst->parent=pe->src;
		}
	}
}

bool Bellman_Ford(pGraphic &pg,int edge_num,int n)//Bellman_Ford算法
{
	initialize_single_source(pg->V,pg->V[0],n);//初始化
	for(int i=0;i<edge_num-1;++i){
		for(int j=0;j<edge_num;++j){
			relax(pg->E[j]);
		}
	}
	for(int i=0;i<edge_num;++i){//判断是否有负权重环路
		if(pg->E[i]->dst->distance > pg->E[i]->src->distance + pg->E[i]->weight){
			return false;
		}
	}
	return true;
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
	int m=10;//10条边
	char va[5]={'s','t','x','y','z'};//5个顶点
	pVertex *pv=new pVertex[n];
	for(int i=0;i<n;++i){//初始化结点
		pv[i]=new vertex;
		pv[i]->value=va[i];
	}
	pEdge *pe=new pEdge[m];
	for(int i=0;i<m;++i){//初始化边
		pe[i]=new edge;
	}
	pe[0]->src=pv[0],pe[0]->dst=pv[1],pe[0]->weight=6;
	pe[1]->src=pv[0],pe[1]->dst=pv[3],pe[1]->weight=7;
	pe[2]->src=pv[1],pe[2]->dst=pv[2],pe[2]->weight=5;
	pe[3]->src=pv[2],pe[3]->dst=pv[1],pe[3]->weight=-2;
	pe[4]->src=pv[1],pe[4]->dst=pv[3],pe[4]->weight=8;
	pe[5]->src=pv[4],pe[5]->dst=pv[2],pe[5]->weight=7;
	pe[6]->src=pv[1],pe[6]->dst=pv[4],pe[6]->weight=-4;
	pe[7]->src=pv[3],pe[7]->dst=pv[2],pe[7]->weight=-3;
	pe[8]->src=pv[3],pe[8]->dst=pv[4],pe[8]->weight=9;
	pe[9]->src=pv[4],pe[9]->dst=pv[0],pe[9]->weight=2;

	for(int i=0;i<m;++i){
		cout<<pe[i]->src->value<<'\t'<<pe[i]->dst->value<<endl;
	}

	pGraphic pg=new Graphic;
	pg->V=pv;
	pg->E=pe;
	bool flag=Bellman_Ford(pg,m,n);//Bellman_Ford算法计算单源最短路径
	if(flag){
		print(pv,n);//打印结点信息
	}else{
		cout<<"there are negative weight loop."<<endl;
	}

	for(int i=0;i<n;++i){//删除结点
		delete pv[i];
	}
	for(int i=0;i<m;++i){//删除边
		delete pe[i];
	}
	delete pg;
}
