#include <iostream>
#include <limits>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;
int cut_rod(int *p,int n,int *result)
{
	if(n==0)
		return 0;
	int q =numeric_limits<int>::min();//q初始为最小值
	for(int i=0;i<n;i++){
		int val=p[i]+cut_rod(p,n-i-1,result);
		if(q<val){
			q=val;
			result[n]=i+1;
		}
	}
	return q;
}

void print_cut_rod(int *p, int n,int *result)
{
	cout<<cut_rod(p,n,result)<<endl;
	while (n>0){
		cout<<result[n]<<"\t";
		n-=result[n];
	}
}

int memo_cut_rod(int *r,int *p,int n,int *result)//备忘录法
{	
	if(n==0){//为0时返回
		return 0;
	}
	if(r[n-1]!=numeric_limits<int>::min()){//若该值已经存储，则直接返回，否则进行计算
		return r[n-1];
	}
	int q =numeric_limits<int>::min();//q初始为最小值
	for(int i=0;i<n;i++){
		int val=p[i]+memo_cut_rod(r,p,n-i-1,result);
		if (q<val){
			q=val;
			result[n]=i+1;
		}
	}
	r[n-1]=q;//创建备忘录
	return q;	
}

void print_memo_cut_rod(int *r,int *p,int n,int *result)
{
	cout<<memo_cut_rod(r,p,n,result)<<endl;
	while(n>0){
		cout<<result[n]<<"\t";
		n-=result[n];	
	}
}

int bottom_up_cut_rod(int *cos,int *p,int n,int *result)//自底向上法
{	
	int q;
	for(int i=1;i<=n;++i){
		q=numeric_limits<int>::min();
		for(int j=0;j<i;++j){
			if(q<p[j]+cos[i-j-1]){
				q=p[j]+cos[i-j-1];
				result[i]=j+1;
			}
		}
		cos[i]=q;
	}
	return cos[n];
}

void print_bottom_up_cut_rod(int *cos,int *p,int n,int *result)//打印bottom_up_cut_rod的信息
{
	cout<<bottom_up_cut_rod(cos,p,n,result)<<endl;
	while(n>0){
		cout<<result[n]<<"\t";
		n-=result[n];
	}
}


int main()
{
	int p[30]={1,5,8,9,10,17,18,20,24,30,
			33,35,38,39,43,47,48,50,54,60,
			63,66,68,69,72,77,78,80,84,90};//代价数组
	int n=29;
	int *cost=new int[n];
	for(int i=0;i<n;++i){
		cost[i]=numeric_limits<int>::min();
	}

	int *cos =new int[n+1];
	memset(cos,0,sizeof(int)*(n+1));
	int *result=new int[n+1];
	cpu_timer t3;
	t3.start();
	print_bottom_up_cut_rod(cos,p,n,result);
	cout<<endl;
	t3.stop();
	cout<<t3.format();
	delete cos;
	
	memset(result,0,sizeof(int)*(n+1));
	cpu_timer t2;
	t2.start();
	print_memo_cut_rod(cost,p,n,result);
	cout<<endl;
	t2.stop();
	cout<<t2.format();

	memset(result,0,sizeof(int)*(n+1));
	cpu_timer t1;
	t1.start();
	print_cut_rod(p,n,result);
	cout<<endl;
	t1.stop();
	cout<<t1.format();
	delete [] cost;
	delete [] result;
}
