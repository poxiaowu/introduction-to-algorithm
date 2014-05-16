#include <iostream>
#include <limits>
#include <map>
using namespace std;

typedef struct Vertex{//结点结构体
	char key;//结点值
	int distance;//结点的距离
	Vertex *parent;//结点父亲结点
}Vertex,*pVertex;

typedef struct Edge{//边结构体
	Vertex *src,*dst;
	int weight;//边权重
}Edge,*pEdge;

typedef struct Graphic{//图
	pVertex *V;
	pEdge *E;
}Graphic,*pGraphic;

typedef struct adj_list{//临接链表
	char ch;
	int weight;//存放边的权重值
	adj_list *next;
}adj_list,*pAdj_list;

pVertex make_set(int key)//初始化结点
{
	pVertex pv=new Vertex;
	pv->key=key;
	pv->parent=pv;
	pv->distance=numeric_limits<int>::max();//距离初始最大值
	return pv;
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

int extract_min(pVertex *pv,int& heap_size)//提取最小值
{
	int min=pv[0]->key;
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


map<char,pAdj_list> adjacent_link_list(pVertex *pv,pEdge *pe,int e_m,int n)//创建邻接链表
{
	pAdj_list *pal=new pAdj_list[n];
	map<char,pAdj_list>ma;
	for(int i=0;i<n;++i){
		pal[i]=new adj_list;
		pal[i]->ch=pv[i]->key;
		pal[i]->next=NULL;
		ma[pv[i]->key]=pal[i];
	}
	pAdj_list pt,pre,p_value;
	for(int i=0;i<e_m;++i){
		pre=ma[pe[i]->src->key];
		pt=ma[pe[i]->src->key]->next;
		while(pt){
			if(pt->ch==pe[i]->dst->key){
				break;
			}
			pre=pt;
			pt=pt->next;
		}
		if(pt==NULL){
			p_value=new adj_list;
			p_value->ch=pe[i]->dst->key;
			p_value->next=pre->next;
			pre->next=p_value;
			p_value->weight=pe[i]->weight;
		}

		pre=ma[pe[i]->dst->key];
		pt=pre->next;
		while(pt){
			if(pt->ch==pe[i]->src->key){
				break;
			}
			pre=pt;
			pt=pt->next;
		}
		if(pt==NULL){
			p_value=new adj_list;
			p_value->ch=pe[i]->src->key;
			p_value->next=pre->next;
			pre->next=p_value;
			p_value->weight=pe[i]->weight;
		}
	}
	return ma;
}

void MST_prim(pGraphic pg,map<char,pAdj_list> all,map<char,pVertex>ma,int v_n,int e_m,char c)//prim最小生成树算法
{
	int heap_size=v_n;//堆结点数
	pVertex pt=ma[c];
	pt->distance=0;
	heap_sort(pg->V,v_n);//堆排序

	for(int i=0;i<heap_size;++i){
		cout<<pg->V[i]->key<<"\t";
	}
	cout<<endl;

	pAdj_list pa;
	while(heap_size>0){
		char u=extract_min(pg->V,heap_size);//获取最短距离值
		if(ma[u]->parent->key!=ma[u]->key){		
			cout<<ma[u]->parent->key<<"\t"<<ma[u]->key<<"\t"<<ma[u]->distance<<endl;
		}
		pa=all[u]->next;
		while(pa){
			bool ex=true;
			int i=0;
			for(i=0;i<heap_size;++i){
				if(pa->ch==pg->V[i]->key){//检查元素是否在二叉堆中
					break;
				}
			}
			if(i==heap_size){//未找到元素
				ex=false;
			}
			if(ex &&  pa->weight < ma[pa->ch]->distance){
				ma[pa->ch]->parent=ma[u];
				ma[pa->ch]->distance=pa->weight;
				int i;
				for(i=0;i<heap_size;++i){
					if(pa->ch==pg->V[i]->key){//当然，此处可以使用更快的其他方法来进行定位
						break;
					}
				}
				heap_decrease_key(pg->V,i);//调整元素值
				/*for(int i=0;i<heap_size;++i){
					cout<<pg->V[i]->key<<"\t";
				}
				cout<<endl;*/
			}
			pa=pa->next;
		}
		//heap_sort(pg->V,heap_size);//调整堆,此处可以使用decrease_key函数操作
	/*	for(int i=0;i<heap_size;++i){
			cout<<pg->V[i]->key<<"\t";
		}
		cout<<endl;*/
	}
}



int main()
{
	int n=9;
	map<char,pVertex>ma;
	pVertex *pv=new pVertex[n];
	for(int i=0;i<n;++i){//生成结点
		pv[i]=make_set('a'+i);
		ma['a'+i]=pv[i];
	}
	int m=14;
	pEdge *pe=new pEdge[m];//生成边
	for(int i=0;i<m;++i){
		pe[i]=new Edge;
	}
	//创建边
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
	map<char,pAdj_list> all =adjacent_link_list(pv,pe,m,n);//生成一个邻接表

	for(int i=0;i<n;++i){//输出邻接链表
		pAdj_list pa=all[pv[i]->key];
		while(pa){
			cout<<pa->ch<<"\t";
			pa=pa->next;
		}
		cout<<endl;
	}
	cout<<"after prim:"<<endl;
	MST_prim(pg,all,ma,n,m,'a');

	map<char,pAdj_list>::iterator iter=all.begin();
	for(;iter!=all.end();++iter){
		delete iter->second;
	}
	map<char,pAdj_list>().swap(all);
	all.clear();
	
	map<char,pVertex>::iterator iter2=ma.begin();
	for(;iter2!=ma.end();++iter2){
		delete iter2->second;
	}
	map<char,pVertex>().swap(ma);
	ma.clear();
	for(int i=0;i<m;++i){
		delete pe[i];
	}
	delete pe;

	delete pg;
}
