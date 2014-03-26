#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

typedef struct Link_graphic{//邻接表
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

void dfs_visit(pLink_graphic *&plg,int value,int *visited)//深度优先遍历
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

void topologic_dfs_visit(pLink_graphic *&plg,int value,bool *visited,int *dist,int &depth)//深度优先遍历
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
void topologic_depthth_first_search(pLink_graphic *&plg,int *dist,int n)//深度优先搜索,并返回距离最大的结点的下标索引值
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

void topological_sort(pLink_graphic *& plg,int n)//拓扑排序
{
	int *dist=new int[n];//记录拓扑长度
	for(int i=0;i<n;++i){
		dist[i]=0;
	}
	topologic_depthth_first_search(plg,dist,n);//深度优先遍历	
	for(int i=0;i<n;++i){
		cout<<dist[i]<<" ";
	}
	cout<<endl;
	delete [] dist;
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
	int n=5;
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
	directed_acyclic_graphs(plg,n);
	cout<<endl;
	cout<<"directed acyclic graphs"<<endl;
	for(int i=0;i<n;++i){
		plgtmp=plg[i];
		while(plgtmp){
			cout<<plgtmp->value<<" ";
			plgtmp=plgtmp->next;
		}
		cout<<endl;
	}
	cout<<"after topological sort"<<endl;
	topological_sort(plg,n);

	for(int i=0;i<n;++i){
		delete[]plg[i];
	}
	delete[]plg;;
}
