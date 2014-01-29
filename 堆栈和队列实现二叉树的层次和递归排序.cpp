#include<iostream>
#include <limits>
#include <ctime>
using namespace std;

typedef struct node{//二叉树节点
	int value;
	node *left;
	node *right;
}node,*pnode;

typedef struct list{//队列的基本结构
	pnode pn;
	list *next;
}list,*plist;

typedef struct queue{//层次遍历时存储节点
	list *head;
	list *tail;
}queue,*pqueue;

typedef struct stack{//栈-模拟递归遍历
	list *top;
}stack,*pstack;

void build_binary_tree(pnode &pn,int depth,int maxDep)//创建一个二叉树
{
	if(depth<maxDep){
		//创建根节点
		pn=new node;
		pn->value=rand()%101-50;
		pn->left=NULL;
		pn->right=NULL;
		cout<<pn->value<<"\t";
		
		build_binary_tree(pn->left,depth+1,maxDep);
		build_binary_tree(pn->right,depth+1,maxDep);
	}
}

void travel_recursive_binary_tree(pnode pn)//递归遍历二叉树
{
	if(pn!=NULL){
		cout<<pn->value<<"\t";
		travel_recursive_binary_tree(pn->left);
		travel_recursive_binary_tree(pn->right);
	}
}

void travel_stack_binary_tree(pnode pn)//利用堆栈模拟递归遍历
{
	if(pn!=NULL){
		pstack ps=new stack;//栈
		plist pl;//链表
		ps->top=NULL;
		while(pn||ps->top){			
			if(pn){
				cout<<pn->value<<"\t";//输出元素值				
				if(pn->left){
					pl=new list;
					pl->pn=pn;//根节点入栈
					pl->next=ps->top;
					ps->top=pl;
					pn=pn->left;//左节点
				}else{
					pn=NULL;
				}
			}
			else{				
				pl=ps->top;
				ps->top=ps->top->next;//弹出栈中左结点元素			
				
				if(pl->pn->right){
					pn=pl->pn->right;
				}else{
					pn=NULL;
				}
				delete pl;//删除左结点
			}	
		}
	}
	cout<<endl;
}

void travel_level_binary_tree(pnode pn)//二叉树层次遍历
{	
	if(pn!=NULL){//队列初始信息设置
		pqueue pq=new queue;//队列
		plist pl=new list;//链表		
		pl->pn=pn;
		pq->head=pl;
		pq->tail=NULL;//链表尾部
		pq->head->next=pq->tail;
		plist pltmp=pl;//用在存放最有一个有用的地址指针

		while(pq->head!=pq->tail){
			cout<<pq->head->pn->value<<"\t";
			if(pq->head->pn->left){
				pl=new list;
				pl->pn=pq->head->pn->left;

				pltmp->next=pl;
				pltmp=pl;
				pltmp->next=pq->tail;
			}
			if(pq->head->pn->right){
				pl=new list;
				pl->pn=pq->head->pn->right;

				pltmp->next=pl;
				pltmp=pl;
				pltmp->next=pq->tail;
			}
			pl=pq->head;
			pq->head=pq->head->next;
			delete pl;
		}
		cout<<endl;
	}	
}
int main()
{
	srand((unsigned int)time(NULL));
	int maxDep;
	while(maxDep=rand()%10,maxDep<3);
	pnode pn;
	maxDep=5;
	build_binary_tree(pn,0,maxDep);//构建二叉树
	cout<<endl;
	travel_level_binary_tree(pn);//层次遍历-队列实现
	travel_recursive_binary_tree(pn);//前序遍历
	cout<<endl;
	travel_stack_binary_tree(pn);//递归遍历-堆栈实现
}
