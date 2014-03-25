#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

typedef struct Link_graphic{//邻接表
	int value;
	Link_graphic *next;
}Link_graphic,*pLink_graphic;

typedef struct Link_list{//链表
	int value;
	Link_list *next;
}Link_list,*pLink_list;

typedef struct Stack{
	Link_list *top;//栈顶元素
}Stack;

void init(Stack *&stack)//初始化栈
{
	//stack=NULL;
	stack->top=NULL;//初始为空
}
pLink_list pop(Stack *&stack)
{
	if(stack->top){
		pLink_list pl=stack->top;
		stack->top=stack->top->next;
		return pl;//返回节点
	}
	return NULL;
}
void push(Stack *&stack,int value)//入栈
{
		pLink_list pl=new Link_list;
		pl->value=value;
		pl->next=stack->top;
		stack->top=pl;
}
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

void dfs_visit(pLink_graphic *&plg,int value,bool *visited)//深度优先遍历
{
	visited[value]=true;
	cout<<value<<" ";
	pLink_graphic plgtmp=plg[value]->next;
	while(plgtmp){
		if(visited[plgtmp->value]==false){
			dfs_visit(plg,plgtmp->value,visited);
		}
		plgtmp=plgtmp->next;
	}
}
void depthth_first_search(pLink_graphic *&plg,int n)//深度优先搜索,并返回距离最大的结点的下标索引值
{
	bool *visited=new bool[n];
	for(int i=0;i<n;++i){
		visited[i]=false;//标记为假
	}
	pLink_graphic plgtmp;
	for(int i=0;i<n;++i){//对每个点都需要进行深度遍历
		plgtmp=plg[i];		
		if(visited[plgtmp->value]==false){
			dfs_visit(plg,i,visited);//深度优先遍历
		}
	}
}

void depthth_first_search_stack(pLink_graphic *&plg,int n)//利用堆栈实现深度优先搜索,并返回距离最大的结点的下标索引值
{
	bool *visited=new bool[n];
	for(int i=0;i<n;++i){
		visited[i]=false;//标记为假
	}
	pLink_graphic plgtmp;
	pLink_list plt;
	Stack *stack=new Stack;//声明栈
	init(stack);//初始化栈
	for(int i=0;i<n;++i){//对每个点都需要进行深度遍历
		plgtmp=plg[i];		
		if(visited[plgtmp->value]==false){//该元素尚未被访问
			push(stack,plgtmp->value);
			visited[plgtmp->value]=true;
		}
		while (stack->top){
			plt=pop(stack);
			cout<<plt->value<<" ";
			plgtmp=plg[plt->value]->next;
			delete plt;
			while(plgtmp ){//有边存在
				if(plgtmp && visited[plgtmp->value]==false){
					push(stack,plgtmp->value);//将下一个元素放入栈
					visited[plgtmp->value]=true;//修改访问标记为真
				}
				plgtmp=plgtmp->next;			
			}
		}			
	}
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
	int n=1000;
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
	depthth_first_search(plg,n);
	cout<<endl;
	depthth_first_search_stack(plg,n);
	cout<<endl;
	//int index1=breadth_first_search(plg,value,n);//广度优先搜索
	//int index2=breadth_first_search(plg,index1,n);//第二次广度优先搜索，找出图的直径
	//cout<<"the graphic's diameter is from "<<index1<<" to "<<index2<<endl;
	for(int i=0;i<n;++i){
		delete[]plg[i];
	}
	delete[]plg;;
}
