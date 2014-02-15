#include<iostream>
#include <ctime>
using namespace std;

typedef struct node{//具有父节点和访问标记的二叉树
	int value;
	node *left,*right,*parent;
	bool visited;
}node, *pNode;


void build_binary_tree(pNode &pn,pNode parent,int depth,int maxDep)//创建一个有父亲节点和访问标记的二叉树
{
	if(depth<maxDep){
		//创建根节点
		pn=new node;
		pn->value=rand()%101-50;
		pn->left=NULL;
		pn->right=NULL;
		pn->visited=false;
		pn->parent=parent;
		cout<<pn->value<<"\t";

		build_binary_tree(pn->left,pn,depth+1,maxDep);
		build_binary_tree(pn->right,pn,depth+1,maxDep);
	}
}

void test_binary_tree(pNode pn)
{
	if(pn){		
		if(pn->left && pn->right && pn->left->parent==pn && pn->right->parent==pn){//测试父节点是否正确
			cout<<pn->value<<"\t";
			cout<<"true"<<endl;
		}
		test_binary_tree(pn->left);
		test_binary_tree(pn->right);
	}	
}

void InOrder_flag(pNode pn)//中序遍历，不用堆栈
{
	while(pn){//回溯到根节点的父节点，即NULL时，退出
		while(pn->left  && !pn->left->visited){
			pn=pn->left;//沿左子树向下搜索尚未访问的最左节点
			continue;
		}
		if(!pn->visited){//访问尚未访问的最左节点并标记为已访问
			cout<<pn->value<<"\t";
			pn->visited=true;
		}
		if(pn->right && !pn->right->visited){//访问当前节点的右子树
			pn=pn->right;
		}else{
			pn=pn->parent;//回溯至父节点
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	pNode pn=NULL;
	int maxDep=5;
	build_binary_tree(pn,NULL,0,maxDep);
	cout<<endl;
	test_binary_tree(pn);
	InOrder_flag(pn);
}
