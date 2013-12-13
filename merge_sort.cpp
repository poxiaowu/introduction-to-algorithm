#include<iostream>
#include<ctime>
#include <limits>
using namespace std;

void merge(int *a,int p,int q,int r)
{
	int Ln=q-p+1;
	int Rn=r-q;

	int *La=new int[Ln+1];
	int *Ra=new int[Rn+1];
	for(int i=0;i<Ln;++i){
		La[i]=a[i+p];
	}
	La[Ln]=numeric_limits<int>::max();

	for(int j=0;j<Rn;++j){
		Ra[j]=a[q+j+1];
	}
	Ra[Rn]=numeric_limits<int>::max();

	int k=0,m=0;

	for(int n=p;n<=r;++n){
		if(La[k]<Ra[m]){
			a[n]=La[k];
			++k;
		}else{
			a[n]=Ra[m];
			m++;
		}
	}
}

void merge_sort(int *a,int p,int q)
{
	if(p<q){
		int mid=(p+q)>>1;
		merge_sort(a,p,mid);
		merge_sort(a,mid+1,q);
		merge(a,p,mid,q);
	}
}


int main()
{
	srand(time(NULL));
	int n;
	while((n= rand()%20)<3);
	//n=5;
	int * a=new int[n];

	for(int i=0;i<n;i++){
		a[i]=rand()%1000;
		cout<<a[i]<<" ";
	}
	cout<<endl;
	merge_sort(a,0,n-1);
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	delete [] a;

}
