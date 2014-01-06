//基数排序
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

int max_bit(int max,int min)//返回基数排序的最大位数
{
	int bits=1;
	while ((max/10)||(min/10)){//考虑为负数的情况
		bits++;
		max/=10,min/=10;
	}
	return bits;
}

void radix_sort(int *a,int *b,int n)//基数排序
{
	int min,max;//存储最大最小值
	find_max_min(a,max,min,n);//寻找最大最小值
	int bits=max_bit(max,min);//返回基数排序最大循环次数
	int radix=1;
	int *s=new int[n];//存储每轮的数据
	for(int i=0;i<bits;++i,radix*=10){

		for(int i=0;i<n;++i){//输出每轮基数排序后a数组的值
			cout<<a[i]<<"\t";
		}
		cout<<endl;

		for(int j=0;j<n;++j){
			s[j]=(a[j]/radix)%10;//存储a的每位数据
			cout<<s[j]<<"\t";
		}
		cout<<endl;
		find_max_min(s,max,min,n);//早出s数组中的最大最小值
		int count=max-min+1;//计算c数组的大小
		int *c=new int[count];
		memset(c,0,count*sizeof(int));//初始化为0

		for(int i=0;i<n;++i){
			c[s[i]-min]++;//个数加1
		}
		for(int i=1;i<count;++i){
			c[i]+=c[i-1];
		}
		for(int i=n-1;i>=0;--i){
			b[c[s[i]-min]-1]=a[i];//c数组从0开始，但是值可正可负
			c[s[i]-min]--;        //所以要将最小值的下标调整到0.
		}

		for(int i=0;i<n;++i){
			a[i]=b[i];
		}

		delete[]c;
	}	
	delete[]s;
}

int main()
{
	srand(time(NULL));
	int count;
	while (count=rand()%16,count<4);
	count=100;
	int *a=new int[count];
	int *b=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%201-150;
	}

	radix_sort(a,b,count);

	for(int i=0;i<count;++i){
		cout<<b[i]<<"\t";
	}
	cout<<endl;
	delete[]a;
	delete[]b;
}
