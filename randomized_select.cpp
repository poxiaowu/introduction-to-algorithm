#include <iostream>
#include <ctime>
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
	return p+1;
}

int random_partition(int *a,int low,int high)//随机化快速排序
{
	int rnd=rand()%(high-low)+low;//随机生成
	int tmp=a[high];
	a[high]=a[rnd];
	a[rnd]=tmp;
	return partition(a,low,high);	
}

int random_select(int *a,int low,int high,int index)
{
	if(low == high){
		return a[low];
	}
	int p=random_partition(a,low,high);
	int k=p-low+1;
	if(k==index)
		return a[p];
	else if(k<index){
		return random_select(a,p+1,high,index-k);
	}else{
		return random_select(a,low,p-1,index);
	}
}

int random_select_recursive(int *a,int low,int high,int index)
{
	while (low<=high)
	{
		if(low==high)
			return a[low];
		else{
			int p=random_partition(a,low,high);
			int k=p-low+1;
		
			if(index>k){
				low=p+1;
				index-=k;
			}else if(index<k){
				high=p-1;
			}
			else
				return a[p];
			}
	}	
	return 0;
}


int main()
{
	srand((unsigned)time(NULL));
	int count;
	while (count=rand()%10,count<3);
	count=10;
	int *a=new int[count];
	int *b=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%21-10;
		b[i]=a[i];
		cout<<a[i]<<"\t";
	}
	cout<<endl;
	int v=random_select(a,0,count-1,3);
	cout<<v<<endl;
	v=random_select_recursive(a,0,count-1,3);
	cout<<v<<endl;
	delete[]a;
	delete[]b;
}
