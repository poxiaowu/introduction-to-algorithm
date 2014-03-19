#include <iostream>
#include <ctime>
using namespace std;

void increment(int *a,int n)//二进制加法
{
	int i=n-1;
	while (i>=0 &&a[i]==1){
		a[i]=0;
		i--;
	}
	if(i>=0){
		a[i]=1;
	}
}

void decrement(int *a,int n)//二进制减法
{
	int i=n-1;
	while(i>=0 && a[i]==0){
		a[i]=1;
		i--;
	}
	if(i>=0){
		a[i]=0;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=10;
	int *a=new int[n];
	for(int i=0;i<n;++i){//初始化为全0
		a[i]=0;
		cout<<a[i];
	}
	cout<<endl;
	for(int i=0;i<10;i++){
		increment(a,n);
		for(int j=0;j<n;++j){
			cout<<a[j];
		}
		cout<<endl;
	}
	for(int i=0;i<10;i++){
		decrement(a,n);
		for(int j=0;j<n;++j){
			cout<<a[j];
		}
		cout<<endl;
	}
}
