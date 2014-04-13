#include <iostream>
#include <limits>
#include <ctime>
using namespace std;


void inventory_planning(int n,int m,int c,int D,int* d,int *h,int **cost,int **make)//库存规划
{
	int f,val;
	for(int s=0;s<=D;++s){//s stands for surplus
		f=max(d[n-1]-s,0);//第n个月应该生产的设备
		cost[n-1][s]=c*max(f-m,0)+h[s+f-d[n-1]];//第n个月，所需花费的代价
		make[n-1][s]=f;
	}
	int U=d[n-1];//每个月生产设备的上界
	for(int k=n-2;k>=0;--k){
		U+=d[k];//每个月可以生产设备的上限
		for(int s=0;s<=D;++s){//上个月剩余的机器数
			cost[k][s]=numeric_limits<int>::max();
			for(f=max(d[k]-s,0);f<=U-s;++f){
				val=cost[k+1][s+f-d[k]]+c*max(f-m,0)+h[s+f-d[k]];
				if(val<cost[k][s]){
					cost[k][s]=val;
					make[k][s]=f;
				}
			}		
		}	
	}
}


void print_plan(int **make,int *d,int n)
{
	int s=0;
	for(int i=0;i<n;++i){
		cout<<"For month "<<i<<" manufacture "<<make[i][s]<<"  machines"<<endl;
		s+=(make[i][s]-d[i]);
	}
}


int main()
{
	srand((unsigned)time(NULL));
	int n=5;
	int *d=new int[n];
	int sum=0;
	for(int i=0;i<n;++i){//每个月的需求
		d[i]=rand()%10+1;
		sum+=d[i];
	}
	int *h=new int[sum+1];
	h[0]=0;
	for(int i=1;i<=sum;++i){//保存i台设备的成本
		h[i]=h[i-1]+rand()%2+1;
	}
	int m=rand()%10+1;//每个月可以生产m台设备
	int **cost=new int *[n];
	int **make=new int *[n];
	for(int i=0;i<n;++i){
		cost[i]=new int [sum+1];	
		make[i]=new int [sum+1];
	}
	int c=rand()%5+1;//请一个工人的代价
	cout<<n<<" month and the demands of every month is :";
	for(int i=0;i<n;++i){
		cout<<d[i]<<" ";
	}
	cout<<endl;
	cout<<"every month the company could manufacture "<<m<<" devices"<<endl;
	cout<<"the cost of inventory is : ";
	for(int i=1;i<=sum;++i){
		cout<<h[i]<<" ";
	}
	cout<<endl;
	cout<<"the costs of labor is : "<<c<<endl;
	inventory_planning(n,m,c,sum,d,h,cost,make);	
	print_plan(make,d,n);

	delete [] d;
	delete [] h;
	for(int i=0;i<n;++i){
		delete[]cost[i];
		delete[]make[i];
	}
	delete[]cost;
	delete[]make;
}
