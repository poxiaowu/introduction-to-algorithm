#include <iostream>
#include <ctime>
#include <limits>

using namespace std;
typedef struct interval_tree{
	int low,high;//区间,同时low做为区间的关键字
	int max;//自己以及子树的区间最大值
	interval_tree *left,*right,*parent;//左右子结点,以及父结点
	bool rb;
}interval_tree,*pInterval_tree;
pInterval_tree nil;

int three_maximum(int a,int b,int c)//求三个数的最大值
{
	int num=a>b?a:b;
	return num>c?num:c;
}

void interval_tree_left_rotation(pInterval_tree &pn,pInterval_tree px)//左旋转操作
{
	pInterval_tree py=px->right;
	px->right=py->left;
	if(py->left!=nil){
		py->left->parent=px;
	}
	py->parent=px->parent;
	if(px->parent==nil){
		pn=py;
	}else if(px==px->parent->left){
		px->parent->left=py;
	}else{
		px->parent->right=py;
	}
	py->left=px;
	px->parent=py;
	px->max=three_maximum(px->left->max,px->right->max,px->high);
	py->max=three_maximum(py->left->max,py->right->max,py->high);
}

void interval_tree_right_rotation(pInterval_tree &pn,pInterval_tree py)//右旋转
{
	pInterval_tree px=py->left;
	py->left=px->right;
	if(px->right!=nil){
		px->right->parent=py;
	}
	px->parent=py->parent;
	if(py->parent==nil){
		pn=px;
	}else if(py==py->parent->left){
		py->parent->left=px;
	}else{
		py->parent->right=px;
	}
	px->right=py;
	py->parent=px;	
	py->max=three_maximum(py->left->max,py->right->max,py->high);
	px->max=three_maximum(px->left->max,px->right->max,px->high);
}


void interval_tree_fixup(pInterval_tree &pn,pInterval_tree pz)
{
	while(pz->parent->rb){//子结点和父结点都是红色
		pInterval_tree py;
		if(pz->parent==pz->parent->parent->left){//父结点是祖父结点的左子树
			py=pz->parent->parent->right;//堂叔结点
			if(py->rb){//堂叔结点是红色
				pz->parent->rb=0;
				py->rb=0;
				pz->parent->parent->rb=1;
				pz=pz->parent->parent;
			}else{
				if(pz==pz->parent->right){
					pz=pz->parent;
					interval_tree_left_rotation(pn,pz);
				}
				pz->parent->parent->rb=1;
				pz->parent->rb=0;
				interval_tree_right_rotation(pn,pz->parent->parent);
			}
		}else{//当前结点的父结点是当前结点父结点的父节点的右子树
			py=pz->parent->parent->left;
			if(py->rb){//堂叔结点是红色
				pz->parent->rb=0;
				pz->parent->parent->rb=1;
				py->rb=0;
				pz=pz->parent->parent;
			}else{
				if(pz==pz->parent->left){//case two
					pz=pz->parent;
					interval_tree_right_rotation(pn,pz);
				}
				pz->parent->rb=0;//case three
				pz->parent->parent->rb=1;
				interval_tree_left_rotation(pn,pz->parent->parent);
			}	
		}
		pn->rb=0;
	}
}


void interval_tree_insert(pInterval_tree &pn,pInterval_tree pz)//区间树插入操作
{
	pInterval_tree py=pn;
	pInterval_tree px=pn;
	while (px!=nil){
		py=px;
		if(pz->low<=px->low){
			px=px->left;
		}else{
			px=px->right;
		}
	}
	if(py==nil){
		pn=pz;
		pz->rb=0;
	}else if(pz->low<=py->low){
		py->left=pz;
	}else{
		py->right=pz;
	}
	pz->parent=py;
	//py->max=three_maximum(py->left->max,py->right->max,py->high);//父结点的最大值
	//pInterval_tree pt=py;
	while(py!=nil){
		py->max=three_maximum(py->left->max,py->right->max,py->high);//更新结点的区间最大值
		py=py->parent;		
	}
	interval_tree_fixup(pn,pz);
}

void build_interval_tree(pInterval_tree &pn,int n)//建立区间数
{
	pInterval_tree ptmp;
	int low,high;
	for(int i=0;i<n;++i){
		low=rand()%101-50;
		high=rand()%101-50;
		if(low>high){//若low>high,则交换
			low+=high;
			high=low-high;
			low-=high;
		}
		ptmp=new interval_tree;
		ptmp->low=low;
		ptmp->high=high;
		ptmp->left=nil;
		ptmp->right=nil;
		ptmp->parent=nil;
		ptmp->max=high;
		ptmp->rb=1;
		interval_tree_insert(pn,ptmp);
		//cout<<"["<<low<<","<<high<<"]"<<"  ";
	}
	//cout<<endl;
}

void InOrder(pInterval_tree pn)//中序遍历
{
	if(pn!=nil){
		InOrder(pn->left);
		cout<<"["<<pn->low<<","<<pn->high<<"]"<<"  ";
		InOrder(pn->right);
	}
}

pInterval_tree interval_search(pInterval_tree pn,pInterval_tree pi)//区间查找
{
	while(pn!=nil && (pi->high<=pn->low || pi->low >= pn->high)){//区间不重叠
		if(pn->left!=nil && pn->left->max>pi->low){
			pn=pn->left;
		}else{
			pn=pn->right;
		}
	}
	return pn;
}

pInterval_tree min_interval_search(pInterval_tree pn,pInterval_tree pi)//搜索最小的区间
{
	if(pn!=nil && pn->left->max>=pi->low){
		pInterval_tree py=min_interval_search(pn->left,pi);
		if (py!=nil){
			return py;
		}else if(pn->low<=pi->high && pi->low<=pn->high){
			return pn;
		}else{
			return nil;
		}
	}else if(pn->low<=pi->high && pi->low<=pn->high){
		return pn;
	}else{
		return min_interval_search(pn->right,pi);
	}
}

void interval_search_all(pInterval_tree pn,pInterval_tree pi)//搜索所以重叠区间
{
	if(pn !=nil && pn->low<=pi->high && pi->low<=pn->high){
		cout<<"["<<pn->low<<","<<pn->high<<"]"<<"  ";
	}
	if(pn->left !=nil && pn->left->max>=pi->low){//查找左子树
		interval_search_all(pn->left,pi);
	}
	if(pn->right !=nil && pn->right->max>=pi->low){//查找右子树
		interval_search_all(pn->right,pi);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	nil=new interval_tree;
	nil->rb=0;
	nil->max=numeric_limits<int>::min();//最小值
	nil->left=nil;
	nil->right=nil;
	pInterval_tree pn=nil;
	int n=10;
	build_interval_tree(pn,n);
	InOrder(pn);
	cout<<endl;
	pInterval_tree pt=new interval_tree;//待搜索区域
	pInterval_tree pr=nil;//存储搜索结果
	int low=rand()%101-50;
	int high=rand()%101-50;
	if(low>high){//若low>high,则交换
		low+=high;
		high=low-high;
		low-=high;
	}
	pt->low=low;
	pt->high=high;
	pr=interval_search(pn,pt);
	cout<<"search area : ["<<pt->low<<","<<pt->high<<"]";
	if(pr!=nil){
		cout<<" founded -> ";
		cout<<"["<<pr->low<<","<<pr->high<<"]"<<"\t";
		pr=min_interval_search(pn,pt);
		cout<<"["<<pr->low<<","<<pr->high<<"]"<<endl;
		interval_search_all(pn,pt);
	}else{
		cout<<"not found"<<endl;
	}
}
