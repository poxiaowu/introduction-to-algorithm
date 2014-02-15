#include<iostream>
#include <ctime>
using namespace std;

typedef struct node_f{//具有父节点和访问标记的二叉树
	int value;
	node_f *left,*right,*parent;
	bool visited;
}node_f, *pNode_f;

/************************使用父节点*************************************/

typedef struct node{//创建具有父节点的二叉树
	int value;
	node *left,*right,*parent;
}node,*pNode;


void InOrder(pNode pn)//中序遍历，不用堆栈,使用父节点
{
	while(pn){
		if(pn->left){//找到子树的最左节点
			pn=pn->left;
			continue;
		}
		cout<<pn->value<<"\t";//输出子树的最左节点
		if(pn->right){//有右节点则处理左节点的右节点
			pn=pn->right;
			continue;
		}

		while(pn){
			if(pn->parent==NULL)
				return;
			if(pn==pn->parent->left){//若节点是父节点的左节点
				cout<<pn->parent->value<<"\t";//则处理父节点
				if(pn->parent->right){//和处理该节点的兄弟节点
					pn=pn->parent->right;
					break;
				}
			}
			pn=pn->parent;//若该节点无右节点或者该节点是父节点的右节点，则回溯到父节点
		}
	}
}

/************************使用父节点和访问标记*************************************/
void build_binary_tree(pNode_f &pn,pNode_f parent,pNode &pn_n,pNode parent_n,int depth,int maxDep)//创建一个有父亲节点和访问标记的二叉树
{
	if(depth<maxDep){
		//创建根节点
		pn=new node_f;		
		pn->value=rand()%101-50;		
		pn->left=NULL;
		pn->right=NULL;
		pn->visited=false;
		pn->parent=parent;
		//cout<<pn->value<<"\t";

		pn_n=new node;
		pn_n->value=pn->value;
		pn_n->left=NULL;
		pn_n->right=NULL;
		pn_n->parent=parent_n;

		build_binary_tree(pn->left,pn,pn_n->left,pn_n,depth+1,maxDep);
		build_binary_tree(pn->right,pn,pn_n->right,pn_n,depth+1,maxDep);
	}
}


void InOrder_flag(pNode_f pn)//中序遍历，不用堆栈，使用父节点和访问标记
{
	while(pn){//回溯到根节点的父节点，即NULL时，退出
		if(pn->left  && !pn->left->visited){
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

void test_binary_tree(pNode_f pn)
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


int main()
{
	srand((unsigned)time(NULL));
	pNode_f pn=NULL;
	pNode pn_n=NULL;
	int maxDep=3;
	build_binary_tree(pn,NULL,pn_n,NULL,0,maxDep);
	//test_binary_tree(pn);
	InOrder_flag(pn);
	cout<<endl<<endl;
	InOrder(pn_n);
	cout<<endl;
}
