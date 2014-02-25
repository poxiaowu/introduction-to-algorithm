#include<iostream>
#include <ctime>
#include <limits>
using namespace std;

typedef struct rb_node{//带父节点的二叉树
	int value;
	rb_node *left,*right,*parent;
	bool rb;//rb=0表示结点,rb=1表示红结点
	int size;//存储左右子树大小和该结点之和
}rb_node,*pRBNode;

pRBNode nil;//所有结点的公共黑色结点，类似于NULL

void binary_tree_left_rotation(pRBNode &pn,pRBNode y)//二叉搜索树左旋
{
	pRBNode x=y->right;
	y->right=x->left;
	if(x->left!=nil){
		x->left->parent=y;
	}
	x->parent=y->parent;
	if(y->parent==nil){
		pn=x;
	}else if(y==y->parent->left){
		y->parent->left=x;
	}else{
		y->parent->right=x;
	}
	x->left=y;
	y->parent=x;
	x->size=y->size;//更新相应结点值
	y->size=y->left->size+y->right->size+1;
}

void binary_tree_right_rotation(pRBNode &pn,pRBNode x)//二叉搜索树右旋
{
	pRBNode y=x->left;
	x->left=y->right;
	if(y->right!=nil){
		y->right->parent=x;
	}
	y->parent=x->parent;
	if(x->parent==nil){
		pn=y;
	}else if(x==x->parent->left){
		x->parent->left=y;
	}else{
		x->parent->right=y;
	}
	y->right=x;
	x->parent=y;
	y->size=x->size;//更新相应的size值
	x->size=x->left->size+x->right->size+1;
}

void rb_tree_insert_fixup(pRBNode &pn,pRBNode pz)//红黑结点修复
{
	while(pz->parent->rb){//子结点父结点均为红结点
		pRBNode y;
		if(pz->parent==pz->parent->parent->left){//当前结点的父结点是当前结点父结点的父节点的左子树
			y=pz->parent->parent->right;
			if(y->rb){//堂叔为红结点,case one
				pz->parent->rb=0;
				pz->parent->parent->rb=1;
				y->rb=0;
				pz=pz->parent->parent;
			}else{
				if(pz==pz->parent->right){//case two
					pz=pz->parent;
					binary_tree_left_rotation(pn,pz);
				}
				pz->parent->rb=0;		//case three
				pz->parent->parent->rb=1;
				binary_tree_right_rotation(pn,pz->parent->parent);
			}
		}else{//当前结点的父结点是当前结点父结点的父节点的右子树
			y=pz->parent->parent->left;
			if(y->rb){//堂叔结点是红色
				pz->parent->rb=0;
				pz->parent->parent->rb=1;
				y->rb=0;
				pz=pz->parent->parent;
			}else{
				if(pz==pz->parent->left){//case two
					pz=pz->parent;
					binary_tree_right_rotation(pn,pz);
				}
				pz->parent->rb=0;//case three
				pz->parent->parent->rb=1;
				binary_tree_left_rotation(pn,pz->parent->parent);
			}			
		}
		pn->rb=0;
	}
}

pRBNode os_select(pRBNode pn,int i)//选择红黑树中的第i个元素
{
	int r=pn->left->size+1;
	if(r==i){
		return pn;
	}else if(i<r){
		return os_select(pn->left,i);
	}else{
		return os_select(pn->right,i-r);
	}
}

int os_rank(pRBNode pn,pRBNode pz)//求红黑树中pz的秩
{
	int r=pz->left->size+1;
	while(pz!=pn){
		if(pz==pz->parent->right){
			r+=pz->parent->left->size+1;
		}
		pz=pz->parent;
	}
	return r;
}

pRBNode os_successor(pRBNode pn,pRBNode pz,int i)//确定pz的第i个后继
{
	int r=os_rank(pn,pz);
	r+=i;
	return os_select(pn,r);
}

