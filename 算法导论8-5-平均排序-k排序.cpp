#include <iostream>
#include <ctime>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;

void quick_k_sort_partition(int *a,int low,int high,int interval)//快速排序
{
	if(low<high){		
			int key=a[low];
			int tmp;
			int p=low-interval;
			int m=high+interval;
			for(int i=low+interval;i<m;i+=interval){
				if(a[i]<key){
					p+=interval;
					tmp=a[i];
					a[i]=a[p];
					a[p]=tmp;
				}else if(a[i]>key){
					m-=interval;
					tmp=a[m];
					a[m]=a[i];
					a[i]=tmp;
					i-=interval;
				}			
			}
			quick_k_sort_partition(a,low,p,interval);
			quick_k_sort_partition(a,m,high,interval);
		}
}

void quick_k_sort(int *a,int low,int high,int interval)
{
	for(int co=0;co<interval;++co){
		int m=(high/interval)*interval;
		int h=(m+co<high)?(m+co):m-interval+co;
		quick_k_sort_partition(a,low+co,h,interval);
	}
}

int main()
{
	srand(time(NULL));
	int count;
	while(count=rand()%10,count<3);
	count=4;
	int *a=new int[count];
	for(int i=0;i<count;++i){
	a[i]=rand()%21-10;
	cout<<a[i]<<"\t";
	}
	cout<<endl;
	quick_k_sort(a,0,count,3);
	for(int i=0;i<count;++i){
		cout<<a[i]<<"\t";
	}
	cout<<endl;
	delete[]a;
}
