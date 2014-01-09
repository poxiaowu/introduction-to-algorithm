//算法导论8-3，变长数据项的排序
#include <iostream>
#include <ctime>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;

int bits(int i)//找出每位数的位数,正数为正，负数为负
{
	int radix=1;
	while (i/10)
	{
		radix++;
		i/=10;
	}
	return (i>=0)?radix:(-radix);
}

void find_max_min(int *aCount,int &max,int &min,int n)
{//查找数字的最大位数
	max=aCount[0];//初始化
	min=max;
	int tmp;
	for(int i=1;i<n;++i){
		tmp=aCount[i];
		if(max<tmp){
			max=tmp;
		}else if(min>tmp){
			min=tmp;
		}
	}
}
void radix_sort(int *bucket,int n)//基数排序
{
	int *s=new int[n];
	int bit=abs(bits(bucket[0]));//此处用正数
	int radix=1;
	int *b=new int[n];
	for(int i=0;i<bit;++i,radix*=10){
		for(int j=0;j<n;++j){
			s[j]=(bucket[j]/radix)%10;//存储每轮的值
		}		
		int max,min;
		find_max_min(s,max,min,n);
		int count=max-min+1;
		int *c=new int[count];
		memset(c,0,count*sizeof(int));
		for(int j=0;j<n;++j){
			c[s[j]-min]++;
		}
		for(int j=1;j<count;++j){
			c[j]+=c[j-1];
		}

		for(int j=n-1;j>=0;--j){
			b[c[s[j]-min]-1]=bucket[j];
			c[s[j]-min]--;
		}
		/*for(int j=0;j<n;++j){
			bucket[j]=b[j];
		}*/
		memcpy(bucket,b,n*sizeof(int));
		delete[]c;
	}
	delete[]b;
	delete[]s;
}

void bucket_sort(int *a,int n)//桶排序
{
	int *aCount=new int[n];//记录a[i]的位数
	for(int i=0;i<n;++i){
		int bit=bits(a[i]);//位数
		aCount[i]=bit;
	}

	int max,min;
	find_max_min(aCount,max,min,n);
	int count=max-min+1;
	int *b=new int[count];//用来存放不同位数的数字的个数
	memset(b,0,count*sizeof(int));//初始化为零

	for(int i=0;i<n;++i){//统计每个桶的元素个数
		b[aCount[i]-min]++;
	}

	int **bucket=new int *[count];
	int *flag=new int [count];
	for(int i=0;i<count;++i){
		bucket[i]=new int[b[i]];//第i个桶有b[i]个元素
		flag[i]=0;//初始化
	}

	for(int i=0;i<n;++i){//将相关元素放到相应的桶中
		bucket[aCount[i]-min][flag[aCount[i]-min]++]=a[i];
	}

	int k=0;
	for(int i=0;i<count;++i){
		radix_sort(bucket[i],b[i]);
		for(int j=0;j<b[i];++j){
			a[k++]=bucket[i][j];
		}
	}
}


int main()
{
	srand(time(NULL));
	int count;
	while (count=rand()%16,count<4);
	count=100;
	int *a=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%201-100;
		cout<<a[i]<<"\t";
	}
	//a[0]=-2,a[1]=-5,a[2]=-3,a[3]=1,a[4]=-2;
	cout<<endl;
	cpu_timer t1;
	t1.start();
	bucket_sort(a,count);
	t1.stop();

	for(int i=0;i<count;++i){
		cout<<a[i]<<"\t";
	}
	cout<<endl;
	delete[]a;
	cout<<t1.format();
}
