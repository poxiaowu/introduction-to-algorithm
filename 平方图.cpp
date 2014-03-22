#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

typedef struct Link_graphic{
	int value;
	Link_graphic *next;
}Link_graphic,*pLink_graphic;

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

pLink_graphic * square_graphic(pLink_graphic *&plg,int n)//邻接矩阵的平方图
{
	pLink_graphic plg_t;
	pLink_graphic plg_copy;
	pLink_graphic pt;//临时存放临时的邻接表
	pLink_graphic pn;
	pLink_graphic *plgtmp=new pLink_graphic[n];//生成新的邻接图
	for(int i=0;i<n;++i){
		plgtmp[i]=new Link_graphic;
		plgtmp[i]->value=i;
		plgtmp[i]->next=NULL;
		plg_t=plg[i]->next;//原邻接表的第一个元素
		pt=plgtmp[i];
		while (plg_t){
			pn=plg[plg_t->value];
			while(pn){
				plg_copy=new Link_graphic;//生成新的结点
				plg_copy->value=pn->value;
				plg_copy->next=NULL;
				add_vertex(pt,plg_copy);
				pt=pt->next;
				pn=pn->next;
			}
			plg_t=plg_t->next;
		}
	}
	delete_redundance(plgtmp,n);
	return plgtmp;
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

	pLink_graphic *pt=square_graphic(plg,n);

	cout<<endl<<endl;
	for(int i=0;i<n;++i){
		plgtmp=pt[i];
		while(plgtmp){
			cout<<plgtmp->value<<" ";
			plgtmp=plgtmp->next;
		}
		cout<<endl;
	}

	for(int i=0;i<n;++i){
		delete[]plg[i];
		delete[]pt[i];
	}
	delete[]plg;
	delete[]pt;
}
