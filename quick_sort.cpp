#include <iostream>
#include <ctime>
#include <utility>
using namespace std;
void quick_sort_partition(int *a,int low,int high)//尾主元
{
	if(low<high){
		int pivot=a[high];
		int k=low-1;
		int p=low;
		for(int i=low;i<high;++i){
			if(a[i]<=pivot){
				++k;
				swap(a[k],a[i]);
			}
		}
		swap(a[k+1],a[high]);

		quick_sort_partition(a,low,k);
		quick_sort_partition(a,k+2,high);
	}
}


void quick_sort_partition_head(int *a,int low,int high)//首主元
{
	if(low<high){
		int pivot=a[low];
		int i=low,j=high;
		while (i<j){
			while (i<j && pivot<a[j]){
				--j;
			}
			if(i<j){
				a[i]=a[j];
				++i;
			}

			while (i<j && a[i]<pivot){
				++i;
			}
			if(i<j){
				a[j]=a[i];
				--j;
			}
		}
		a[i]=pivot;
		quick_sort_partition_head(a,low,i-1);
		quick_sort_partition_head(a,i+1,high);
	}
}

int main()
{
	srand(time(NULL));
	int count;
	while((count=(rand()%30))<10);
	int *a=new int[count];
	int *b=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%101-50;
		b[i]=a[i];
		cout<<a[i]<<" ";
	}
	cout<<endl;

	
	quick_sort_partition(a,0,count-1);
	for(int i=0;i<count;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	
	quick_sort_partition_head(b,0,count-1);
	for(int i=0;i<count;++i){
		cout<<b[i]<<" ";
	}
	cout<<endl;

	delete[]a;
	delete[]b;
}
