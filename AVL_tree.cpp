#include<iostream>
#include <ctime>
using namespace std;

typedef struct avl_node{//AVL树
	int value;
	int height;
	avl_node *left,*right,*parent;
}avl_node,*pAvl_node;


void left_rotation(pAvl_node &pn,pAvl_node  px)//左旋转,并调整结点高度值
{
	if(px && px->right){
		pAvl_node py=px->right;
		px->right=py->left;
		if(py->left){
			py->left->parent=px;
		}
		py->parent=px->parent;
		if(px->parent==NULL){
			pn=py;
		}else if(px==px->parent->left){
			px->parent->left=py;
		}else{
			px->parent->right=py;
		}
		py->left=px;
		px->parent=py;
		py->height+=(-1);//调整结点高度值
		px->height=0;
	}
}
void right_rotation(pAvl_node &pn,pAvl_node py)//右旋转，并调整结点高度值
{
	if(py && py->left){
		pAvl_node px=py->left;
		py->left=px->right;
		if(px->right){
			px->right->parent=py;
		}
		px->parent=py->parent;
		if(py->parent==NULL){
			pn=px;
		}else if(py==py->parent->left){
			py->parent->left=px;
		}else{
			py->parent->right=px;
		}
		px->right=py;
		py->parent=px;
		px->height+=1;//调整结点高度值
		py->height=0;
	}
}

void avl_tree_fixup(pAvl_node &pn,pAvl_node pz)//高度值调整
{//AVL数的平衡方法需要借助于三个结点来完成，pz表示插入结点，py为指针
	pAvl_node py=pz->parent;
	int height=0;//pz祖父结点的高度值,初始值为0
	while (py->parent){//while循环查找不平衡结点
		if(py==py->parent->left){//左结点加负值
			py->parent->height+= -1;
		}else{//右结点加正值
			py->parent->height += 1;
		}		
		height=py->parent->height;//获取pz祖父结点的高度值
		if(height==0 || height==2 || height==-2){//结点平衡
			break; 
		}else if(height==-1 || height==1){//结点失去平衡
			pz=pz->parent;//pz结点上移
			py=pz->parent;//py表示成pz的祖父结点
		}
	}
	if(height==2 || height==-2){//已找出不平衡结点，否则所有结点平衡
		if(pz==pz->parent->left){
			if(pz->parent==pz->parent->parent->left){//case one,right-rotation
				right_rotation(pn,pz->parent->parent);
			}else{//case two,first right-rotation,then left-rotation
				right_rotation(pn,pz->parent);
				left_rotation(pn,pz->parent);
			}
		}else{
			if(pz->parent==pz->parent->parent->left){//case three,first left-rotaion,then right-rotation
				left_rotation(pn,pz->parent);
				right_rotation(pn,pz->parent);
			}else{//case four,left-rotation
				left_rotation(pn,pz->parent->parent);
			}
		}  
	}
}

void avl_tree_insert(pAvl_node &pn,pAvl_node pz)
{
	pAvl_node py=NULL;
	pAvl_node px=pn;
	while (px){
		py=px;
		if(pz->value<=px->value){
			px=px->left;
		}else{
			px=px->right;
		}
	}
	if(py==NULL){
		pn=pz;
	}else if(pz->value<=py->value){
		py->left=pz;
		py->height+=-1;//更新父亲结点高度值
	}else{
		py->right=pz;
		py->height+=1;//更新父亲结点高度值
	}
	pz->parent=py;
	if(py && py->height!=0){
		avl_tree_fixup(pn,pz);//当插入结点父结点不为零时可能会引起其某个祖父结点不平衡
	}
}
void build_binary_search_tree(pAvl_node &pn,int n)//建立n个具有父节点的二叉搜索树
{
	int value;
	pAvl_node ptmp;
	for(int i=0;i<n;++i){
		value=rand()%101-50;
		ptmp=new avl_node;
		ptmp->left=NULL;
		ptmp->right=NULL;
		ptmp->parent=NULL;
		ptmp->value=value;
		ptmp->height=0;//初始高度为0
		avl_tree_insert(pn,ptmp);
		cout<<value<<"\t";
	}
	cout<<endl;
}
void InOrder(pAvl_node pn)//中序遍历
{
	if(pn){
		InOrder(pn->left);
		cout<<pn->value<<"\t";
		InOrder(pn->right);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=100;
	pAvl_node pn=NULL;
	build_binary_search_tree(pn,n);
	cout<<endl;
	InOrder(pn);//中序排序
	cout<<endl;
}     
