#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
typedef struct fib_heap_node{//斐波那契堆结点
	int key;//结点值
	int degree;//结点度
	fib_heap_node *parent;//结点的父结点
	fib_heap_node *left;//结点的左兄弟,循环双链表
	fib_heap_node *right;//结点的右兄弟
	fib_heap_node *child;//结点的子结点,会使用双向链表链接
	bool mark;//判断子结点是否被删除
}fib_heap_node,*pfib_heap_node;

typedef struct fib_heap{//斐波那契堆
	pfib_heap_node min;//最小结点的指针
	int node_num;//斐波那契堆的结点总数
}fib_heap,*pfib_heap;

pfib_heap_node fib_heap_node_init(int key)//创建新的结点并初始化
{
	pfib_heap_node fib=new fib_heap_node;
	fib->key=key;
	fib->degree=0;
	fib->parent=NULL;
	fib->left=NULL;
	fib->right=NULL;
	fib->child=NULL;
	fib->mark=false;
	return fib;
}
void fib_heap_init(pfib_heap &fib)//斐波那契堆的初始化
{
	fib=new fib_heap;
	fib->min=NULL;
	fib->node_num=0;
}

void fib_heap_insert(pfib_heap &fib,int key)//斐波拉契堆插入数据
{
	pfib_heap_node pf_node=fib_heap_node_init(key);
	if(fib->min==NULL){
		fib->min=pf_node;
		fib->min->right=fib->min;//双向循环链表
		fib->min->left=fib->min;//双向循环链表
	}else{
		pf_node->right=fib->min->right;
		fib->min->right->left=pf_node;
		pf_node->left=fib->min;
		fib->min->right=pf_node;
		if(fib->min->key>key){//比较插入的关键字和当前的最小的关键字的大小
			fib->min=pf_node;
		}
	}
	++fib->node_num;
}

pfib_heap fib_heap_union(pfib_heap &fib1,pfib_heap &fib2)//合并2个堆
{//合并2个堆，合并他们的根的双向链表
	if(fib1->min==NULL){
		return fib2;
	}else{
		if(fib2->min!=NULL){
			pfib_heap_node ptmp=fib1->min->left;//保存该指针指
			fib2->min->left->right=fib1->min;
			fib1->min->left->right=fib2->min;
			fib1->min->left=fib2->min->left;
			fib2->min->left=ptmp;
			if(fib1->min->key<fib2->min->key){
				fib1->node_num+=fib2->node_num;//结点数增加
				return fib1;
			}
			fib2->node_num+=fib1->node_num;//结点数增加
			return  fib2;
		}
		return fib1;
	}
}

void print(pfib_heap fib)//打印结点信息
{
	pfib_heap_node pf_node=fib->min;
	do{
		cout<<pf_node->key<<" ";
		pf_node=pf_node->right;
	}while(pf_node!=fib->min);
	cout<<endl;
}

void fib_heap_link(pfib_heap &fib,pfib_heap_node px,pfib_heap_node py)//将px从根树上移除，并将其作为py的孩子结点
{
	//1.将px从斐波拉契堆的根链表移除
	px->left->right=px->right;
	px->right->left=px->left;
	//2.将px插入到py的孩子链表中
	if(py->child){//如果孩子结点存在
		px->right=py->child->right;
		py->child->right->left=px;	
		py->child->right=px;
		px->left=py->child;
	}else{//孩子结点不存在
		py->child=px;
		px->right=px;
		px->left=px;
	}
	//3.py的度增加1
	++py->degree;
	//4.mark为false
	py->mark=false;
}

