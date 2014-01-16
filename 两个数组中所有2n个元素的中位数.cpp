#include <iostream>
#include <ctime>
#include <limits>
#include <boost/timer/timer.hpp>
using namespace boost::timer;
using namespace std;

int partition(int *a,int low,int high)
{
	int key=a[high];
	int p=low-1;
	int tmp;
	for(int i=low;i<high;++i){
		if(a[i]<=key){
			p++;
			tmp=a[i];
			a[i]=a[p];
			a[p]=tmp;
		}
	}
	tmp=a[p+1];
	a[p+1]=key;
	a[high]=tmp;
	return p+1;
}

void quick_sort_partition(int *a,int low,int high)
{
	if(low<high){
		int q=partition(a,low,high);
		quick_sort_partition(a,low,q-1);
		quick_sort_partition(a,q+1,high);
	}	
}

int find_median(int *a,int *b,int lowA,int highA,int lowB,int highB)
{
	while (lowA<highA && lowB<highB)
	{	
		int kA=(lowA+highA+1)/2;
		int kB=(lowB+highB+1)/2;
		if(a[kA]<b[kB]){
			lowA=kA;
			highB=kB;
		}else if(a[kA]>b[kB]){
			highA=kA;
			lowB=kB;
		}else if((a[kA]==b[kB])/* && kA+kB==n*/){
			return a[kA];
		}
	}
	if(lowA==highA)
		return a[lowA];
	if(lowB==highB)
		return b[lowB];
}



int random_parition(int *a,int low,int high)
{
	int index=rand()%(high-low+1)+low;
	int tmp=a[index];
	a[index]=a[high];
	a[high]=tmp;
	return partition(a,low,high);
}

int random_select(int *a,int low,int high,int index)
{
	if(low==high)
		return a[low];
	if(low<high){
		int q=random_parition(a,low,high);
		int k=q+1;
		if(k==index){
			return a[q];
		}
		else if(k<index){
			return random_select(a,q+1,high,index);
		}else{
			return random_select(a,low,q-1,index);
		}
	}
}


int random_find_median(int *a,int *b,int lowA,int highA,int lowB,int highB)
{
	while (lowA<highA && lowB<highB)
	{	
		int kA=(lowA+highA+1)/2;
		int kB=(lowB+highB+1)/2;
		random_select(a,lowA,highA,kA+1);//选取A中位数
		random_select(b,lowB,highB,kB+1);//选取B中位数
		if(a[kA]<b[kB]){
			lowA=kA;
			highB=kB;
		}else if(a[kA]>b[kB]){
			highA=kA;
			lowB=kB;
		}else if((a[kA]==b[kB])/* && kA+kB==n*/){
			return a[kA];
		}
	}

	if(lowA==highA){
		random_select(a,lowA,highA,lowA+1);//选取A中位数		
		return a[lowA];
	}
	if(lowB==highB){
		random_select(b,lowB,highB,lowB+1);//选取B中位数
		return b[lowB];
	}
}

int find_median_two_array(int *a,int *b,int low,int high,int n)
{
	if(low>high){
		return numeric_limits<int>::min();
	}else{
		int k=(low+high)/2;
		if(k==n && a[k]<b[0]){
			return a[k];
		}
		else if(k<n && a[k]>=b[n-k] && a[k]<=b[n-k+1]){
			return a[k];
		}else if(a[k]>b[n-k+1]){
			return find_median_two_array(a,b,low,k-1,n);
		}else{
			return find_median_two_array(a,b,k+1,high,n);
		}
	}
}

int random_find_median_two_array(int *a,int *b,int low,int high,int n)
{
	if(low>high){
		return numeric_limits<int>::min();
	}else{
		int k=(low+high)/2;
		random_select(a,low,high,k+1);
		random_select(b,low,high,n-k+1);
		random_select(b,low,high,n-k+2);
		if(k==n && a[k]<b[0]){
			return a[k];
		}
		else if(k<n && a[k]>=b[n-k] && a[k]<=b[n-k+1]){
			return a[k];
		}else if(a[k]>b[n-k+1]){
			return random_find_median_two_array(a,b,low,k-1,n);
		}else{
			return random_find_median_two_array(a,b,k+1,high,n);
		}
	}
}

int two_array_median(int *a,int *b,int n)
{
	int median=find_median_two_array(a,b,0,n,n);
	if(median==numeric_limits<int>::min())
		median=find_median_two_array(b,a,0,n,n);
	return median;
}
int random_two_array_median(int *a,int *b,int n)
{
	int median=random_find_median_two_array(a,b,0,n,n);
	if(median==numeric_limits<int>::min())
		median=random_find_median_two_array(b,a,0,n,n);
	return median;
}


int main()
{
	srand((unsigned)time(NULL));
	int count;
	while (count=rand()%10,count<3);
	count=20000000;
	int *a=new int[count];
	int *b=new int[count];
	int *c=new int[count];
	int *d=new int[count];
	int *e=new int[count];
	int *f=new int[count];
	int *g=new int[count];
	int *h=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%400000001-200000000;
		b[i]=rand()%400000001-200000000;
		c[i]=a[i];
		d[i]=b[i];
		e[i]=a[i];
		f[i]=b[i];
		g[i]=a[i];
		h[i]=b[i];
	}

	cpu_timer t1;
	t1.start();
	quick_sort_partition(a,0,count-1);//对两个数组快速排序
	quick_sort_partition(b,0,count-1);//对两个数组快速排序
	
	/*for(int i=0;i<count;++i){
		cout<<a[i]<<"\t";
	}
	cout<<endl;
	for(int i=0;i<count;++i){
		cout<<b[i]<<"\t";
	}
	cout<<endl;*/
	
	int median=find_median(a,b,0,count-1,0,count-1);
	t1.stop();
	cout<<median<<endl;
	cout<<t1.format();

	cpu_timer t2;
	t2.start();
	median=random_find_median(c,d,0,count-1,0,count-1);
	t2.stop();
	cout<<median<<endl;
	cout<<t2.format();

	cpu_timer t3;
	t3.start();
	quick_sort_partition(e,0,count-1);//对两个数组快速排序
	quick_sort_partition(f,0,count-1);//对两个数组快速排序
	median=two_array_median(e,f,count-1);
	t3.stop();
	cout<<median<<endl;
	cout<<t3.format();

	cpu_timer t4;
	t4.start();
	median=random_two_array_median(g,h,count-1);
	t4.stop();
	cout<<median<<endl;
	cout<<t4.format();

	delete[]a;
	delete[]b;
	delete[]c;
	delete[]d;
	delete[]e;
	delete[]f;
	delete[]g;
	delete[]h;
}
