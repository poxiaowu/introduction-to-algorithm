#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

typedef struct min_heap{//最小堆
	int value;
	min_heap *left,*right;//左右结点
}min_heap,*pmin_heap;

typedef struct list{//双向链表实现栈
	int value;
	list *next;
	list *prev;
}list ,*plist;

typedef struct stack{//栈，用于打印哈夫曼编码编码
	list *top;
	list *front;//指向最开始的元素
}stack,*pstack;

void init(pstack &ps)//初始化栈
{
	ps=new stack;
	ps->top=NULL;
}

void push(pstack &ps,int value)//入栈
{
	plist pl;
	pl=new list;
	pl->value=value;
	pl->next=NULL;
	pl->prev=ps->top;//前向指针
	if(ps->top){
		ps->top->next=pl;
	}
	if(ps->top==NULL){
		ps->front=pl;
	}
	ps->top=pl;	
}

void popup(pstack &ps)
{
	plist pl;
	if(ps->top){
		pl=ps->top;
		ps->top=ps->top->prev;
		delete pl;//删除结点元素
	}
}


void min_heapify(pmin_heap *&a,int i,int heap_size)//维护最小堆
{
	while(i<heap_size/2){
		if(i<0){
			cout<<"heap underflow"<<endl;
			return;
		}
		if(i>heap_size){
			cout<<"heap overflow"<<endl;
			return;
		}
		int left=2*i+1;
		int right=2*i+2;
		int smallest=i;
		if(left<heap_size &&a[left]->value<a[i]->value){
			smallest=left;
		}
		if(right<heap_size && a[right]->value<a[smallest]->value){
			smallest=right;
		}
		if(smallest != i){
			pmin_heap tmp=a[smallest];
			a[smallest]=a[i];
			a[i]=tmp;
			i=smallest;
		}else{
			break;
		}
	}
}

void build_min_heapify(pmin_heap *&a,int heap_size)//建立最小堆
{
	for(int i=heap_size/2-1;i>=0;--i){
		min_heapify(a,i,heap_size);
	}
}

void insert_min_heapify(pmin_heap *&a,pmin_heap key,int &heap_size,int n)//插入元素
{//heap_size是最小堆的大小,n是数组的大小
	if(heap_size<0){
		cout<<"heap underflow"<<endl;
	}
	if(heap_size==n){
		cout<<"heap overflow"<<endl;
	}
	int i=heap_size;
	while(i>0 &&(i-1)/2>=0 && key->value<a[(i-1)/2]->value){
		a[i]=a[(i-1)/2];
		i=(i-1)/2;
	}
	a[i]=key;//插入元素
	++heap_size;
}

pmin_heap extract_min(pmin_heap *&a,int &heap_size)//获取最小堆的最小的元素
{
	if(heap_size<0){
		cout<<"heapify underflow"<<endl;
	}
	pmin_heap result=a[0];
	a[0]=a[heap_size-1];
	--heap_size;
	min_heapify(a,0,heap_size);
	return result;
}

pmin_heap huffman(pmin_heap *&a,int &heap_size,int n)//哈夫曼编码
{
	pmin_heap phroot=NULL;
	pmin_heap phz=NULL;
	pmin_heap phx=NULL,phy=NULL;
	for(int i=0;i<n-1;++i){
		phx=extract_min(a,heap_size);
		phy=extract_min(a,heap_size);
		phz=new min_heap;
		phz->value=phx->value+phy->value;
		phz->left=phx;
		phz->right=phy;
		insert_min_heapify(a,phz,heap_size,n);//插入新元素
	}
	return extract_min(a,heap_size);
}

void travel_heapify(pmin_heap &root,pstack &pst)//只访问子结点，并打印出其哈夫曼编码的信息
{
	if(root){
		if(root->left && root->right){
			push(pst,0);
			travel_heapify(root->left,pst);
			popup(pst);
			push(pst,1);
			travel_heapify(root->right,pst);
			popup(pst);
		}else{
			cout<<root->value<<" : ";
			plist pt=pst->front;
			while(pt){
				cout<<pt->value;
				pt=pt->next;
			}
			cout<<endl;
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=20;
	pmin_heap *aph=new pmin_heap[n];
	int tmp;
	for(int i=0;i<n;++i){
		tmp=rand()%21;
		aph[i]=new min_heap;
		aph[i]->value=tmp;
		aph[i]->left=NULL;
		aph[i]->right=NULL;
		cout<<tmp<<" ";
	}
	cout<<endl;
	build_min_heapify(aph,n);
	for(int i=0;i<n;++i){
		cout<<aph[i]->value<<" ";
	}
	cout<<endl;
	pmin_heap root=huffman(aph,n,n);
	pstack pst;
	init(pst);//堆栈
	travel_heapify(root,pst);
	cout<<endl;
	for(int i=0;i<n;++i){
		delete [] aph[i];
	}
	delete [] aph;
}
