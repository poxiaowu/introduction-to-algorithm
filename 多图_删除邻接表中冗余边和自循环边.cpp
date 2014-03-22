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

int main()
{
	srand((unsigned)time(NULL));
	int n=20;
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
	for(int i=0;i<n;++i){
		delete[]plg[i];
	}
	delete[]plg;
}
