//桶排序
#include <iostream>
#include <ctime>

using namespace std;


typedef struct point_circle//圆内点的数据结构
{
	double x,y;//x,y坐标
	double r;  //半径
}point_circle, *ppoint_circle;

typedef struct node{//桶数据结构
	point_circle *value;
	node *next;
}node,*pNode;

void find_max_min(ppoint_circle *a,int &max,int &min,int n)//查找最大值
{
	max=static_cast<int>(a[0]->r*10),min=static_cast<int>(a[0]->r*10);//寻找最大最小值
	for(int i=1;i<n;++i){
		if(max<static_cast<int>(a[i]->r*10)){
			max=static_cast<int>(a[i]->r*10);
		}else if(min>static_cast<int>(a[i]->r*10)){
			min=static_cast<int>(a[i]->r*10);
		}
	}
}

void inserting_sort(node *c,point_circle *b)
{//c是带插入的桶，b是待插入的节点
	//node *cur=c;
	node *inse=new node;//为b元素生成一个节点
	inse->value=b;
	if(c->next==NULL){
		c->next=inse;
		inse->next=NULL;
	}else{
		while (c->next!=NULL&&(c->next->value->r)<b->r){
			c=c->next;
		}
		inse->next=c->next;
		c->next=inse;
	}
}

void bucket_sort(ppoint_circle *a,int n)//桶排序
{
	int max,min;
	find_max_min(a,max,min,n);//找出节点的最大最小值

	int count=max-min+1;
	pNode *c=new pNode[count];//生成count个桶
	for(int i=0;i<count;++i){
		c[i]=new node;
		c[i]->value=new point_circle;//初始化point_circle
		c[i]->value->r=min+i;//存储值,正负数同等对待处理,每个桶的初始值
		c[i]->next=NULL;//置空
	}
	int index;
	for(int i=0;i<n;++i){
		index=floor(static_cast<int>(a[i]->r*10));
		inserting_sort(c[index-min],a[i]);		
	}

	node *ptr;//控制指针
	int k=0;
	for(int i=0;i<count;++i){
		ptr=c[i]->next;
		while (ptr!=NULL){
			a[k++]=ptr->value;
			ptr=ptr->next;
		}
	}	
	delete [] c;
}

void equal_probability_distribution_in_circle(ppoint_circle *a,int n)
{
	srand((unsigned)time(NULL));        //在圆内产生(-1,1)的等概率的点
	for(int i=0;i<n;++i){
		double x=1,y=1,r=1;//初始值
		do{
			x=2.0*((double) rand() / (RAND_MAX))-1.0;//产生（-1,1)内的点
			y=2.0*((double) rand() / (RAND_MAX))-1.0;
			r=x*x+y*y;
			a[i]->x=x;
			a[i]->y=y;
			a[i]->r=r;
		}while (x==1.0 || y==1.0 ||x==-1.0 || y==-1.0 ||r>=1);
	}
}

int main()
{
	srand((unsigned)time(NULL)); 
	int count;
	while (count=rand()%10,count<4);
	count=500;
	
	ppoint_circle *a=new ppoint_circle[count];
	for(int i=0;i<count;++i){
		a[i]= new point_circle;
	}

	equal_probability_distribution_in_circle(a,count);

	for(int i=0;i<count;++i){
		cout<<a[i]->x<<"\t"<<a[i]->y<<"\t"<<a[i]->r<<endl;
	}
	cout<<endl;

	bucket_sort(a,count);

	cout<<"result is :"<<endl<<endl;
	for(int i=0;i<count;++i){
		cout<<a[i]->x<<"\t"<<a[i]->y<<"\t"<<a[i]->r<<endl;
	}
	cout<<endl;
	system("pause");
}
