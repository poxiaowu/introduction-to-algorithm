#include <iostream>
#include <ctime>
#include<algorithm>
#include <vector>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;
int compare(const void *a,const void *b)//qsort比较函数
{
	if ( *(double*)a <  *(double*)b ) return -1;
	if ( *(double*)a == *(double*)b ) return 0;
	if ( *(double*)a >  *(double*)b ) return 1;		
	return -2;
}
void rnd(double* drnd,int n)//生成指定数目的（0,1]之间随机数
{
	double d;
	int tmp;
	int count=0;
	srand((unsigned)time(NULL));
	vector<double> vec;
	while(true){	//生成大量的随机数，直到最大值为1
		d=rand()/(RAND_MAX*1.0);
		tmp=static_cast<int>((d*100+0.5));//保留2位小数取整
		d=tmp/100.0;//变成浮点数
		vec.push_back(d);
		//cout<<d<<endl;
		count++;
		if(d==1.0){
			if(count>=n)
				break;
			else
				vec.pop_back();
		}
	}
	int size=vec.size();//容器的大小
	for(int i=0;i<n;++i){
		drnd[i]=vec[size-i-1];
	}
	/*for(int i=0;i<n;++i){
		cout<<drnd[i]<<" ";
	}
	cout<<endl;*/
	qsort(drnd,n,sizeof(double),compare);//调用系统快速排序算法
	for(int i=n-1;i>0;--i){
		drnd[i]=drnd[i]-drnd[i-1];
	}
	/*for(int i=n-1;i>=0;--i){
		cout<<drnd[i]<<"\t";
	}
	cout<<endl;*/

	vector<double>().swap(vec);//删除内容并回收空间
	//vec.clear();
}

int main()
{
	srand((unsigned)time(NULL));
	int n=10;
	double *drnd=new double[n];
	rnd(drnd,n);

	for(int i=0;i<n;++i){
		cout<<drnd[i]<<"\t";
	}
	cout<<endl;
	delete [] drnd;
}   
