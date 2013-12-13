#include<iostream>
#include<ctime>
#include <limits>
using namespace std;

void merge(int *a,int p,int q,int r)//哨兵法
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
	delete [] La;
	delete [] Ra;
}

void merge_no(int *a,int p,int q,int r)//无哨兵
{
	int Ln=q-p+1;
	int Rn=r-q;

	int *La=new int[Ln/*+1*/];
	int *Ra=new int[Rn/*+1*/];
	for(int i=0;i<Ln;++i){
		La[i]=a[i+p];
	}
	/*La[Ln]=numeric_limits<int>::max();*/

	for(int j=0;j<Rn;++j){
		Ra[j]=a[q+j+1];
	}
	/*Ra[Rn]=numeric_limits<int>::max();*/

	int k=0,m=0;

	for(int n=p;n<=r;++n){
		if(La[k]<Ra[m]){
			if(k<Ln){
				a[n]=La[k];
				++k;
			}else{
				break;
			}
		}else{
			if(m<Rn){
				a[n]=Ra[m];
				m++;
			}else{
				break;
			}
		}
	}

	if(k==Ln){
		while (m<Rn){
			a[p+Ln+m]=Ra[m];
			m++;
		}
	}else{
		while (k<Ln){
			a[p+Rn+k]=La[k];
			k++;
		}
	
	}
	delete [] La;
	delete [] Ra;
}


void merge_no2(int *a,int p,int q,int r)//无哨兵
{
	int Ln=q-p+1;
	int Rn=r-q;

	int *La=new int[Ln];
	int *Ra=new int[Rn];
	for(int i=0;i<Ln;++i){
		La[i]=a[i+p];
	}
	for(int j=0;j<Rn;++j){
		Ra[j]=a[q+j+1];
	}	
	int k=0,t=0,n=0,m=0;

	for(t=0,k=0,n=p; t<Ln && k<Rn ;++n){//k是右边指针，t是左边指针
		if(La[t]<=Ra[k]){
			a[n]=La[t++];
		}else{
			a[n]=Ra[k++];
		}
	}

	if(k<Rn){//右边剩余
		for(m=0;m<Rn-k;++m)
			a[n+m]=Ra[k+m];
	}
	if(t<Ln){//左边剩余
		for(m=0;m<Ln-t;++m)
			a[n+m]=La[t+m];
	}

	delete [] La;
	delete [] Ra;
}




void merge_sort(int *a,int p,int q)
{
	if(p<q){
		int mid=(p+q)>>1;
		merge_sort(a,p,mid);
		merge_sort(a,mid+1,q);
		//merge(a,p,mid,q);
		merge_no2(a,p,mid,q);
	}
}


int main()
{
	srand(time(NULL));
	int n;
	while((n= rand()%100)<3);
	int * a=new int[n];

	for(int i=0;i<n;i++){
		a[i]=rand()%100000;
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
