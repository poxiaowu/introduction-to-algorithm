#include<iostream>
#include <ctime>
using namespace std;

typedef struct rb_node{//带父节点的二叉树
	int value;
	rb_node *left,*right,*parent;
	bool rb;//rb=0表示结点,rb=1表示红结点
}rb_node,*pRBNode;

void binary_tree_left_rotation(pRBNode &pn,pRBNode y)//二叉搜索树左旋
{
	if(y->right){
		pRBNode x=y->right;
		y->right=x->left;
		if(x->left){
			x->left->parent=y;
		}
		x->parent=y->parent;
		if(y->parent==NULL){
			pn=x;
		}else if(y==y->parent->left){
			y->parent->left=x;
		}else{
			y->parent->right=x;
		}
		x->left=y;
		y->parent=x;
	}
}

void binary_tree_right_rotation(pRBNode &pn,pRBNode x)//二叉搜索树右旋
{
	if(x->left){
		pRBNode y=x->left;
		x->left=y->right;
		if(y->right){
			y->right->parent=x;
		}
		y->parent=x->parent;
		if(x->parent==NULL){
			pn=y;
		}else if(x==x->parent->left){
			x->parent->left=y;
		}else{
			x->parent->right=y;
		}
		y->right=x;
		x->parent=y;
	}
}

void rb_tree_insert_fixup(pRBNode &pn,pRBNode pz)//红黑结点修复
{
	while(pz->parent &&pz->parent->parent && pz->parent->rb){//子结点父结点均为红结点
		pRBNode y;
		if(pz->parent==pz->parent->parent->left){//当前结点的父结点是当前结点父结点的父节点的左子树
			y=pz->parent->parent->right;
			if(y && y->rb){//堂叔为红结点,case one
				pz->parent->rb=0;
				pz->parent->parent->rb=1;
				y->rb=0;
				pz=pz->parent->parent;
			}else if(pz==pz->parent->right){//case two
				pz=pz->parent;
				binary_tree_left_rotation(pn,pz);
			}
			if(pz->parent && pz->parent->parent){//case three
				pz->parent->rb=0;		
				pz->parent->parent->rb=1;
				binary_tree_right_rotation(pn,pz->parent->parent);
			}
		}else{//当前结点的父结点是当前结点父结点的父节点的右子树
			y=pz->parent->parent->left;
			if(y && y->rb){//堂叔结点是红色
				pz->parent->rb=0;
				pz->parent->parent->rb=1;
				y->rb=0;
				pz=pz->parent->parent;
			}else if(pz==pz->parent->left){//case two
				pz=pz->parent;
				binary_tree_right_rotation(pn,pz);
			}
			if(pz->parent && pz->parent->parent){//case three
				pz->parent->rb=0;
				pz->parent->parent->rb=1;
				binary_tree_right_rotation(pn,pz->parent->parent);
			}
		}
		pn->rb=0;
	}
}

