#include <iostream>
#include <ctime>
#include <limits>
#include <boost/timer/timer.hpp>
using namespace boost::timer;
using namespace std;

int partition(double *a,int low,int high)
{
	double key=a[high];
	int p=low-1;
	double tmp;
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

void quick_sort_partition(double *a,int low,int high)
{
	if(low<high){
		int q=partition(a,low,high);
		quick_sort_partition(a,low,q-1);
		quick_sort_partition(a,q+1,high);
	}	
}

int random_parition(double *a,int low,int high)
{
	int index=rand()%(high-low+1)+low;
	double tmp=a[index];
	a[index]=a[high];
	a[high]=tmp;
	return partition(a,low,high);
}

double random_select(double *a,int low,int high,int index)
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

double find_weight_median(double *a,int low,int high,double w_l,double w_r)//计算带权中位数
{
	if(high==low){
		return a[low];
	}else{
		int k=(low+high)/2;
		random_select(a,low,high,k+1);//查找第k+1小的元素
		double sum_l=w_l,sum_r=w_r;		   
		for(int i=low;i<k;++i){
			sum_l+=a[i];//中位数左边权重值之和
		}
		for(int i=k+1;i<=high;++i){
			sum_r+=a[i];//中位数右边权重值之和
		}
		if(sum_l<0.5 && sum_r<=0.5){
			return a[k];
		}else if(sum_l>=0.5){
			w_r=sum_r;
			return find_weight_median(a,low,k-1,w_l,w_r+a[k]);
		}else{
			w_l=sum_l;
			return find_weight_median(a,k+1,high,sum_l+a[k],w_r);
		}
	}
}


void random_weight_number(double *a,int n)//随机生成n个和为1的浮点数
{
	double *b=new double[n];
	b[n-1]=1;
	for(int i=0;i<n-1;++i){
		b[i]=(double) rand() / (RAND_MAX);
	}
	quick_sort_partition(b,0,n-1);
	a[0]=b[0];
	for(int i=1;i<n;++i){
		a[i]=b[i]-b[i-1];		
	}
	delete [] b;
}


int main()
{
	srand((unsigned)time(NULL));
	int count;
	while (count=rand()%10,count<3);
	count=20000;
	double *a=new double[count];	
	
	random_weight_number(a,count);//随机生成count个和为1的浮点数
	//a[0]=0.014,a[1]=0.047,a[2]=0.05,a[3]=0.09,a[4]=0.095,a[5]=0.126,a[6]=0.128,a[7]=0.133,a[8]=0.134,a[9]=0.183;
	//a[0]=0.012,a[1]=0.064,a[2]=0.154,a[3]=0.33,a[4]=0.44;
	//a[0]=0.1,a[1]=0.35,a[2]=0.05,a[3]=0.1,a[4]=0.15,a[5]=0.05,a[6]=0.2;
	
	double weight_median= find_weight_median(a,0,count-1,0,0);
	cout<<weight_median<<endl;
	quick_sort_partition(a,0,count-1);
	for(int i=0;i<count;++i){
		cout<<a[i]<<"\t";
	}
	cout<<endl;

	delete[]a;
}
