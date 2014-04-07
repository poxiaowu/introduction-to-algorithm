#include<iostream>
#include <limits>
#include<ctime>
using namespace std;

void dynamic_0_1_knapsack(int *v,int *w,int **c,int n,int W)//0-1背包问题
{
	for(int j=0;j<=W;++j){//进行初始化操作
		c[0][j]=0;
	}
	for(int i=1;i<=n;++i){//i=1表示第一个物品时
		c[i][0]=0;
		for(int j=1;j<=W;++j){//j=1表示重量为1时的情况
			if(w[i-1]<=j){//wi<=w
				if(v[i-1]+c[i-1][j-w[i-1]]>c[i-1][j]){
					c[i][j]=v[i-1]+c[i-1][j-w[i-1]];
				}else{
					c[i][j]=c[i-1][j];
				}
			}else{//wi>w的情况
				c[i][j]=c[i-1][j];
			}
		}
	}
}

void print_0_1_knapsack(int *v,int *w,int **c,int n,int W)//打印0-1背包结果
{
	if(n>0){
		if(c[n][W]==v[n-1]+c[n-1][W-w[n-1]]){//此时n属于解决方案的一部分
			print_0_1_knapsack(v,w,c,n-1,W-w[n-1]);
			cout<<n<<"\t";
		}else{
			print_0_1_knapsack(v,w,c,n-1,W);//此时n-1不属于解决方案的一部分
			//cout<<n-1<<"\t";
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=8;
	int *v=new int[n];
	int *w=new int[n];
	int W=16;
	for(int i=0;i<n;++i){
		v[i]=rand()%5+1;//物品的价值
		w[i]=rand()%5+1;//物品的重量
	}
	int **c=new int *[n+1];
	for(int i=0;i<n+1;++i){//存放策略结果
		c[i]=new int [W+1];
	}
	for(int i=0;i<n;++i){
		cout<<v[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<w[i]<<" ";
	}
	cout<<endl;
	dynamic_0_1_knapsack(v,w,c,n,W);
	for(int i=0;i<=n;++i){
		for(int j=0;j<=W;++j){
			cout<<c[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	print_0_1_knapsack(v,w,c,n,W);
	cout<<endl;
	delete [] v;
	delete [] w;
	for(int i=0;i<n+1;++i){
		delete []c[i];
	}
	delete [] c;
}
