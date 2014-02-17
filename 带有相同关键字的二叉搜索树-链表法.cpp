#include<iostream>
#include <ctime>
using namespace std;

typedef struct node{//带父节点的二叉树
	int value;
	node *left,*right,*parent;
	node *next;//具有相同关键字的二叉搜索树,
}node,*pNode;//当关键字相同时候，使用链表链接


void binary_tree_insert(pNode &pn,pNode pz)//二叉树插入操作
{
	pNode y=NULL;
	pNode x=pn;
	while(x!=NULL){
		y=x;
		if(pz->value==x->value){
			pz->next=x->next;
			x->next=pz;
			return;
		}else if(pz->value<x->value){
			x=x->left;
		}else{
			x=x->right;
		}	
	}
	pz->parent=y;
	if(y==NULL){
		pn=pz;
	}else if(pz->value<y->value){
		y->left=pz;
	}else{
		y->right=pz;
	}
}

void build_binary_search_tree(pNode &pn,int n)//建立n个具有父节点的二叉搜索树
{
	int value;
	pNode ptmp;
	for(int i=0;i<n;++i){
		value=rand()%51-25;
		ptmp=new node;
		ptmp->left=NULL;
		ptmp->right=NULL;
		ptmp->parent=NULL;
		ptmp->next=NULL;
		ptmp->value=value;
		binary_tree_insert(pn,ptmp);
		cout<<value<<"\t";
	}
	cout<<endl;
}

void InOrder(pNode pn)//中序遍历
{
	if(pn){
		InOrder(pn->left);
		pNode p=pn;
		while(p){
			cout<<p->value<<"\t";
			p=p->next;
		}
		InOrder(pn->right);
	}
}


int main()
{
	srand((unsigned)time(NULL));
	int n=100;
	pNode pn=NULL;
	build_binary_search_tree(pn,n);
	cout<<endl;
	InOrder(pn);//中序排序
	cout<<endl;
}     
