#include <iostream>
#include<ctime>
using namespace std;

void insertion_sort(int *a,int n)//直接插入 O(n*n)
{
	int key;
	int j;
	for(int i=1;i<n;++i){
		key=a[i];
		j=i-1;
		while(j>=0 && key<a[j]){
			a[j+1]=a[j];
			--j;
		}
		a[j+1]=key;
	}
}


int binary_search(int *a,int low,int high,int x)//迭代法二分查找
{
	int mid=0;
	while(low<=high){
		mid=(low+high)>>1;
		if(x==a[mid])
			return mid+1;
		else if(x<a[mid]){
			high=mid-1;
		}else{
			low=mid+1;
		}		
	}
	
	return ((low+high)>>1) + 1;
}


void binary_insertion_sort(int *a,int n)//二分插入排序 O(n*n*lgn)
{
	int key;
	int j;
	for(int i=1;i<n;++i){
		key=a[i];
		int pos=i-binary_search(a,0,i-1,a[i]);
		j=i-1;
		while (pos-- && j>=0){
			a[j+1]=a[j];
			--j;
		}
		a[j+1]=key;
	}
}





int main()
{
	srand(time(NULL));
	int count=rand()%20;
	//count=5;
	int *a=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%100;
		cout<<a[i]<<" ";
	}
	cout<<endl;

	binary_insertion_sort(a,count);

	for(int j=0;j<count;++j)
		cout<<a[j]<<" ";
	cout<<endl;
	
}
