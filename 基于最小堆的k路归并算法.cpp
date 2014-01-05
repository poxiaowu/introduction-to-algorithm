//基于最小堆的K路归并算法
#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

typedef struct node{
	int value;
	node *next;
}node,*pNode;

typedef struct heap_list{
	node *curr;
	node *left;
	node *right;
};

void insert_node(node *head, node *nenode)//直接插入法，插入新节点
{
	node *cur=head;
	if(head->next==NULL){
		head->next=nenode;
	}else{
		while ((cur->next!=NULL)&&(cur->next->value<nenode->value)){
			cur=cur->next;
		}
		nenode->next=cur->next;
		cur->next=nenode;
	}
}

pNode delete_first_node(node *head)//删除链表第一个有效元素
{
	//node *cur=head;
	pNode min_value=NULL;
	if(head->next!=NULL){
		/*return ;
	}else{*/
		min_value=head->next;
		head->next=head->next->next;		
	}
	return min_value;//链表的最小值
}

void min_heapify(pNode *a,int i,int n)//维护最小堆
{
	int left=2*i+1;
	int right=2*i+2;
	int smallest=i;
	if(left<n && a[smallest]->value>a[left]->value){
		smallest=left;
	}
	if(right<n && a[smallest]->value>a[right]->value){
		smallest=right;
	}
	if(smallest!=i){
		pNode tmp=a[i];
		a[i]=a[smallest];
		a[smallest]=tmp;
		min_heapify(a,smallest,n);
	}
}

void build_min_heapify(pNode *a,int n)//建立最小堆
{
	for(int i=(n-1)/2;i>=0;--i){
		min_heapify(a,i,n);
	}
}

int heap_extract_min(pNode *a,int n)//获取堆的最小值，并更新堆
{
	int min_value=a[0]->value;
	if(a[0]->next!=NULL){
		a[0]=a[0]->next;
	}else{
		a[0]->value=numeric_limits<int>::max();
	}
	min_heapify(a,0,n);
	return min_value;
}


int main()
{
	srand(time(NULL));
	int count=10;
	int k;
	while (k=(rand()%6),k<3 || k>6);//k个链表
	int *size=new int[k];//每个链表的大小，不含首元素
	node *ptr;//节点指针
	pNode *pn=new pNode[k];//对k个链表初始化
	for(int i=0;i<k;++i){//k个链表的头节点
		pn[i]=new node;//初始化第i个链表
		pn[i]->value=numeric_limits<int>::min();
		pn[i]->next=NULL;
		while (size[i]=(rand()%10),size[i]<4);//第i个链表有size个元素
		for(int j=0;j<size[i];++j){
			ptr=new node;
			ptr->value=rand()%101-50;
			ptr->next=NULL;
			insert_node(pn[i],ptr);
		}
	}
	
	for(int i=0;i<k;++i){//输出k个链表的元素
		cout<<"list "<<i<<" has "<<size[i]<<" elements"<<endl;
		node *cur=pn[i]->next;
		while (cur->next!=NULL){
			cout<<cur->value<<" -> ";
			cur=cur->next;
		}
		cout<<cur->value;
		cout<<endl;
	}
	cout<<endl;

	pNode *min_heap=new pNode[k];//排序堆，用来存储每个链表的第一个元素

	for(int i=0;i<k;++i){//删除首节点后，输出k个链表的元素
		min_heap[i]=delete_first_node(pn[i]);//将最小元素存储在数组min_heap中
		//cout<<min_heap[i]->value<<"\t";
		/*while (pn[i]->next->next!=NULL){
			cout<<pn[i]->next->value<<" -> ";
			pn[i]=pn[i]->next;
		}
		cout<<pn[i]->next->value;
		cout<<endl;*/
	}
	//cout<<endl;

	build_min_heapify(min_heap,k);//建立最小堆

	int size_sum=0;
	for(int i=0;i<k;++i){//获取k个堆的元素总数
		size_sum+=size[i];
	}
	int min_val;//存储每次的最小值
	for(int i=0;i<size_sum;++i){
		min_val=heap_extract_min(min_heap,k);
		cout<<min_val<<"\t";
	}
	cout<<endl;
	
	delete [] size;
	for(int i=0;i<k;++i){
		delete [] pn[i];
	}
	delete[]pn;
	delete[] min_heap;
}
