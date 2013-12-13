#include<iostream>
#include<ctime>
using namespace std;


void insert_sort(int *a ,int n)
{
	int key,j;
	for(int i=1;i<n;++i){
		key=a[i];
		j=i-1;
		while(j>=0 && key>a[j]){
			a[j+1]=a[j];
			--j;
		}	
		a[j+1]=key;
	}
}


int main()
{
	bool flag=true;
	srand(time(NULL));
	int rnd=rand()%2000;
	int count=rand()%10000;
	for(int k=0;k<count;++k){
		int *test=new int[rnd];
		for(int i=0;i<rnd;++i){
			test[i]=rand()%1000000;
			//cout<<test[i]<<" ";
		}
		//cout<<endl;
		insert_sort(test,rnd);
		for(int j=0;j<rnd-1;++j)
		{
			//cout<<test[j]<<" ";
			if(test[j]<test[j+1])
				flag=false;

		}
		//cout<<endl;
		delete [] test;
	}

	cout<<(flag?"true":"false")<<endl;

}
