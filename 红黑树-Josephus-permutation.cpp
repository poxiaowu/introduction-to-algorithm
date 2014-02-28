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

void binary_tree_insert(pRBNode &pn,pRBNode pz)
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
}
void build_binary_search_tree(pRBNode &pn,int n)//建立n个具有父节点的二叉搜索树
{
	int value;
	pRBNode ptmp;
	//int a[10]={-2,-3,4,-3,-5,5,5,3,-3,0};
	for(int i=0;i<n;++i){
		//value=rand()%101-50;
		ptmp=new rb_node;
		ptmp->left=nil;
		ptmp->right=nil;
		ptmp->parent=nil;
		ptmp->value=/*a[i]*//*value*/i+1;
		ptmp->rb=1;//红结点
		ptmp->size=1;
		cout<</*value*//*a[i]*/i+1<<"\t";
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

void rb_transplant(pRBNode &pn,pRBNode u,pRBNode v)//红黑树删除操作辅助程序
{
	if(u->parent==nil){
		pn=v;
	}else if(u==u->parent->left){
		u->parent->left=v;
	}else{
		u->parent->right=v;
	}
	v->parent=u->parent;
}

void rb_delete_fixup(pRBNode &pn,pRBNode px)//红黑树 删除操作修正
{
	while(px!=pn && 0==px->rb){
		pRBNode pw;//px的兄弟结点
		if(px==px->parent->left){//px为左子结点
			pw=px->parent->right;
			if(pw->rb){//兄弟结点为红色,case one
				px->parent->rb=1;
				pw->rb=0;
				binary_tree_left_rotation(pn,px->parent);//左旋转
				pw=px->parent->right;
			}
			if(pw->left->rb==0 && pw->right->rb==0){//case two
				pw->rb=1;
				px=px->parent;
			}
			else{ 
				if(pw->right->rb==0){//case three
					pw->left->rb=0;
					pw->rb=1;				
					binary_tree_right_rotation(pn,pw);
					pw=px->parent->right;
				}
				pw->rb=px->parent->rb;
				px->parent->rb=0;
				pw->right->rb=0;				
				binary_tree_left_rotation(pn,px->parent);
				px=pn;
			}
		}else{//px为右子结点
			pw=px->parent->left;
			if(pw->rb){
				px->parent->rb=1;
				pw->rb=0;
				binary_tree_right_rotation(pn,px->parent);
				pw=px->parent->left;
			}
			if(pw->left->rb==0 && pw->right->rb==0){
				pw->rb=1;
				px=px->parent;
			}else{
				if(pw->left->rb==0){
					pw->right->rb=0;
					pw->rb=1;
					binary_tree_left_rotation(pn,pw);
					pw=px->parent->left; 
				}
				pw->rb=px->parent->rb;
				px->parent->rb=0;
				pw->left->rb=0;
				binary_tree_right_rotation(pn,px->parent);
				px=pn;
			}
		}
	}
	px->rb=0;
}

void rb_delete(pRBNode &pn,pRBNode pz)
{
	pRBNode py=pz;//py记录pz或者pz的后继
	bool y_org_color=py->rb;//记录删除结点的颜色
	pRBNode px;//px记录py的右结点
	if(pz->left==nil){
		px=py->right;
		rb_transplant(pn,pz,pz->right);
	}else if(pz->right==nil){
		px=py->left;
		rb_transplant(pn,pz,pz->left);
	}else{
		py=binary_tree_minimux(pz->right);//pz的后继
		px=py->right;//py的后继
		y_org_color=py->rb;
		if(py==pz->right){
			px->parent=py;
		}else{
			rb_transplant(pn,py,py->right);
			py->right=pz->right;
			py->right->parent=py;
		}
		rb_transplant(pn,pz,py);
		py->left=pz->left;
		py->left->parent=py;
		py->rb=pz->rb;
	}
	py=pz->parent;
	while (py!=nil){//更新结点的size值
		py->size--;
		py=py->parent;
	}
	delete pz;

	if(0==y_org_color){//被删除或者被调整为的内部结点为黑色
		rb_delete_fixup(pn,px);
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

void Josephus_permutation(pRBNode &pn,int n,int m)
{
	int j=1;
	pRBNode p;
	for(int k=n;k>0;k--){
		j=(j+m-2)%k+1;
		p=os_select(pn,j);
		cout<<p->value<<"\t";
		rb_delete(pn,p);
	}
	cout<<endl;
}

int main()
{
	srand((unsigned)time(NULL));
	int n=7;

	nil=new rb_node;
	nil->left=nil;
	nil->right=nil;
	nil->rb=0;//黑色
	nil->parent=nil;
	nil->value=numeric_limits<int>::min();
	nil->size=0;//nil结点大小为0
	pRBNode pn=nil;

	build_binary_search_tree(pn,n);
	cout<<endl;
	Josephus_permutation(pn,n,3);	
}
