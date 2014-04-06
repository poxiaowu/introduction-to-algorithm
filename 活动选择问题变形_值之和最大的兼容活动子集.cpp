#include<iostream>
#include <limits>
#include<ctime>
using namespace std;

void dynamic_max_value_activity_selector(int *s,int *f,int *val,int **c,int **act,int n)//动态规划-自底向上
{
	for(int i=0;i<n;++i){
		c[i][i]=0;//如果只有一个元素，则两者之间最长的活动只有0个
		c[i][i+1]=0;
	}
	c[n][n]=0;
	int j,k;
	for(int l=2;l<=n;++l){//活动区间
		for(int i=0;i<n-l+1;++i){
			j=i+l;
			k=j-1;
			c[i][j]=0;
			while (f[k]>f[i]){
				if(f[i]<=s[k] && f[k]<=s[j] && c[i][k]+c[k][j]+val[k]>c[i][j]){
					 c[i][j]=c[i][k]+c[k][j]+val[k];
					 act[i][j]=k;
				}
				--k;
			}
		}
	}
}
void print_activity(int **act,int l,int h)
{
	int k=act[l][h];
	if(k){
		print_activity(act,l,k);
		cout<<k<<"\t";
		print_activity(act,k,h);
	}
}

void quick_sort(int *s,int *f,int *val,int low,int high)//快速排序，安装活动的开始时间升序排序
{
	while (low<high){
		int pivot=s[high];
		int k=low-1;
		int tmp;
		for(int i=low;i<high;++i){
			if(s[i]<=pivot){
				++k;
				tmp=s[i];
				s[i]=s[k];
				s[k]=tmp;
				tmp=f[i];
				f[i]=f[k];
				f[k]=tmp;
				tmp=val[i];
				val[i]=val[k];
				val[k]=tmp;
			}
		}
		tmp=s[high];
		s[high]=s[k+1];
		s[k+1]=tmp;
		tmp=f[high];
		f[high]=f[k+1];
		f[k+1]=tmp;
		tmp=val[high];
		val[high]=val[k+1];
		val[k+1]=tmp;
		if((k-low)<(high-k-2)){//栈深度为O(lgn)
			quick_sort(s,f,val,low,k);		
			low=k+2;
		}else{
			quick_sort(s,f,val,k+2,high);
			high=k;
		}
	}
}

void sort_final_time(int *s,int *f,int *val,int n)//按照结束时间排序
{
	int low=0,high=0,tmp,tmpval;
	for(int i=1;i<=n;++i){
		if(s[i]!=s[i-1]){
			low=i;
		}else{
			high=i;
			tmp=f[i];
			tmpval=val[i];
			while (high>low && tmp<f[high-1]){//开始时间相同，结束时间进行插入排序
				f[high]=f[high-1];
				val[high]=val[high-1];
				--high;
			}
			f[high]=tmp;
			val[high]=tmpval;
			/*for(int j=low;j<=i;++j){
				cout<<s[j]<<" ";
			}
			cout<<endl;
			for(int j=low;j<=i;++j){
				cout<<f[j]<<" ";
			}
			cout<<endl;*/
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=11;
	int *s=new int[n];
	int *f=new int[n];
	int *val=new int[n];
	s[0]=0,f[0]=0,s[n-1]=numeric_limits<int>::max(),f[n-1]=numeric_limits<int>::max();
	for(int i=1;i<n-1;++i){
		s[i]=rand()%n+1;//活动i开始时间
		f[i]=rand()%(n/2)+1+s[i];//活动i结束时间
		val[i]=rand()%11-2;//为每个活动添加一个收益值
	}
	quick_sort(s,f,val,0,n-1);//按照开始时间排序
	sort_final_time(s,f,val,n-1);//按照结束时间排序

	for(int i=1;i<n-1;++i){
		cout<<s[i]<<"\t";
	}
	cout<<endl;
	for(int i=1;i<n-1;++i){
		cout<<f[i]<<"\t";
	}
	cout<<endl;
	for(int i=1;i<n-1;++i){
		cout<<val[i]<<"\t";
	}
	cout<<endl;

	int **c=new int*[n];//
	for(int i=0;i<n;++i){
		c[i]=new int[n];
	}
	int **act=new int*[n];
	for(int i=0;i<n;++i){
		act[i]=new int[n];
		for(int j=0;j<n;++j){
			act[i][j]=0;
		}
	}
	dynamic_max_value_activity_selector(s,f,val,c,act,n-1);//动态规划-自底向上
	print_activity(act,0,n-1);
	cout<<endl;
	delete []s;
	delete []f;
	for(int i=0;i<n;++i){
		delete [] c[i];
		delete [] act[i];
	}
	delete [] c;
	delete [] val;
	delete [] act;
}
