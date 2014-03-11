#include <iostream>
#include <ctime>
#include<algorithm>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;

void lis(int *a,int *s,int *b,int n)//Longest Increasing Subsequence,最长单调递增子序列
{
	for(int l=1;l<n;++l){//最长子序列的长度取值范围
		//cout<<"l = "<<l<<endl;
		for(int i=0;i<l;++i){
			if(a[i]<a[l] && s[l]<s[i]+1){
				s[l]=s[i]+1;
				b[l]=i;//存储小于a[l]的最大值的索引
			}
			//cout<<s[l]<<"  ";
		}
		//cout<<endl;
	}
}

void print_lis(int *a,int *c,int *b,int ma,int n)
{
	int index;
	for(int i=0;i<n;++i){
		if(c[i]==ma){
			for(int j=i;j>=0;j=b[index]){
				cout<<a[j]<<"\t";
				index=j;
			}
			cout<<endl;
		}
	}
	cout<<endl;
}

int compare(const void *a,const void *b)//qsort比较谓词
{
	return (*(int *)a-*(int *)b);
}

int memo_lcs_length(int *a,int m,int *b,int n,int **c)//最长公共子序列方法求解最长单调递增子序列
{//递归的，自上而下
	if(c[m][n]!=numeric_limits<int>::min())
		return c[m][n];
	if(a[m-1]==b[n-1]){
		c[m][n]=memo_lcs_length(a,m-1,b,n-1,c)+1;
	}else{
		c[m][n]=max(memo_lcs_length(a,m-1,b,n,c),memo_lcs_length(a,m,b,n-1,c));
	}
	return c[m][n];
}

void print_lcs_recursive(int *a,int *b,int **c,int m,int n)
{
	if(m==0 || n==0)
		return;
	if((c[m][n]==c[m-1][n-1]+1)&& c[m][n]!=c[m-1][n] &&c[m][n]!=c[m][n-1]){
		print_lcs_recursive(a,b,c,m-1,n-1);
		cout<<a[m-1]<<"\t";
	}else if(c[m-1][n]>c[m][n-1]){
		print_lcs_recursive(a,b,c,m-1,n);
	}else{
		print_lcs_recursive(a,b,c,m,n-1);
	}
}

int binary_search(int *b,int key,int low,int high)//二叉搜索待插入点位置
{
	int mid;
	while (low<high){
		mid=(low+high)>>1;
		if(b[mid]<key){
			low=mid+1;
		}else if(b[mid]>key){
			high=mid;//最长单调递增子序列时，此处的high=mid
		}else{
			return mid;
		}
	}
	return low;
}

int minimum_lis(int *a,int *b,int n)//最小元素的最长递增子序列
{
	int len=0;
	b[len]=a[0];
	int pos;
	for(int i=1;i<n;++i){
		if(b[len]<a[i]){
			len++;
			b[len]=a[i];
		}else{
			pos=binary_search(b,a[i],0,len);
			b[pos]=a[i];
		}
	}
	return len;
}

int main()
{
	srand((unsigned)time(NULL));
	int n;
	while(n=rand()%53,n<30);
	/*n=48;
	int a[48]={36,14, -23, -26, -35, -44, 42, 11, 18, 35,
				10, -42, 45, -42, -19, -43, -9 ,-48, 49,-28 ,
				-31, 9, 18 ,19 ,14, 30 ,-35 ,42, -46,-50,
				38, 5, 22, 35, -19 ,-30, -18 ,35, -50,24 ,
				-7 ,-13, 15 ,-8 ,37 ,43, -44, 36};*/
	int *a=new int[n];
	for(int i=0;i<n;++i){//随机生成字符数组
			a[i]=rand()%101-50;
	}
	for(int i=0;i<n;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	int *c=new int [n];	
	int *b=new int [n];
	for(int j=0;j<n;++j){
		c[j]=1;
		b[j]=-1;
	}	
	cpu_timer t1;
	t1.start();
	lis(a,c,b,n);
	t1.stop();
	cout<<t1.format();
	int ma=*max_element(c,c+n);
	cout<<ma<<endl;//最长子字符串	
	print_lis(a,c,b,ma,n);
	delete[]c;
	delete[]b;

	int *d=new int[n];
	for(int i=0;i<n;++i){
		d[i]=a[i];
	}
	
	int **m=new int *[n+1];
	for(int i=0;i<n+1;++i){
		m[i]=new int [n+1];
	}
	for(int i=0;i<n+1;++i){
		m[i][0]=0;
	}
	for(int j=0;j<n+1;++j){
		m[0][j]=0;
	}
	for(int i=1;i<n+1;++i){
		for(int j=1;j<n+1;++j){
			m[i][j]=numeric_limits<int>::min();
		}
	}	
	cpu_timer t2;
	t2.start();
	qsort(d,n,sizeof(int),compare);
	for(int i=0;i<n;++i){
		cout<<d[i]<<" ";
	}
	cout<<endl;
	memo_lcs_length(a,n,d,n,m);
	t2.stop();
	cout<<t2.format();
	cout<<m[n][n]<<endl;
	print_lcs_recursive(a,d,m,n,n);
	cout<<endl;	
	delete []d;
	for(int i=0;i<n+1;i++){
		delete [] m[i];
	}
	delete [] m;

	int *e=new int[n];

	cpu_timer t3;
	t3.start();
	int size=minimum_lis(a,e,n);
	t3.stop();
	cout<<t3.format();
	cout<<size+1<<endl;
	for(int i=0;i<=size;++i){
		cout<<e[i]<<"\t";
	}
	cout<<endl;
	delete[]a;
	delete[]e;
}   
