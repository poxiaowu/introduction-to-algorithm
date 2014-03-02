#include<iostream>
#include <ctime>
#include <limits>
using namespace std;

typedef struct rb_node{//带父节点的红黑树
	int value;
	rb_node *left,*right,*parent;
	bool rb;//rb=0表示结点,rb=1表示红结点
	int min,max,min_gap;//计算红黑树中两个最接近的数的差值
}rb_node,*pRBNode;

pRBNode nil;//所有结点的公共黑色结点，类似于NULL

int four_min(int a,int b,int c,int d)
{
	int num1=a>b?b:a;
	int num2 = num1>c?c:num1;
	return num2>d?d:num2;
}

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

	if(y->left!=nil){//调整y结点的值
		y->min=y->left->min;
	}else{
		y->min=y->value;
	}
	if(y->right!=nil){
		y->max=y->right->max;
	}else{
		y->max=y->value;
	}
	y->min_gap=four_min(abs(y->left->min_gap),abs(y->right->min_gap),abs(y->value-y->left->max),abs(y->right->min-y->value));
	if(x->left!=nil){//调整x结点的值
		x->min=x->left->min;
	}else{
		x->min=x->value;
	}
	if(x->right!=nil){
		x->max=x->right->max;
	}else{
		x->max=x->value;
	}
	x->min_gap=four_min(abs(x->left->min_gap),abs(x->right->min_gap),abs(x->value-x->left->max),abs(x->right->min-x->value));
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

	if(x->left!=nil){//调整x结点的值
		x->min=x->left->min;
	}else{
		x->min=x->value;
	}
	if(x->right!=nil){
		x->max=x->right->max;
	}else{
		x->max=x->value;
	}
	x->min_gap=four_min(abs(x->left->min_gap),abs(x->right->min_gap),abs(x->value-x->left->max),abs(x->right->min-x->value));

	if(y->left!=nil){//调整y结点的值
		y->min=y->left->min;
	}else{
		y->min=y->value;
	}
	if(y->right!=nil){
		y->max=y->right->max;
	}else{
		y->max=y->value;
	}
	y->min_gap=four_min(abs(y->left->min_gap),abs(y->right->min_gap),abs(y->value-y->left->max),abs(y->right->min-y->value));

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

void binary_tree_insert(pRBNode &pn,pRBNode pz)
{	
	pRBNode x=pn;
	pRBNode y=nil;
	while (x!=nil){
		y=x;
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
	pRBNode ptm=pz;
	int left_gap,right_gap,c_left_gap,right_c_gap;
	while (y!=nil){//调整路径上的结点的min,max,min_gap值
		if(ptm==ptm->parent->left){//左子树的时候
			y->min=y->left->min;
			left_gap=y->left->min_gap;
			c_left_gap=y->value-y->left->max;
			if(y->right!=nil){//判断是否具有相应的结点
				right_gap=y->right->min_gap;
				right_c_gap=y->right->min-y->value;
			}else{
				right_gap=numeric_limits<int>::max();
				right_c_gap=numeric_limits<int>::max();
			}
		}else{//右子树的时候
			y->max=y->right->max;
			right_gap=y->right->min_gap;
			right_c_gap=y->right->min-y->value;
			if(y->left!=nil){
				left_gap=y->left->min_gap;
				c_left_gap=y->value-y->left->max;
			}else{
				left_gap=numeric_limits<int>::max();
				c_left_gap=numeric_limits<int>::max();
			}
		}
		y->min_gap=four_min(left_gap,c_left_gap,right_gap,right_c_gap);//获取最小的差值
		ptm=y;
		y=y->parent;
	}
	rb_tree_insert_fixup(pn,pz);//插入结点后可能会破坏红黑树的性质，
}
void build_binary_search_tree(pRBNode &pn,int n)//建立n个具有父节点的二叉搜索树
{
	int value;
	pRBNode ptmp;
	//int a[10]={-2,-3,4,-3,-5,5,5,3,-3,0};
	for(int i=0;i<n;++i){
		value=rand()%10001-5000;
		ptmp=new rb_node;
		ptmp->left=nil;
		ptmp->right=nil;
		ptmp->parent=nil;
		ptmp->value=/*a[i]*/value;
		ptmp->rb=1;//红结点
		ptmp->min=value;
		ptmp->max=value;
		ptmp->min_gap=numeric_limits<int>::max();//初始为最大值
		//cout<<value/*a[i]*/<<"\t";
		binary_tree_insert(pn,ptmp);
	}
	//cout<<endl;
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

int compare(const void *a,const void *b)
{
	return (*(int *)a- *(int *)b);
}

int minimum_gap(pRBNode pn,int n)
{
	int *a=new int[n];
	pRBNode pr=binary_tree_minimux(pn);
	for(int i=0;i<n;++i){
		a[i]=pr->value;
		pr=binary_tree_successor(pr);
		cout<<a[i]<<"\t";
	}
	cout<<endl;
	int *b=new int[n-1];
	for(int i=0;i<n-1;i++){
		b[i]=a[i+1]-a[i];
		cout<<b[i]<<"\t";
	}
	cout<<endl<<endl;
	delete []a;
	qsort(b,n-1,sizeof(int),compare);
	for(int i=0;i<n-1;i++){
		cout<<b[i]<<"\t";
	}
	cout<<endl;
	int result=b[0];
	delete []b;
	return result;
}


int main()
{
	srand((unsigned)time(NULL));
	int n=100;

	nil=new rb_node;
	nil->left=nil;
	nil->right=nil;
	nil->rb=0;//黑色
	nil->parent=nil;
	nil->value=numeric_limits<int>::max();
	nil->min=numeric_limits<int>::max();
	nil->max=numeric_limits<int>::max();
	nil->min_gap=numeric_limits<int>::max();
	pRBNode pn=nil;

	build_binary_search_tree(pn,n);
	InOrder(pn);//中序排序
	cout<<endl;
	cout<<"minimum gap is : "<<minimum_gap(pn,n)<<
		"\t"<<pn->min_gap<<endl;
}   
