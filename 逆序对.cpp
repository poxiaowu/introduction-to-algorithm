#include <iostream>
#include <limits>
#include <vector>
#include <set>
#include<ctime>
#include <algorithm>
using namespace std;

int inversion(int *a,int low, int mid,int high)//归并计算逆序数
{
	int inversion_count=0;
	int Ln=mid-low+1;
	int Rn=high-mid;

	int *La=new int[Ln+1];
	int *Ra=new int[Rn+1];

	for(int i=0;i<Ln;++i)
		La[i]=a[low+i];
	for(int j=0;j<Rn;++j)
		Ra[j]=a[mid+j+1];

	La[Ln]=numeric_limits<int>::max();
	Ra[Rn]=numeric_limits<int>::max();

	int p=0,q=0;
	for(int k=low;k<=high;++k){
		if(La[p]<Ra[q]){
			a[k]=La[p];
			p++;
		}else{
			a[k]=Ra[q];
			q++;
			inversion_count+=(Ln-p);
		}
	}
	delete []La;
	delete [] Ra;
	return inversion_count;
}

int inversion_pair(int *a,int low,int high)//采用归并算法的逆序对计算方法，
{
	int inversion_count=0;
	if(low<high){
			int mid=(low+high)>>1;
			inversion_count+=inversion_pair(a,low,mid);
			inversion_count+=inversion_pair(a,mid+1,high);
			inversion_count+=inversion(a,low,mid,high);
	}
	return inversion_count;
}

int main()
{
	srand(time(NULL));
	vector<int> vec;
	set<int> se;
	int num;
	while((num=rand()%20)<3);
	//num=5;
	for(int i=0;i<num;++i){
		se.insert(rand()%100);
	}
	int *a=new int[se.size()];
	//cout<<se.size()<<endl;
	

	num=-1;
	for(set<int>::iterator iter=se.begin();iter!=se.end();++iter){
		a[++num]=*iter;			
	}

	//cout<<num<<endl;	
	
	random_shuffle(a,a+num+1);//乱序

	for(int i=0;i<=num;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;

	int count=inversion_pair(a,0,num);
	


	for(int i=0;i<=num;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	cout<<count<<endl;
	delete [] a;
}
