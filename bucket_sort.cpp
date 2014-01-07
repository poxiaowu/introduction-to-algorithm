//桶排序
#include <iostream>
#include <ctime>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;

typedef struct node{//数组联合指针的节点
	int value;
	node *next;
}node ,*pNode;

void find_max_min(int *a,int &max,int &min,int n)//查找最大值
{
	max=a[0],min=a[0];//寻找最大最小值
	for(int i=1;i<n;++i){
		if(max<a[i]){
			max=a[i];
		}else if(min>a[i]){
			min=a[i];
		}
	}
}

void inserting_sort(node *c,int b)
{//c是带插入的桶，b是待插入的节点
	//node *cur=c;
	node *inse=new node;//为b元素生成一个节点
	inse->value=b;
	if(c->next==NULL){
		c->next=inse;
		inse->next=NULL;
	}else{
		while ((c->next->value)<(b)){
			c=c->next;
		}
		inse->next=c->next;
		c->next=inse;
	}
}

void bucket_sort(int *a,int n)//桶排序
{
	int max,min;
	find_max_min(a,max,min,n);//找出节点的最大最小值

	int count=max-min+1;
	pNode *c=new pNode[count];//生成count个桶
	for(int i=0;i<count;++i){
		c[i]=new node;
		c[i]->value=min+i;//存储值,正负数同等对待处理,每个桶的初始值
		c[i]->next=NULL;//置空
	}
	int index;
	for(int i=0;i<n;++i){
		index=floor(a[i]);
		inserting_sort(c[index-min],a[i]);		
	}

	node *ptr;//控制指针
	node *pDl;//删除节点指针
	int k=0;
	for(int i=0;i<count;++i){
		ptr=c[i]->next;
		pDl=c[i];
		while (ptr!=NULL){
			a[k++]=ptr->value;
			pDl=ptr;//删除元素的指针
			ptr=ptr->next;
			delete pDl;
		}
	}	
	delete [] c;
}

void same_elem_quick_sort(int *a,int low,int high)//考虑相同元素的情况
{
	if(low<high){
		int pivot=a[low];
		int i=low,h=low;
		for(int j=low+1;j<high;++j){
			if(a[j]<pivot){
				int y=a[j];
				a[j]=a[h+1];
				a[h+1]=a[i];
				a[i]=y;
				++h,++i;
			}else if(a[j]==pivot){
				int y=a[j];
				a[j]=a[h+1];
				a[h+1]=y;
				++h;
			}
		}
		same_elem_quick_sort(a,low,i);
		same_elem_quick_sort(a,h+1,high);
	}
}

int max_bit(int max,int min)//返回基数排序的最大位数
{
	int bits=1;
	while ((max/10)||(min/10)){//考虑为负数的情况
		bits++;
		max/=10,min/=10;
	}
	return bits;
}

void counting_sort(int *a,int *b,int n)//计数排序
{
	int min,max;
	find_max_min(a,max,min,n);//寻找最大最小值
	int count=max-min+1;//计算c数组的大小
	int *c=new int[count];
	memset(c,0,count*sizeof(int));//初始化为0

	for(int i=0;i<n;++i){
		c[a[i]-min]++;//个数加1
	}

	for(int i=1;i<count;++i){
		c[i]+=c[i-1];
	}

	for(int i=n-1;i>=0;--i){
		b[c[a[i]-min]-1]=a[i];//c数组从0开始，但是值可正可负
		c[a[i]-min]--;        //所以要将最小值的下标调整到0.
	}
	delete[]c;
}

void radix_sort(int *a,int n)//基数排序
{
	int min,max;//存储最大最小值
	find_max_min(a,max,min,n);//寻找最大最小值
	int bits=max_bit(max,min);//返回基数排序最大循环次数
	int radix=1;
	int *s=new int[n];//存储每轮的数据
	int *b=new int[n];//存储每轮排序后的数据，并将其转移到a中
	for(int i=0;i<bits;++i,radix*=10){

		//for(int i=0;i<n;++i){//输出每轮基数排序后a数组的值
		//	cout<<a[i]<<"\t";
		//}
		//cout<<endl;

		for(int j=0;j<n;++j){
			s[j]=(a[j]/radix)%10;//存储a的每位数据
			//cout<<s[j]<<"\t";
		}
		//cout<<endl;
		find_max_min(s,max,min,n);//早出s数组中的最大最小值
		int count=max-min+1;//计算c数组的大小
		int *c=new int[count];
		memset(c,0,count*sizeof(int));//初始化为0

		for(int i=0;i<n;++i){
			c[s[i]-min]++;//个数加1
		}
		for(int i=1;i<count;++i){
			c[i]+=c[i-1];
		}
		for(int i=n-1;i>=0;--i){
			b[c[s[i]-min]-1]=a[i];//c数组从0开始，但是值可正可负
			c[s[i]-min]--;        //所以要将最小值的下标调整到0.
		}

		for(int i=0;i<n;++i){
			a[i]=b[i];
		}

		delete[]c;
	}	
	delete[]s;
	delete[]b;
}


int main()
{
	srand(time(NULL));
	int count;
	while (count=rand()%10,count<4);
	count=20000000;
	int *a=new int[count];
	int *b=new int[count];
	int *c=new int[count];
	int *d=new int[count];
	int *e=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%20000001-10000000;
		b[i]=a[i];
		c[i]=b[i];
		d[i]=c[i];
		//cout<<a[i]<<"\t";
	}
	//cout<<endl;

	cpu_timer t1;
	t1.start();
	bucket_sort(a,count);//桶排序
	t1.stop();
	cout<<"bucket sort"<<endl;
	cout<<t1.format();	
	/*for(int i=0;i<count;++i){
		cout<<a[i]<<"\t";
	}
	cout<<endl;*/

	cpu_timer t2;
	t2.start();
	same_elem_quick_sort(b,0,count);//快速排序
	t2.stop();
	cout<<"quick sort"<<endl;
	cout<<t2.format();

	cpu_timer t3;
	t3.start();
	counting_sort(c,e,count);
	t3.stop();
	cout<<"counting sort"<<endl;
	cout<<t3.format();

	cpu_timer t4;
	t4.start();
	radix_sort(d,count);
	t4.stop();
	cout<<"radix sort"<<endl;
	cout<<t4.format();

	delete[]a;
	delete[]b;
	delete[]c;
	delete[]d;
	delete[]e;
}
