#include <iostream>
#include <ctime>
using namespace std;

void table_insert(int *&result,int x,int &num,int &n)//动态数组,动态插入
{
	if(n==0){
		result=new int[1];
		n=1;
	}
	if(num==n){
		int * n_result=new int[2*n];
		for(int i=0;i<n;++i){
			n_result[i]=result[i];
		}
		delete [] result;
		result=n_result;
		n*=2;
	}
	result[num]=x;
	num++;
}
void table_delete(int *&result,int &num,int &n)//动态删除
{
	if(num==0){//如果为空表，则返回
		return;
	}
	if(num * 4 ==n){//当剩余元素为表中元素的1/4是，将表大小减少1/2
		int *n_result=new int[n/2];
		for(int i=0;i<num;++i){
			n_result[i]=result[i];
		}
		delete[]result;
		result=n_result;
		n/=2;
	}
	num--;
	//cout<<result[num]<<" ";
	//if(num==0){//如果全部删除，则将空间全部删除
	//	n=0;
	//	delete [] result;
	//}
}


int main()
{
	srand((unsigned)time(NULL));
	int t;
	t=/*rand()%1000+*/5;
	int *result=NULL;
	int tmp;
	int m=0,n=0;
	for(int i=0;i<t;++i){//首先在表中插入t个元素
		tmp=rand()%101;
		cout<<tmp<<" ";
		table_insert(result,tmp,m,n);
	}
	for(int i=0;i<100;++i){
		if(rand()%2){
			tmp=rand()%11;
			cout<<tmp<<" ";
			table_insert(result,tmp,m,n);
		}else{
			table_delete(result,m,n);
		}
	}
	cout<<endl;
	for(int i=0;i<m;++i){
		cout<<result[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<500;++i){
		table_delete(result,m,n);
	}	
	cout<<endl;
	if(result){
		delete[]result;
	}
}