int binary_tree_insert(pRBNode &pn,pRBNode pz)
{	
	pRBNode x=pn;
	pRBNode y=nil;
	while (x!=nil){
		y=x;
		x->size++;//相应路径上的结点的子结点个数加1
		if(pz->value<=x->value){
			x=x->left;
		}else{
			x=x->right;
		}
	}
	if(y==nil){
		pn=pz;
		pn->rb=0;
	}else if(pz->value<=y->value){
		y->left=pz;		
	}else{
		y->right=pz;
	}
	pz->parent=y;
	rb_tree_insert_fixup(pn,pz);//插入结点后可能会破坏红黑树的性质，
	return os_rank(pn,pz);
}

void random_data(int *a,int n)//生成乱序随机数
{
	int tmp;
	int rnd;
	for(int i=0;i<n;++i){
		rnd=rand()%(n-i)+i;
		tmp=a[i];
		a[i]=a[rnd];
		a[rnd]=tmp;
	}
}

int build_binary_search_tree(pRBNode &pn,int n)//建立n个具有父节点的二叉搜索树
{
	int invert_pair=0;
	int value;
	pRBNode ptmp;
	//int a[10]={-2,-3,4,-3,-5,5,5,3,-3,0};
	int *a=new int[n];
	for(int i=0;i<n;++i){
		a[i]=i;
	}
	random_data(a,n);//随机
	for(int i=0;i<n;++i){
		value=rand()%101-50;
		ptmp=new rb_node;
		ptmp->left=nil;
		ptmp->right=nil;
		ptmp->parent=nil;
		ptmp->value=a[i];
		ptmp->rb=1;//红结点
		ptmp->size=1;
		cout<<a[i]<<"\t";
		invert_pair+=(i+1-binary_tree_insert(pn,ptmp));
	}
	cout<<endl;
	return invert_pair;
}
void InOrder(pRBNode pn)//中序遍历
{
	if(pn!=nil){
		InOrder(pn->left);
		cout<<pn->value<<"\t";
		InOrder(pn->right);
	}
}

pRBNode binary_tree_search(pRBNode pn,int key)//二叉搜索树查找
{
	pRBNode pp=pn;
	while (pp !=nil && key != pp->value){
		if(key<pp->value){
			pp=pp->left;
		}else{
			pp=pp->right;
		}
	}
	return pp;		
}

pRBNode binary_tree_maximum(pRBNode pn)//最大值
{
	while (pn!=nil && pn->right!=nil){
		pn=pn->right;
	}
	return pn;
}

pRBNode binary_tree_minimux(pRBNode pn)//最小值
{
	while(pn!=nil && pn->left!=nil){
		pn=pn->left;
	}
	return pn;
}

pRBNode binary_tree_successor(pRBNode pz)//后继结点
{
	if(pz->right!=nil){
		return binary_tree_minimux(pz->right);
	}
	pRBNode p=pz->parent;//父亲节点
	while(p!=nil && pz==p->right){
		pz=p;
		p=p->parent;
	}
	return p;
}

pRBNode binary_tree_predecessor(pRBNode pz)
{
	if(pz->left!=nil){
		return binary_tree_maximum(pz->left);
	}
	pRBNode p=pz->parent;
	while(p!=nil && pz==p->left){
		pz=p;
		p=p->parent;
	}
	return p;
}

int main()
{
	srand((unsigned)time(NULL));
	int n=4;

	nil=new rb_node;
	nil->left=nil;
	nil->right=nil;
	nil->rb=0;//黑色
	nil->parent=nil;
	nil->value=numeric_limits<int>::min();
	nil->size=0;//nil结点大小为0
	pRBNode pn=nil;

	int inversions=build_binary_search_tree(pn,n);
	cout<<"inversions pairs is : "<<inversions<<endl;
	cout<<endl;
	InOrder(pn);//中序排序
	cout<<endl;
	
	pRBNode p;	

	p=binary_tree_maximum(pn);
	cout<<"maximum is : "<<p->value<<endl;
	p=binary_tree_minimux(pn);
	cout<<"minimum is : "<<p->value<<endl;
}     
