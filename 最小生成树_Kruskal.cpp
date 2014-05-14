#include <iostream>
using namespace std;

typedef struct Vertex{//结点结构体
	char key;
	Vertex *parent;
}Vertex,*pVertex;

typedef struct Edge{//边结构体
	Vertex *src,*dst;
	int weight;
}Edge,*pEdge;

typedef struct Graphic{//图
	pVertex *V;
	pEdge *E;
}Graphic,*pGraphic;

typedef struct edge_list{
	pEdge edge;
	edge_list *next;
}edge_list,*pedge_list;

int partion(pEdge * pe,int low,int high)//快速排序
{
	if(low<high){
		pEdge pte=pe[high];
		Edge ptmp;
		int p=low-1;
		for(int i=low;i<high;++i){
			if(pe[i]->weight<pte->weight){
				p++;
				ptmp=*pe[i];
				*pe[i]=*pe[p];
				*pe[p]=ptmp;
			}
		}
		ptmp=*pe[p+1];
		*pe[p+1]=*pte;
		*pte=ptmp;
		return p+1;
	}
	return 0;
}

void quick_sort(pEdge * pe,int low,int high)//快速排序
{
	if(low<high){
		int index=partion(pe,low,high);
		quick_sort(pe,low,index-1);
		quick_sort(pe,index+1,high);
	}	
}

pVertex make_set(int key)
{
	pVertex pv=new Vertex;
	pv->key=key;
	pv->parent=pv;
	return pv;
}

pVertex find_set(pVertex pv)//路径压缩
{
	if(pv->parent!=pv){
		pv->parent=find_set(pv->parent);
	}
	return pv->parent;
}

void union_set(pVertex &pvx,pVertex &pvy)//合并
{
	pvy->parent=pvx;
}


pedge_list MST_Kruskal(pGraphic pg,int v_n,int e_m)//kruskal最小生成树算法
{
	quick_sort(pg->E,0,e_m-1);//按照边的权重递增的方式排序

	for(int i=0;i<e_m;++i){
		cout<<pg->E[i]->src->key<<"\t"<<pg->E[i]->dst->key<<"\t"<<pg->E[i]->weight<<endl;
	}
	cout<<endl;

	pedge_list pel=new edge_list;
	pel->edge=NULL;
	pedge_list ptmp;

	for(int i=0;i<e_m;++i){
		pVertex pv1=find_set(pg->E[i]->src);
		pVertex pv2=find_set(pg->E[i]->dst);
		if(pv1!=pv2){
			union_set(pv1,pv2);
			if(pel->edge==NULL){
				pel->edge=pg->E[i];
				pel->next=NULL;
			}else{
				ptmp=new edge_list;
				ptmp->edge=pg->E[i];
				ptmp->next=pel;
				pel=ptmp;
			}
		}
	}
	return pel;	
}


int main()
{
	int n=9;
	pVertex *pv=new pVertex[n];
	for(int i=0;i<n;++i){//生成结点
		pv[i]=make_set('a'+i);
	}
	int m=14;
	pEdge *pe=new pEdge[m];//生成边
	for(int i=0;i<m;++i){
		pe[i]=new Edge;
	}

	pe[0]->src=pv[0],pe[0]->dst=pv[1],pe[0]->weight=4;
	pe[1]->src=pv[0],pe[1]->dst=pv[7],pe[1]->weight=8;
	pe[2]->src=pv[1],pe[2]->dst=pv[7],pe[2]->weight=11;
	pe[3]->src=pv[1],pe[3]->dst=pv[2],pe[3]->weight=8;

	pe[4]->src=pv[2],pe[4]->dst=pv[8],pe[4]->weight=2;
	pe[5]->src=pv[8],pe[5]->dst=pv[7],pe[5]->weight=7;
	pe[6]->src=pv[8],pe[6]->dst=pv[6],pe[6]->weight=6;
	pe[7]->src=pv[2],pe[7]->dst=pv[5],pe[7]->weight=4;
	pe[8]->src=pv[5],pe[8]->dst=pv[6],pe[8]->weight=2;
	pe[9]->src=pv[6],pe[9]->dst=pv[7],pe[9]->weight=1;
	pe[10]->src=pv[3],pe[10]->dst=pv[5],pe[10]->weight=14;	
	pe[11]->src=pv[3],pe[11]->dst=pv[4],pe[11]->weight=9;
	pe[12]->src=pv[4],pe[12]->dst=pv[5],pe[12]->weight=10;
	pe[13]->src=pv[2],pe[13]->dst=pv[3],pe[13]->weight=7;	

	pGraphic pg=new Graphic;
	pg->V=pv;
	pg->E=pe;	
	pedge_list pel=MST_Kruskal(pg,n,m);
	cout<<"after Kruskal:"<<endl;
	while(pel){
		cout<<pel->edge->src->key<<'\t'<<pel->edge->dst->key<<"\t"<<pel->edge->weight<<endl;
		pel=pel->next;
	}
	for(int i=0;i<n;++i){
		delete pv[i];
	}
	delete pv;
	for(int i=0;i<m;++i){
		delete pe[i];
	}
	delete pe;	
}
