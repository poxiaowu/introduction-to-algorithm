#include <iostream>
using namespace std;

void package(int *need,int *value,int n,int m)
{
	int **p=new int *[2];
	for(int i=0;i<2;++i){
		p[i]=new int [m+1];
		for(int j=0;j<=m;++j){
			p[i][j]=0;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<=m;++j){
			if(j<need[i-1]){
				p[i%2][j]=p[(i-1)%2][j];
			}else{
				p[i%2][j]=max(p[(i-1)%2][j],p[(i-1)%2][j-need[i-1]]+value[i-1]);
			}
		}
	}
	cout<<p[n%2][m]<<endl;
	for(int i=0;i<2;++i){
		delete []p[i];
	}
	delete [] p;
}

int main()
{
	int n,m;
	cin>>n>>m;
	int *need=new int[n];
	int *value=new int[n];
	for(int i=0;i<n;++i){
		cin>>need[i]>>value[i];	
	}
	package(need,value,n,m);
	delete [] need;
	delete [] value;
}
