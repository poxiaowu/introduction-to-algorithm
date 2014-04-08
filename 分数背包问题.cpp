#include<iostream>
#include <limits>
#include<ctime>
#include <Windows.h>
using namespace std;

int partition(double *ration,int *v,int *w,int low,int high)//快速排序子程序
{
	double pivot=ration[high];
	int k=low-1;
	double tmp;
	int tmp2;
	for(int i=low;i<high;++i){
		if(pivot<=ration[i]){
			k++;
			tmp=ration[i];
			ration[i]=ration[k];
			ration[k]=tmp;

			tmp2=v[i];
			v[i]=v[k];
			v[k]=tmp2;

			tmp2=w[i];
			w[i]=w[k];
			w[k]=tmp2;
		}
	}
	tmp=ration[high];
	ration[high]=ration[k+1];
	ration[k+1]=tmp;

	tmp2=v[high];
	v[high]=v[k+1];
	v[k+1]=tmp2;

	tmp2=w[high];
	w[high]=w[k+1];
	w[k+1]=tmp2;
	return k+1;
}

void quick_sort(double *ration,int *v,int *w,int low,int high)//快速排序，安装活动的开始时间升序排序
{
	if(low<high){
		int index=partition(ration,v,w,low,high);
		quick_sort(ration,v,w,low,index-1);
		quick_sort(ration,v,w,index+1,high);
	}
}
void naive_fractional_knapsack(double *ration,int *v,int *w,double *r,int W,int n)//传统分数背包问题
{
	int sum=0;
	for(int i=0;i<n;++i){
		if(sum+w[i]<=W){
			sum+=w[i];//重量总和
			r[i]=1.0;
		}else if(sum<W && sum+w[i]>W){//第i个物品不能完整装下
			r[i]=1.0*(W-sum)/w[i];
			sum=W;
		}else{//后面的物品都不需要装下
			r[i]=0.0;
		}
	}
}
int random_partiton(double *ration,int *v,int *w,int low,int high)
{
	int index=rand()%(high-low+1)+low;
	double tmp;
	int tmp2;
	tmp=ration[index];
	ration[index]=ration[high];
	ration[high]=tmp;

	tmp2=v[index];
	v[index]=v[high];
	v[high]=tmp2;

	tmp2=w[index];
	w[index]=w[high];
	w[high]=tmp2;
	return partition(ration,v,w,low,high);
}

void random_select(double *ration,int *v,int *w,int low,int high,int index)//随机选择
{
	if(low==high){
		return ;
	}
	int q=random_partiton(ration,v,w,low,high);
	int k=q+1;
	if(k==index){
		return;
	}else if(k<index){
		return random_select(ration,v,w,q+1,high,index);
	}else{
		return random_select(ration,v,w,low,q-1,index);
	}
}

void median_fractional_knapsack(double *ration,int *v,int *w,double *r,int W,int low,int high)//中位数法的分数背包问题
{
	int sumG,sumL;
	int index;
	while(low<=high){//此处用中位数法，或者随机算法
		//index=((low+high)>>1);
		index=partition(ration,v,w,low,high);//首先分割
		//random_select(ration,v,w,low,high,index+1);
		sumG=0,sumL=0;
		for(int i=low;i<=index;++i){
			sumG+=w[i];
		}
		/*for(int i=low;i<=high;++i){
			cout<<ration[i]<<" ";
		}
		cout<<endl;*/
		if(sumG>W){
			high=index-1;
		}else if(sumG==W){
			for(int i=low;i<=index;++i){
				r[i]=1;
			}
			return;//返回结果
		}else{
			for(int i=low;i<=index;++i){
				r[i]=1;
			}
			low=index+1;
			W-=sumG;
		}
	}
	if(w[low]==W){
		r[low]=1.0;
	}else{
		r[low]=W*1.0/w[low];
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=20;
	int *v=new int[n];
	int *w=new int[n];
	double *ration=new double[n];//比值


	int *v2=new int[n];
	int *w2=new int[n];
	double *ration2=new double[n];//比值

	int W=40;
	/*v[7]=3,v[4]=3,v[2]=5,v[6]=4,v[1]=5,v[5]=4,v[3]=2,v[0]=2;
	w[7]=2,w[4]=2,w[2]=3,w[6]=3,w[1]=4,w[5]=4,w[3]=5,w[0]=5;*/
	for(int i=0;i<n;++i){
		v[i]=rand()%5+1;//物品的价值
		w[i]=rand()%5+1;//物品的重量
		ration[i]=v[i]*1.0/w[i];

		v2[i]=v[i];
		w2[i]=w[i];
		ration2[i]=ration[i];
	}
	DWORD start,end;
	start=GetTickCount();
	quick_sort(ration,v,w,0,n-1);//快速排序
	for(int i=0;i<n;++i){
		cout<<ration[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<v[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<w[i]<<" ";
	}
	cout<<endl;
	double *r=new double[n];//存放每个最后放到背包里的百分比
	naive_fractional_knapsack(ration,v,w,r,W,n);//传统分数背包问题
	end=GetTickCount();
	for(int i=0;i<n;++i){
		cout<<r[i]<<" ";
		r[i]=0.0;
	}
	cout<<endl;
	cout<<end-start<<" ms"<<endl;
	cout<<endl<<endl;
	start=GetTickCount();
	median_fractional_knapsack(ration2,v2,w2,r,W,0,n-1);//中位数法
	end=GetTickCount();
	
	for(int i=0;i<n;++i){
		cout<<ration2[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<v2[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<w2[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<r[i]<<" ";
	}
	cout<<endl;
	cout<<end-start<<" ms"<<endl;
	delete [] v;
	delete [] w;
	delete [] ration;
	delete [] v2;
	delete [] w2;
	delete [] ration2;
	delete [] r;
}
