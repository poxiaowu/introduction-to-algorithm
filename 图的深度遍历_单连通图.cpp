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

bool dfs_visit(pLink_graphic *&plg,int value,int *visited)//深度优先遍历
{
	visited[value]=1;//将当前结点标记为正在访问
	pLink_graphic plgtmp=plg[value]->next;
	//bool flag=true;
	while(plgtmp){
		if(visited[plgtmp->value]==0){//该结点尚未被访问
			if(dfs_visit(plg,plgtmp->value,visited)==false){
				//flag=false;
				return false;
			}
		}else if(visited[plgtmp->value]==2){//当前是一条前向边或者横向边
			cout<<"this is not a singly connected graphic."<<endl;
			//flag=false;
			return false;
		}
		plgtmp=plgtmp->next;
	}
	visited[value]=2;//将当前边标记为已经访问结束
	return true;
}

void singly_connectd(pLink_graphic *&plg,int n)//判断是否是单连通
{
	int *visited=new int[n];//判断连通与否，需要用到2种状态，0表示尚未被访问，1表示正在被访问，尚未回溯结束，2表示已经被访问并已结束
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){//对每个定点的时候都要进行初始化
			visited[j]=0;//初始都标记为未被访问
		}
		if(dfs_visit(plg,i,visited)==false){//若为非单连通，则退出
			delete [] visited;
			return;//如果发现非单连通，直接退出
		}
	}
	delete [] visited;
	cout<<"this is a singly connected graphic."<<endl;//所有结点访问完成后都未发现违例情况
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
	cout<<endl<<endl;
	break_isolated(plg,n);//检查是否有孤立点
	//delete_redundance(plg,n);
	for(int i=0;i<n;++i){
		plgtmp=plg[i];
		while(plgtmp){
			cout<<plgtmp->value<<" ";
			plgtmp=plgtmp->next;
		}
		cout<<endl;
	}
	int value=rand()%n;//随机产生一个源结点
	singly_connectd(plg,n);
	cout<<endl;

	for(int i=0;i<n;++i){
		delete[]plg[i];
	}
	delete[]plg;;
}
