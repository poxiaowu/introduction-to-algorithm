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

void travel_recursive_binary_tree(pnode pn)
{
	if(pn!=NULL){
		cout<<pn->value<<"\t";
		travel_recursive_binary_tree(pn->left);
		travel_recursive_binary_tree(pn->right);
	}
}

void travel_level_binary_tree(pnode pn)//二叉树层次遍历
{	
	if(pn!=NULL){//队列初始信息设置
		pqueue pq=new queue;		
		pq->head=new list;
		pq->tail=new list;

		plist pl=new list;
		pl->pn=pn;

		pq->head=pl;
		pq->tail=pl;
		do
		{
			cout<<pq->head->pn->value<<"\t";
			if(pq->head->pn->left){
				pl=new list;
				pl->pn=pq->head->pn->left;
				pq->tail->next=pl;
				pq->tail=pl;
			}
			if(pq->head->pn->right){
				pl=new list;
				pl->pn=pq->head->pn->right;
				pq->tail->next=pl;
				pq->tail=pl;
			}
			pl=pq->head;
			pq->head=pq->head->next;
			delete pl;
		}while(pq->head!=pq->tail);
		cout<<pq->tail->pn->value<<endl;
		delete pq->tail;
	}	
}

int main()
{
	srand((unsigned int)time(NULL));
	int maxDep;
	while(maxDep=rand()%10,maxDep<3);
	pnode pn;
	maxDep=4;
	build_binary_tree(pn,0,maxDep);//构建二叉树
	cout<<endl;
	travel_recursive_binary_tree(pn);//中序遍历
	cout<<endl;
	travel_level_binary_tree(pn);//层次遍历
}
