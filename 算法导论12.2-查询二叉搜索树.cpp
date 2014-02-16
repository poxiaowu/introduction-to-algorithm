#include<iostream>
#include <ctime>
using namespace std;

typedef struct node{//二叉树
	int value;
	node *left,*right;
}node,*pNode;

void build_binary_search_tree(pNode &pn,int n)//建立n个节点的二叉搜索树
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
						break;//插入到节点的左子树并退出
					}
				}else{
					if(pnt->right){
						pnt=pnt->right;
					}else{
						pnt->right=ptmp;
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


int main()
{
	srand((unsigned)time(NULL));
	int n=50;
	pNode pn=NULL;
	build_binary_search_tree(pn,n);
	cout<<endl;
	InOrder(pn);//中序排序
	cout<<endl;

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
	p=binary_tree_minimum(pn);//查找最小值
	if(p){
		cout<<"minimum is :"<<p->value<<endl;
	}
	p=binary_tree_maximum(pn);//查找最大值
	if(p){
		cout<<"maximum is :"<<p->value<<endl;
	}

}     
