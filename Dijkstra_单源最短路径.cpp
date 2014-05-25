#include <iostream>
#include <limits>
using namespace std;

typedef struct vertex{//点
	char value;//结点的值
	int distance;//结点的初始距离
	vertex *parent;//结点的父亲结点
	int index;
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

void min_heap(pVertex *pv,int i,int n)//最小堆
{
	int l=2*i+1;//左结点
	int r=2*i+2;//右结点
	int smallest=i;
	if(l<n && pv[i]->distance > pv[l]->distance){
		smallest=l;
	}
	if(r<n && pv[smallest]->distance > pv[r]->distance){
		smallest=r;
	}
	if(smallest != i){
		pVertex ph=pv[i];
		pv[i]=pv[smallest];
		pv[smallest]=ph;
		min_heap(pv,smallest,n);
	}
}

void heap_sort(pVertex * pv,int n)//堆排序
{//pv_root代表创建最小堆的时候的根结点
	for(int i=n/2-1;i>=0;--i){
		min_heap(pv,i,n);
	}			
}

pVertex extract_min(pVertex *pv,int& heap_size)//提取最小值的索引值
{
	pVertex min=pv[0];
	pv[0]=pv[heap_size-1];
	--heap_size;
	min_heap(pv,0,heap_size);
	return min;
}

void heap_decrease_key(pVertex *pv,int i)//元素值发生改变，调整该元素值
{
	while(i>=0 && pv[i]->distance<pv[(i-1)/2]->distance){
		pVertex ph=pv[i];
		pv[i]=pv[(i-1)/2];
		pv[(i-1)/2]=ph;
		i=(i-1)/2;
	}
}

pAdj_list Dijkstra(pGraphic pg,pVertex ps,pAdj_list *pal,int **weight,int n)//Dijkstra最短路径
{
	initialize_single_source(pg->V,ps,n);
	heap_sort(pg->V,n);
	int heap_size=n;

	pAdj_list palRes=NULL,palNode;
	pAdj_list pos;

	while(heap_size!=0){
		pVertex pver=extract_min(pg->V,heap_size);
		if(palRes==NULL){//链表为空
			palNode=new adj_list;
			palNode->ver=pver;
			palNode->next=NULL;
			pos=palNode;
			palRes=palNode;//链表头结点
		}else{
			palNode=new adj_list;
			palNode->ver=pver;
			palNode->next=NULL;
			pos->next=palNode;
			pos=palNode;
		}
		pAdj_list pat=pal[pver->index]->next;
		while(pat){
			relax(pver,pat->ver,weight[pver->index][pat->ver->index]);
			int i=0;
			for(i=0;i<heap_size;++i){
				if(pg->V[i]==pat->ver){
					break;
				}
			}
			heap_decrease_key(pg->V,i);
			pat=pat->next;
		}
		
	}

	return palRes;
}

void print(pAdj_list pal,int n)//打印最短路径信息
{
	for(int i=0;i<n;++i){
		cout<<pal->ver->value<<" ";
		pal=pal->next;
	}
	cout<<endl;
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
		pv[i]->index=i;
	}
	pEdge *pe=new pEdge[m];
	for(int i=0;i<m;++i){//初始化边
		pe[i]=new edge;
	}
	pe[0]->src=pv[0],pe[0]->dst=pv[1],pe[0]->weight=10;
	pe[1]->src=pv[0],pe[1]->dst=pv[3],pe[1]->weight=5;
	pe[2]->src=pv[1],pe[2]->dst=pv[2],pe[2]->weight=1;
	pe[3]->src=pv[2],pe[3]->dst=pv[4],pe[3]->weight=4;
	pe[4]->src=pv[1],pe[4]->dst=pv[3],pe[4]->weight=2;
	pe[5]->src=pv[4],pe[5]->dst=pv[2],pe[5]->weight=6;
	pe[6]->src=pv[3],pe[6]->dst=pv[1],pe[6]->weight=3;
	pe[7]->src=pv[3],pe[7]->dst=pv[2],pe[7]->weight=9;
	pe[8]->src=pv[3],pe[8]->dst=pv[4],pe[8]->weight=2;
	pe[9]->src=pv[4],pe[9]->dst=pv[0],pe[9]->weight=7;

	for(int i=0;i<m;++i){
		cout<<pe[i]->src->value<<'\t'<<pe[i]->dst->value<<endl;
	}

	pGraphic pg=new Graphic;
	pg->V=pv;
	pg->E=pe;

	int **weight=new int *[n];
	for(int i=0;i<n;++i){//结点权重
		weight[i]=new int [n];
		for(int j=0;j<n;++j){
			weight[i][j]=numeric_limits<int>::max();
		}
	}
	weight[0][1]=10,weight[0][3]=5;
	weight[1][2]=1,weight[1][3]=2;
	weight[3][1]=3,weight[3][4]=2;
	weight[2][4]=4,weight[4][2]=6;
	weight[3][2]=9,weight[4][0]=7;


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
	pAdj_list palRes=Dijkstra(pg,pv[0],pal,weight,n);
	cout<<"Dijkstra shortest path : "<<endl;
	print(palRes,n);

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
		pAdj_list pt=palRes;
		while(palRes){
			pt=palRes;
			palRes=palRes->next;
			delete pt->ver;
			delete pt;
		}
	}
	for(int i=0;i<n;++i){
		delete []weight[i];
	}
	delete []weight;
}