void binary_tree_insert(pRBNode &pn,pRBNode pz)
{	
	pRBNode x=pn;
	pRBNode y=NULL;
	while (x){
		y=x;
		if(pz->value<=x->value){
			x=x->left;
		}else{
			x=x->right;
		}
	}
	if(y==NULL){
		pn=pz;
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
	for(int i=0;i<n;++i){
		value=rand()%201-100;
		ptmp=new rb_node;
		ptmp->left=NULL;
		ptmp->right=NULL;
		ptmp->parent=NULL;
		ptmp->value=value;
		ptmp->rb=1;//红结点
		//cout<<value<<"\t";
		binary_tree_insert(pn,ptmp);
	}
	//cout<<endl;
}
void InOrder(pRBNode pn)//中序遍历
{
	if(pn){
		InOrder(pn->left);
		cout<<pn->value<<"\t";
		InOrder(pn->right);
	}
}

pRBNode binary_tree_search(pRBNode pn,int key)//二叉搜索树查找
{
	while (pn && key != pn->value){
		if(key<pn->value){
			pn=pn->left;
		}else{
			pn=pn->right;
		}
	}
	return pn;		
}

pRBNode binary_tree_maximum(pRBNode pn)//最大值
{
	while (pn && pn->right){
		pn=pn->right;
	}
	return pn;
}

pRBNode binary_tree_minimux(pRBNode pn)//最小值
{
	while(pn && pn->left){
		pn=pn->left;
	}
	return pn;
}

pRBNode binary_tree_successor(pRBNode pz)//后继结点
{
	if(pz->right){
		return binary_tree_minimux(pz->right);
	}
	pRBNode p=pz->parent;//父亲节点
	while(p && pz==p->right){
		pz=p;
		p=p->parent;
	}
	return p;
}

pRBNode binary_tree_predecessor(pRBNode pz)
{
	if(pz->left){
		return binary_tree_maximum(pz->left);
	}
	pRBNode p=pz->parent;
	while(p && pz==p->left){
		pz=p;
		p=p->parent;
	}
	return p;
}

void rb_transplant(pRBNode &pn,pRBNode u,pRBNode v)//红黑树删除操作辅助程序
{
	if(u->parent==NULL){
		pn=v;
	}else if(u==u->parent->left){
		u->parent->left=v;
	}else{
		u->parent->right=v;
	}
	if(v){
		v->parent=u->parent;
	}
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
				//delete px->left;//删掉多余的辅助结点
				//px->left=NULL;
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
				/*px->parent->left=NULL;
				delete px;*/
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
				/*delete px->right;
				px->right=NULL;*/
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
				/*px->parent->right=NULL;
				delete px;*/
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
	if(pz->left==NULL){
		px=py->right;
		//if(px==NULL){//出现px为空的情况
		//	px=new rb_node;
		//	px->rb=0;
		//	px->parent=py;
		//	py->right=px;
		//}
		rb_transplant(pn,pz,pz->right);
	}else if(pz->right==NULL){
		px=py->left;
		//if(px==NULL){//px记录py的右结点
		//	px=new rb_node;
		//	px->rb=0;
		//	px->parent=py;
		//	py->left=px;
		//}
		rb_transplant(pn,pz,pz->left);
	}else{
		py=binary_tree_minimux(pz->right);//pz的后继
		px=py->right;//py的后继
		//if(px==NULL){//出现px为空的情况
		//	px=new rb_node;
		//	px->rb=0;
		//	px->parent=py;
		//	py->right=px;
		//}
		y_org_color=py->rb;
		if(py=pz->right){
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
	if(0==py->rb){//被删除或者被调整为的内部结点为黑色
		rb_delete_fixup(pn,px);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=100;
	pRBNode pn=NULL;
	build_binary_search_tree(pn,n);
	InOrder(pn);//中序排序

	pRBNode p;
	int key;
	for(int i=0;i<50;++i){
		key=rand()%101-50;
		cout<<endl<<"search key : "<<key;
		p=binary_tree_search(pn,key);//二叉搜索树查找
		if(p){
			cout<<" founded"<<endl;
			cout<<"successor is : "<<binary_tree_successor(p)->value<<endl;
			cout<<"predecessor is :"<<binary_tree_predecessor(p)->value<<endl;
			if(key % 2 ){
				cout<<"left rotation"<<endl;
				binary_tree_left_rotation(pn,p);
			}else{
				cout<<"right rotation"<<endl;
				binary_tree_right_rotation(pn,p);
			}
			cout<<"node be deleted"<<endl;
			//rb_delete(pn,p);//删除结点
			InOrder(pn);//中序排序
		}else{
			cout<<" not founded"<<endl;
		}
	}

	p=binary_tree_maximum(pn);
	cout<<"maximum is : "<<p->value<<endl;
	p=binary_tree_minimux(pn);
	cout<<"minimum is : "<<p->value<<endl;
}     
