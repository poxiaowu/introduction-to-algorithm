#include <iostream>
#include <algorithm>
using namespace std;

void nextpermutation(int *arr,int n)
{
	int index=n-1;
	while(index>0 && arr[index-1]>=arr[index]){
		--index;
	}
	if(!index){//如果是最后一个序列，则其下一个序列为第一个序列
		sort(arr,arr+n);
		return;
	}
	int mp=index;
	for(int i=index;i<n;++i){
		if(arr[i]>=arr[index-1] &&arr[i]<=arr[mp]){
			mp=i;	
		}
	}
	swap(arr[index-1],arr[mp]);
	sort(arr+index,arr+n);
}

int main()
{
	int m;
	cin>>m;
	int n,k;
	int *arr;
	for(int i=0;i<m;++i){
		cin>>n>>k;
		arr=new int[n];
		for(int j=0;j<n;++j){
			cin>>arr[j];
		}
		for(int j=0;j<k;++j){
			//next_permutation(arr,arr+n);//STL自带算法
			nextpermutation(arr,n);
		}
		for(int j=0;j<n-1;++j){
			cout<<arr[j]<<" ";
		}
		cout<<arr[n-1]<<endl;
		delete [] arr;
	}
}
