#include <iostream>
#include <ctime>
#include <limits>
#include<boost/timer/timer.hpp>
#include<algorithm>
using namespace std;
using namespace boost::timer;
void brute_force_maximum_subarray(int *a,int& index_low,int& index_high,int& maximum,int n)
{
	maximum=numeric_limits<int>::min();	
	for(int i=0;i<n;++i){
		int sum=0;
		for(int j=i;j<n;++j){
			sum+=a[j];
			if(sum>maximum){
				maximum=sum;
				index_low=i;
				index_high=j;
			}			
		}
		//if(a[i]>=maximum){//改进后的暴力法求最大子数组，求出长度为1的最大数
		//	maximum=a[i];
		//	index_low=i;
		//	index_high=i;
		//}
	}	
}

void find_max_cross_subarray(int *a,int& low,int mid,int &high,int &sum)
{
	int index_low=low,index_high=high;
	sum=0;
	int left_sum=numeric_limits<int>::min();	
	int right_sum=numeric_limits<int>::min();
	for(int i=mid;i>=index_low;--i){
		sum+=a[i];
		if(sum>=left_sum){
			left_sum=sum;
			low=i;
		}
	}
	
	sum=0;
	for(int j=mid+1;j<=index_high;++j){
		sum+=a[j];
		if(sum>=right_sum){
			right_sum=sum;
			high=j;
		}
	}
	sum=left_sum+right_sum;
}

void find_maximum_subarray(int *a,int & low,int & high,int &sum)
{
	if(low==high){
		sum=a[low];
	}else{		
		int mid=(low+high)>>1;
		int left_low=low;
		int left_high=mid;
		int left_sum;
		find_maximum_subarray(a,left_low,left_high,left_sum);

		//int mid2=mid+1;
		int right_low=mid+1;
		int right_high=high;
		int right_sum;
		find_maximum_subarray(a,right_low,right_high,right_sum);

		int cross_sum;
		find_max_cross_subarray(a,low,mid,high,cross_sum);

		if(left_sum>right_sum && left_sum>cross_sum){
			low=left_low;
			high=left_high;
			sum=left_sum;
		}else if(right_sum>left_sum && right_sum>cross_sum){
			low=right_low;
			high=right_high;
			sum=right_sum;
		}else{
			sum=cross_sum;
		}
	}
}

void maximum_subarray_liner(int *a,int & low,int & high,int &sum)
{
	int n=high-low+1;
	int ending_here_sum=numeric_limits<int>::min();
	sum=numeric_limits<int>::min();
	int ending_here_low;
	//int ending_here_high;
	for(int i=0;i<n;++i){
		//ending_here_high=i;
		if(ending_here_sum>=0){
			ending_here_sum+=a[i];
		}else{
			ending_here_sum=a[i];
			ending_here_low=i;
		}
		if(ending_here_sum>sum){
			sum=ending_here_sum;
			low=ending_here_low;
			//high=ending_here_high;
			high=i;
		}
	}
}



int main()
{
	//int a[16]={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	int index_low=0,index_high=0,maximum;
	/*violence_maximum_subarray(a,index_low,index_high,maximum,16);
	cout<<index_low<<endl;
	cout<<index_high<<endl;
	cout<<maximum<<endl;*/


	srand(time(NULL));
	int count;
	while ((count=rand()%20)<5);
	count=500000;
	int *b=new int[count];
	//b[0]=0,	b[1]=-4,b[2]=-1,b[3]=-7,b[4]=3;
	for(int i=0;i<count;++i){
		b[i]=rand()%101-50;
		//cout<<b[i]<<" ";
	}
	//cout<<endl;

	cpu_timer t1;
	t1.start();
	brute_force_maximum_subarray(b,index_low,index_high,maximum,count);
	t1.stop();
	cout<<index_low<<endl;
	cout<<index_high<<endl;
	cout<<maximum<<endl;
	cout<<t1.format();
	cout<<endl;

	index_low=0,index_high=count-1,maximum=0;
	cpu_timer t2;
	t2.start();
	find_maximum_subarray(b,index_low,index_high,maximum);
	t2.stop();
	cout<<index_low<<endl;
	cout<<index_high<<endl;
	cout<<maximum<<endl;
	cout<<t2.format();
	cout<<endl;

	index_low=0,index_high=count-1,maximum=0;
	cpu_timer t3;
	t3.start();
	maximum_subarray_liner(b,index_low,index_high,maximum);
	t3.stop();
	cout<<index_low<<endl;
	cout<<index_high<<endl;
	cout<<maximum<<endl;
	cout<<t3.format();
	cout<<endl;

	
}
