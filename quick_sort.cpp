#include <iostream>
#include <ctime>
#include <utility>
#include <boost/timer/timer.hpp>
using namespace boost::timer;
using namespace std;
void quick_sort_partition(int *a,int low,int high)//尾主元
{
	if(low<high){
		int pivot=a[high];
		int k=low-1;
		int tmp;
		for(int i=low;i<high;++i){
			if(a[i]<=pivot){
				++k;
				//swap(a[k],a[i]);
				tmp=a[i];//时间更快
				a[i]=a[k];
				a[k]=tmp;
			}
		}
		//swap(a[k+1],a[high]);
		tmp=a[high];
		a[high]=a[k+1];
		a[k+1]=tmp;

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

void insertion(int *a,int n)//插入排序
{
	int key,j;
	for(int i=1;i<n;++i){
		key=a[i];
		j=i-1;
		while (j>=0 && key<a[j]){
			a[j+1]=a[j];
			--j;
		}
		a[j+1]=key;
	}
}

void pre_quick_insert_sort(int *a,int low,int high,int k)//联合 快速排序与 插入排序
{
	if(high-low+1 > k){
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
		pre_quick_insert_sort(a,low,i-1,k);
		pre_quick_insert_sort(a,i+1,high,k);
	}
}

void randomize_quicksort(int *a,int low,int high)
{
	if(low<high){
		int rnd=rand()%(high-low+1)+low;
		//swap(a[rnd],a[high]);//随机交换元素值

		int tmp=a[high];
		a[high]=a[rnd];
		a[rnd]=tmp;

		int pivot=a[high];
		int i=low-1;
		for(int j=low;j<high;++j){
			if(a[j]<=pivot){
				++i;
				//swap(a[i],a[j]);
				tmp=a[j];
				a[j]=a[i];
				a[i]=tmp;
			}
		}
		//swap(a[i+1],a[high]);
		tmp=a[high];
		a[high]=a[i+1];
		a[i+1]=tmp;
		randomize_quicksort(a,low,i);
		randomize_quicksort(a,i+2,high);
	}
}

void hoare_partition(int *a,int low,int high)
{
	if(low<high){
		int pivot=a[low];
		int i=low-1,j=high+1;
		while (i<j){
			do{
				--j;
			}while(a[j]>pivot);
			do{
				++i;
			}while(a[i]<pivot);
			if(i<j){
				int tmp=a[j];
				a[j]=a[i];
				a[i]=tmp;
			}/*else{
				return j;
			}*/
		}

		hoare_partition(a,low,j);
		hoare_partition(a,j+1,high);		
	}
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


int main()
{
	srand(time(NULL));
	int count;
	while((count=(rand()%30))<10);
	count=10000;
	int *a=new int[count];
	int *b=new int[count];
	int *c=new int[count];
	int *d=new int[count];
	int *e=new int[count];
	int *f=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%10001-5000;
		b[i]=a[i];
		c[i]=b[i];
		d[i]=c[i];
		e[i]=d[i];
		f[i]=e[i];
		//cout<<a[i]<<" ";
	}
	//cout<<endl;

	cpu_timer t1;
	t1.start();
	quick_sort_partition(a,0,count-1);
	t1.stop();
	/*for(int i=0;i<count;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;*/
	cout<<t1.format();

	cpu_timer t2;
	t2.start();
	quick_sort_partition_head(b,0,count-1);
	t2.stop();
	/*for(int i=0;i<count;++i){
		cout<<b[i]<<" ";
	}
	cout<<endl;*/
	cout<<t2.format();

	cpu_timer t4;
	t4.start();
	pre_quick_insert_sort(d,0,count-1,log(count)/log(2));
	insertion(d,count);
	t4.stop();
	cout<<t4.format();
	/*for(int i=0;i<count;++i){
	cout<<d[i]<<" ";
	}
	cout<<endl;*/

	cpu_timer t3;
	t3.start();
	randomize_quicksort(c,0,count-1);
	t3.stop();
	//for(int i=0;i<count;++i){
	//	cout<<c[i]<<" ";
	//}
	//cout<<endl;
	cout<<t3.format();

	cpu_timer t5;
	t5.start();
	hoare_partition(e,0,count-1);
	t5.stop();
	cout<<t5.format();
	//for(int i=0;i<count;++i){
	//	cout<<e[i]<<" ";
	//}
	//cout<<endl;

	cpu_timer t6;
	t6.start();
	same_elem_quick_sort(f,0,count);
	t6.stop();
	cout<<t6.format();
	/*for(int i=0;i<count;++i){
		cout<<f[i]<<" ";
	}
	cout<<endl;*/

	delete[]a;
	delete[]b;
	delete[]c;
	delete[]d;
	delete[]e;
	delete[]f;
}