#include<iostream>
#include <ctime>
using namespace std;

typedef struct node{//带父节点的二叉树
	int value;
	node *left,*right,*parent;
}node,*pNode;

void build_binary_search_tree(pNode &pn,int n)//建立n个具有父节点的二叉搜索树
{
	int value;
	pNode ptmp;
	pNode pnt;
	for(int i=0;i<n;++i){//生成n个节点
		value=rand()%201-100;
		ptmp=new node;
		ptmp->value=value;
		ptmp->left=NULL;
		ptmp->right=NULL;
		ptmp->parent=NULL;//父节点为空
		
		cout<<value<<"\t";

		if(pn==NULL){
			pn=ptmp;
		}else{//插入节点,每次插入操作从根节点开始查找
			pnt=pn;
			while(pnt){
				if(value<=pnt->value){
					if(pnt->left){
						pnt=pnt->left;
					}else{
						pnt->left=ptmp;
						ptmp->parent=pnt;//父节点
						break;//插入到节点的左子树并退出
					}
				}else{
					if(pnt->right){
						pnt=pnt->right;
					}else{
						pnt->right=ptmp;
						ptmp->parent=pnt;//父节点
						break;//插入到节点的右子树并退出
					}
				}
			}
		}
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

void InOrder_Parent(pNode pn)//中序遍历，不用堆栈,使用父节点
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


pNode binary_tree_search_recursive(pNode pn,int key)//递归查找
{
	if(pn==NULL || pn->value==key)
		return pn;
	if(key<pn->value){
		return binary_tree_search_recursive(pn->left,key);
	}else{
		return binary_tree_search_recursive(pn->right,key);
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

pNode binary_tree_minimum(pNode pn)//二叉搜索树的最小值
{
	if(pn!=NULL){
		while(pn->left!=NULL){
			pn=pn->left;
		}
	}
	return pn;
}

pNode binary_tree_maximum(pNode pn)//二叉搜索树的最大值
{
	if(pn!=NULL){
		while(pn->right!=NULL){
			pn=pn->right;
		}
	}
	return pn;
}

pNode binary_tree_successor(pNode pn)//二叉查找树节点的后继
{
	if(pn->right){
		return binary_tree_minimum(pn->right);
	}
	pNode y=pn->parent;
	while(y && y->right==pn){
		pn=y;
		y=y->parent;
	}
	return y;
}

pNode binary_tree_predecessor(pNode pn)//二叉查找树节点前驱
{
	if(pn->left){
		return binary_tree_maximum(pn->left);
	}
	pNode y=pn->parent;
	while(y && y->left==pn){
		pn=y;
		y=y->parent;
	}
	return y;
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
	InOrder_Parent(pn);

	int key=rand()%201-100;//随机查找值
	pNode p;//存放返回值
	p=binary_tree_search_recursive(pn,key);//递归查找
	cout<<"key "<<key<<" ";
	if(p){
		cout<<" founded."<<endl;
	}else{
		cout<<"not found"<<endl;
	}
	p=binary_tree_search_iterator(pn,key);//迭代查找
	cout<<"key "<<key<<" ";
	if(p){
		cout<<" founded."<<endl;
	}else{
		cout<<"not found"<<endl;
	}

	if(p){
		cout<<"successor : "<<binary_tree_successor(p)->value<<endl;
		cout<<"predecessor : "<<binary_tree_predecessor(p)->value<<endl;
	}

	p=binary_tree_minimum(pn);//查找最小值
	if(p){
		cout<<"minimum is :"<<p->value<<endl;
	}
	p=binary_tree_maximum(pn);//查找最大值
	if(p){
		cout<<"maximum is :"<<p->value<<endl;
	}
}     
