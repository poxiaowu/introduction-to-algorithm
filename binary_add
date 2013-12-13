#include<iostream>
#include<ctime>
using namespace std;

void binary_add(int *a, int *b,int *c,int n)
{
	c[n]=0;
	int temp;
	for(int i=n-1;i>=0;--i){
		temp=c[i+1];
		c[i+1]=c[i+1]^a[i]^b[i];
		c[i]=(a[i]+b[i]+temp) >> 1;
	}
}


int main()
{
	srand(time(NULL));
	int n;
	while((n= rand()%20)==0);
	int *a=new int[n];
	int *b =new int[n];
	int *c =new int[n+1];
	for(int i=0;i<n;++i){
		a[i]=rand()%2;
		b[i]=rand()%2;
	}

	cout<<" ";
	for(int i=0;i<n;++i)
		cout<<a[i];
	cout<<endl;
	cout<<" ";
	for(int i=0;i<n;++i)
		cout<<b[i];
	cout<<endl;


	binary_add(a,b,c,n);

	for(int i=0;i<n+1;++i)
		cout<<"-";
	cout<<endl;

	for(int i=0;i<n+1;++i)
		cout<<c[i];
	cout<<endl;

}
