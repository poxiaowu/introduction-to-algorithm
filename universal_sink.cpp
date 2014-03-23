#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

bool is_sink(int **matrix,int n,int k)//判断点k是否是通用汇点universal sink
{
	for(int j=0;j<n;++j){//出度是否大于1
		if(matrix[k][j]==1)
			return false;
	}
	for(int i=0;i<n;++i){//入度是否等于n-1
		if(matrix[i][k]==0 && i!=k){
			return false;
		}
	}
	return true;
}

void universal_sink(int **matrix,int n)//判断是否有通用交汇点
{
	int i=0,j=0;
	while (i<n && j<n){
		if(matrix[i][j]==1){
			++i;
		}else{
			++j;
		}
	}
	if(i>=n){
		if(is_sink(matrix,n,j)){
			cout<<j<<" is a universal sink";
		}/*else{
			cout<<"there is no universal sink"<<endl;
		}*/
	}else if(is_sink(matrix,n,i)){
		cout<<i<<" is a universal sink";		
	}/*else{
		cout<<"there is no universal sink"<<endl;
	}*/
}

int main()
{
	srand((unsigned)time(NULL));
	int n=10;
	int **matrix=new int *[n];
	for(int i=0;i<n;++i){
		matrix[i]=new int [n];
	}
	for(int m=0;m<1000000000;++m){
		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				matrix[i][j]=rand()%2;
			}
		}
		universal_sink(matrix,n);
	}
	for(int i=0;i<n;++i){
		delete[]matrix[i];
	}
	delete[]matrix;
}
