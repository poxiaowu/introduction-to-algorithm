#include <iostream>
#include <ctime>
#include <boost/timer/timer.hpp>
using namespace boost::timer;
using namespace std;

int partition(int *a,int low,int high)//快速排序分割
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

	/*for(int i=low;i<=high;i++){
	cout<<a[i]<<"\t";
	}
	cout<<endl;*/

	return p+1;
}

int random_partition(int *a,int low,int high)//随机化快速排序
{
	int rnd=rand()%(high-low+1)+low;//随机生成
	int tmp=a[high];
	a[high]=a[rnd];
	a[rnd]=tmp;
	return partition(a,low,high);	
}

int random_select(int *a,int low,int high,int index)
{
	if(low==high)
		return a[low];
	int q=random_parition(a,low,high);
	int k=q+1;

	/*for(int i=low;i<=high;++i)
		cout<<a[i]<<"\t";
	cout<<endl;*/

	if(k==index){
		return a[q];
	}
	else if(k<index){
		return random_select(a,q+1,high,index);
	}else{
		return random_select(a,low,q-1,index);
	}
}


void best_case_quicksort(int *a,int low,int high)
{
	if(low<high){
		int index=((low+high)>>1);
		random_select(a,low,high,index);//取中位数
		//int q = partition(a,low,high);
		best_case_quicksort(a,low,index-1);
		best_case_quicksort(a,index+1,high);
	}
}

void naive_quicksort(int *a,int low,int high)
{
	if(low<high){
		int q = partition(a,low,high);
		naive_quicksort(a,low,q-1);
		naive_quicksort(a,q+1,high);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int count;
	while (count=rand()%10,count<3);
	count=10000000;
	int *a=new int[count];
	int *b=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%10000001-5000000;
		b[i]=a[i];
		//cout<<a[i]<<"\t";
	}
	cout<<endl;

	cpu_timer t1;
	t1.start();
	naive_quicksort(a,0,count-1);
	t1.stop();
	cout<<t1.format();

	////for(int i=0;i<count;i++){
	////	cout<<a[i]<<"\t";
	////}
	////cout<<endl;

	cpu_timer t2;
	t2.start();
	best_case_quicksort(b,0,count-1);
	t2.stop();
	/*for(int i=0;i<count;++i){
		cout<<b[i]<<"\t";
	}
	cout<<endl;*/
	cout<<t2.format();
	delete[]a;
	delete[]b;
}
