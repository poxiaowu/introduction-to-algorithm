//计数排序
#include <iostream>
#include <ctime>
using namespace std;

void find_max_min(int *a,int &max,int &min,int n)
{
	max=a[0],min=a[0];//寻找最大最小值
	for(int i=1;i<n;++i){
		if(max<a[i]){
			max=a[i];
		}else if(min>a[i]){
			min=a[i];
		}
	}
}

void counting_sort(int *a,int *b,int n)
{
	for(int i=0;i<n;++i){
		cout<<a[i]<<"\t";
	}
	cout<<endl;

	int min,max;
	find_max_min(a,max,min,n);//寻找最大最小值
	int count=max-min+1;//计算c数组的大小
	int *c=new int[count];
	memset(c,0,count*sizeof(int));//初始化为0
	/*for(int i=0;i<count;++i)
		cout<<c[i]<<"\t";
	cout<<endl;*/

	for(int i=0;i<n;++i){
		c[a[i]-min]++;//个数加1
	}

	//for(int i=0;i<count;++i)
	//	cout<<c[i]<<"\t";
	//cout<<endl;

	for(int i=1;i<count;++i){
		c[i]+=c[i-1];
	}

	/*for(int i=0;i<count;++i){
		cout<<c[i]<<"\t";
	}
	cout<<endl;*/

	for(int i=n-1;i>=0;--i){
		b[c[a[i]-min]-1]=a[i];//c数组从0开始，但是值可正可负
		c[a[i]-min]--;        //所以要将最小值的下标调整到0.
	}
	delete[]c;
}

int main()
{
	srand(time(NULL));
	int count;
	while (count=rand()%16,count<4);
	//count=10;
	int *a=new int[count];
	int *b=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%31-15;
	}

	counting_sort(a,b,count);

	for(int i=0;i<count;++i){
		cout<<b[i]<<"\t";
	}
	cout<<endl;
	delete[]a;
	delete[]b;
}
