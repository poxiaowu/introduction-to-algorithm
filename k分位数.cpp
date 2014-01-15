#include <iostream>
#include <ctime>
#include <boost/timer/timer.hpp>
using namespace boost::timer;
using namespace std;

int partition(int *a,int low,int high)
{
	int key=a[high];
	int p=low-1;
	int tmp;
	for(int i=low;i<high;++i){
		if(a[i]<=key){
			p++;
			tmp=a[i];
			a[i]=a[p];
			a[p]=tmp;
		}
	}
	tmp=a[p+1];
	a[p+1]=key;
	a[high]=tmp;
	return p+1;
}

int random_parition(int *a,int low,int high)
{
	int index=rand()%(high-low+1)+low;
	int tmp=a[index];
	a[index]=a[high];
	a[high]=tmp;
	/*for(int i=low;i<=high;++i)
		cout<<a[i]<<"\t";
	cout<<endl;*/
	return partition(a,low,high);
}

int random_select(int *a,int low,int high,int index)
{
	if(low==high)
		return a[low];
	int q=random_parition(a,low,high);
	int k=q+1;

	/*for(int i=low;i<=high;++i)
		cout<<a[i]<<"\t";
	cout<<endl;*/

	if(k==index){
		return a[q];
	}
	else if(k<index){
		return random_select(a,q+1,high,index);
	}else{
		return random_select(a,low,q-1,index);
	}
}

void k_quantile(int *a,int low,int high,int k)
{
	if(high-low+1>=k){
		int count=(high-low+1)/k;   //k分位数的个数,元素总个数与没组个数之商
		int index=((count+1)/2)*k;//k分数的中位数
		index+=low;//中位数的位置
		random_select(a,low,high,index);//寻找k分数的中位数,index表示第index个数，其在有序列表中表示为a[index-1]
		k_quantile(a,low,index-2,k);
		cout<<a[index-1]<<"\t";
		k_quantile(a,index,high,k);		
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int count;
	while (count=rand()%10,count<3);
	count=1000;
	int *a=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%1001-500;
		//cout<<a[i]<<"\t";
	}
	//cout<<endl;
	/*a[0]=-74,a[1]=93,a[2]=66,a[3]=-21,a[4]=-79,a[5]=22,a[6]=10,
	a[7]=-100,a[8]=37,a[9]=6;
	for(int i=0;i<count;++i){
	cout<<a[i]<<"\t";
	}
	cout<<endl;*/
	cpu_timer t1;
	t1.start();
	k_quantile(a,0,count-1,10);
	t1.stop();
	cout<<endl;
	cout<<t1.format();
	//int v=random_select(a,0,count-1,3);
	//cout<<v<<endl;
	delete[]a;
}
