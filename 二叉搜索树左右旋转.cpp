#include<iostream>
#include <ctime>
using namespace std;

typedef struct node{//带父节点的二叉树
	int value;
	node *left,*right,*parent;
}node,*pNode;


void binary_tree_insert(pNode &pn,pNode pz)//二叉树插入操作
{
	pNode y=NULL;
	pNode x=pn;
	while(x!=NULL){
		y=x;
		if(pz->value<=x->value){
			x=x->left;
		}else{
			x=x->right;
		}	
	}
	pz->parent=y;
	if(y==NULL){
		pn=pz;
	}else if(pz->value<=y->value){
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
		value=rand()%201-100;
		ptmp=new node;
		ptmp->left=NULL;
		ptmp->right=NULL;
		ptmp->parent=NULL;
		ptmp->value=value;
		binary_tree_insert(pn,ptmp);
	}
}
void InOrder(pNode pn)//中序遍历
{
	if(pn){
		InOrder(pn->left);
		cout<<pn->value<<"\t";
		InOrder(pn->right);
	}
}

void binary_tree_right_rotation(pNode &pn,pNode y)//二叉树右旋转操作
{
	if(y && y->left){//符合条件是右旋
		pNode x=y->left;//y节点的左子结点
		y->left=x->right;
		if(x->right){
			x->right->parent=y;
		}
		x->parent=y->parent;
		if(y->parent==NULL){
			pn=x;
		}else if(y==y->parent->left){
			y->parent->left=x;
		}else{
			y->parent->right=x;
		}
		x->right=y;
		y->parent=x;
	}
}

void binary_tree_left_rotation(pNode &pn,pNode x)//二叉树左旋操作
{
	if(x && x->right){//符合条件是左旋
		pNode y=x->right;
		x->right=y->left;
		if(y->left){
			y->left->parent=x;
		}
		y->parent=x->parent;
		if(x->parent==NULL){
			pn=y;
		}else if(x==x->parent->left){
			x->parent->left=y;
		}else{
			x->parent->right=y;
		}
		y->left=x;
		x->parent=y;
	}
}

pNode binary_tree_search_iterator(pNode pn,int key)//迭代查找
{
	while(pn!=NULL && key!=pn->value){
		if(key<pn->value){
			pn=pn->left;
		}else{
			pn=pn->right;
		}
	}
	return pn;
}

int main()
{
	srand((unsigned)time(NULL));
	int n=50;
	pNode pn=NULL;
	build_binary_search_tree(pn,n);
	cout<<endl;
	InOrder(pn);//中序排序
	cout<<endl;

	pNode p;//存放返回值
	for(int i=0;i<5;++i){
		int key=rand()%101-50;//随机查找值		
		p=binary_tree_search_iterator(pn,key);//递归查找
		binary_tree_left_rotation(pn,p);
		key=rand()%101-50;//随机查找值		
		p=binary_tree_search_iterator(pn,key);//递归查找
		binary_tree_right_rotation(pn,p);
	}
	InOrder(pn);//中序排序
}     