void consolidate(pfib_heap &fib)//合并斐波拉契根链表
{
	int num=log(fib->node_num*1.0)/log(2.0)+1;//斐波拉契堆的根结点的度数
	pfib_heap_node *A=new pfib_heap_node[num];//数组A存储度为i的结点
	for(int i=0;i<num;++i){
		A[i]=NULL;//数组初始化
	}
	pfib_heap_node pfhn=fib->min;//pfhn指向最小值的结点
	pfib_heap_node py,ptmp;
	int degree;
	pfib_heap_node pfirst=fib->min;//链表头元素，以此判断链表是否循环完毕
	do{
		degree=pfhn->degree;//结点的度		
		while(A[degree]){//如果该度的结点存在
			py=A[degree];
			if(pfhn->key>py->key){//交换2个指针
				ptmp=py;
				py=pfhn;
				pfhn=ptmp;
				if(py==pfirst){
					pfirst=pfhn;//更新根链表中的第一个指针来判断循环是否应该结束 
				}
			}else{
				if(py==pfirst){//如果指针没有被交换，则将pfirst指向下一个结点的指针
					pfirst=py->right;
				}
			}
			fib_heap_link(fib,py,pfhn);//将py链接到pfhn结点上			
			A[degree]=NULL;
			++degree;
		}
		A[degree]=pfhn;

	}while((pfhn!=pfirst) && (pfhn=pfhn->right));
	fib->min=NULL;

	ptmp=pfirst->right;
	fib->min=pfirst;
	while(ptmp!=pfirst){
		if(ptmp->key<fib->min->key){
			fib->min=ptmp;
		}
		ptmp=ptmp->right;
	}	 
	//for(int i=0;i<num;++i){
	//	if(A[i]){
	//		if(fib->min==NULL){
	//			fib->min=A[i];
	//			pfhn=fib->min;//pfhn指针，指向根链表
	//			pfhn->right=pfhn;
	//			pfhn->left=pfhn;
	//		}else{
	//			A[i]->right=pfhn->right;
	//			pfhn->right->left=A[i];
	//			A[i]->left=pfhn;
	//			pfhn->right=A[i];
	//			if (fib->min->key>A[i]->key){
	//				fib->min=A[i];
	//			}
	//		}
	//	}
	//	A[i]=NULL;
	//}
	for(int i=0;i<num;++i){
		A[i]=NULL;
	}
	delete []A;
}

pfib_heap_node fib_heap_extract_min(pfib_heap &fib)//斐波那契堆的最小结点
{
	pfib_heap_node pf_node=fib->min;
	pfib_heap_node node,nodepa_ri,node_right;
	if(pf_node){
		node=pf_node->child;//指向最小结点的第一个子结点
		nodepa_ri=pf_node->right;//指向最小结点的右边的结点		
		if(node){//如果子结点存在
			node_right=node->left;//子结点双链表中的最后一个结点
			node_right->right=nodepa_ri;
			nodepa_ri->left=node_right;
			pf_node->right=node;
			node->left=pf_node;
			//将pf_node结点的父结点更新
			nodepa_ri=node;
		}
		pf_node->left->right=pf_node->right;//删除了fib->min结点
		pf_node->right->left=pf_node->left;

		if(pf_node==pf_node->right){
			fib->min=NULL;
			--fib->node_num;
		}else{
			fib->min=pf_node->right;
			--fib->node_num;
			consolidate(fib);
		}
	}
	return pf_node;
}

int main()
{
	srand((unsigned)time(NULL));
	int n=20;
	pfib_heap fib;//斐波那契堆
	fib_heap_init(fib);
	int key;
	//int v1[5]={18,47,5,23,81};
	for(int i=0;i<n;++i){
		key=rand()%100+1;
		//key=v1[i];
		cout<<key<<" ";
		fib_heap_insert(fib,key);
	}
	cout<<endl;
	pfib_heap fibb;//斐波那契堆
	fib_heap_init(fibb);
	//int v2[5]={78,43,13,89,90};
	for(int i=0;i<n;++i){
		key=rand()%100+1;
		//key=v2[i];
		cout<<key<<" ";
		fib_heap_insert(fibb,key);
	}
	cout<<endl;	
	pfib_heap result=fib_heap_union(fib,fibb);
	print(result);
	consolidate(result);
	pfib_heap_node pn;
	for(int i=0;i<n*2;++i){
		pn=fib_heap_extract_min(result);
		cout<<pn->key<<" ";
		delete pn;
	}
	cout<<endl;
}
