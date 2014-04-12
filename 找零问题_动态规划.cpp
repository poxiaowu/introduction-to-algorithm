#include <iostream>
#include <ctime>
#include <limits>
using namespace std;


void compute_change(int cost,int *demos,int *count,int *re,int n)
{
	count[0]=0;
	for(int j=1;j<=cost;++j){
		count[j]=numeric_limits<int>::max();
		for(int i=0;i<n;++i){
			if(j>=demos[i] && count[j]>count[j-demos[i]]+1){
				count[j]=count[j-demos[i]]+1;
				re[j]=demos[i];
			}
		}
	}
}

void give_change(int cost,int *re)
{
	if(cost>0){
		give_change(cost-re[cost],re);
		cout<<re[cost]<<" ";
	}
}


int main()
{
	srand((unsigned)time(NULL));
	int cost=rand()%1000+2;
	int n=6;
	int *demos=new int[n];
	demos[0]=1;
	cout<<cost<<endl;
	cout<<demos[0]<<" ";
	demos[1]=5,demos[2]=10,demos[3]=20,demos[4]=50,demos[5]=100;
	for(int i=1;i<n;++i){
		//demos[i]=rand()%(cost-9)+1;
		cout<<demos[i]<<" ";
	}
	cout<<endl;
	int *count=new int[cost+1];
	int *re=new int[cost+1];
	compute_change(cost,demos,count,re,n);
	give_change(cost,re);
	cout<<endl;
	delete[]demos;
	delete[]count;
	delete[]re;
}
