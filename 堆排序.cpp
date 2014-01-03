#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

void max_heapify(int *a,int i,int heap_size)//维护最大堆
{
	while (i<=heap_size/2)
	{
		int left=2*i+1,right=2*i+2;
		int largest=i;
		if(left<=heap_size && a[left]>a[i])
			largest=left;
		if(right<=heap_size && a[right]>a[largest])
			largest=right;
		if(largest != i){
			int tmp=a[i];
			a[i]=a[largest];
			a[largest]=tmp;
			i=largest;       //尾递归
		}	
		else//递归结束
			break;
		
	}
}

void build_max_heapify(int *a,int heap_size)//建堆
{
	for(int i=heap_size/2;i>=0;--i){
		max_heapify(a,i,heap_size);
	}
}

void heap_sort(int *a,int heap_size)//堆排序
{
	build_max_heapify(a,heap_size);//建堆
	int tmp;
	for(int i=heap_size;i>0;--i){
		tmp=a[i];//值交换
		a[i]=a[0];
		a[0]=tmp;
		--heap_size;
		max_heapify(a,0,heap_size);//堆维护
	}
}


int heap_extract_max(int *a,int heap_size)
{
	if(heap_size<0)
		cout<<"heap underflow";
	int max=a[0];
	a[0]=a[heap_size];
	--heap_size;
	max_heapify(a,0,heap_size);
	return max;
}

void heap_increase_key(int *a,int index,int key)//增加堆的某个元素的值
{
	if(a[index]>key)
		cout<<"new key smaller than current key";
	a[index]=key;
	while ((index>=0)&&(key>a[(index-1)/2])){
		//临时变量交换法
		/*int tmp=a[(index-1)/2];
		a[(index-1)/2]=a[index];
		a[index]=tmp;*/
		//insertion_sort变量赋值法
		a[index]=a[(index-1)/2];
		index=(index-1)/2;		
	}
	a[index]=key;//insertion_sort变量赋值法
	
}

void heap_delete(int *a,int i,int heap_size)
{
	if(i<0)
		cout<<"heap underflow";

	if(i>heap_size)
		cout<<"heap overflow";
	a[i]=a[heap_size];
	--heap_size;//元素个数减少一个
	if(a[i]>a[(i-1)/2]){//如果大于父亲节点
		heap_increase_key(a,i,a[i]);
	}else{
		max_heapify(a,i,heap_size);
	}

}

int main()
{
	srand(time(NULL));
	int count;
	while ((count=rand()%101)<10);
	count=10;
	int a[10]={16,14,10,8,7,9,3,2,4,1};
	/*int *a=new int[count];
	for(int i=0;i<count;++i){
	a[i]=rand()%101-50;
	cout<<a[i]<<" ";
	}
	cout<<endl;*/
	
	/*heap_sort(a,count-1);
	for(int i=0;i<count;++i){
	cout<<a[i]<<" ";
	}
	cout<<endl;*/

	build_max_heapify(a,count-1);
	for(int i=0;i<count;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;

	/*int ex_max=heap_extract_max(a,count-1);
	cout<<ex_max<<endl;
	for(int i=0;i<count-1;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;*/

	heap_increase_key(a,8,15);
	for(int i=0;i<count;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;

	heap_delete(a,2,count-1);
	for(int i=0;i<count-1;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;


	//int rnd=rand()%101-50;
	//delete[]a;
}
