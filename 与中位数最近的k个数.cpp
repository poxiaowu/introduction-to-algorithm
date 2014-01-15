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

void latest_k_value(int *a,int low, int high,int k)
{
	int idx=((low+high)>>1)+1;
	random_select(a,low,high,idx);
	cout<<a[idx-1]<<endl;
	int *b=new int[high-low];//存储差值
	for(int i=0;i<idx-1;++i){
		b[i]=abs(a[i]-a[idx-1]);
	}
	for(int i=idx;i<=high;++i){
		b[i-1]=abs(a[i]-a[idx-1]);
	}
	cout<<endl<<endl<<endl;
	//for(int i=low;i<high;++i){
	//	cout<<b[i]<<"\t";
	//}
	//cout<<endl;
	int laterst_k=random_select(b,low,high-1,k);//找出b中的第k小的元素,中位数是b[idx-1]
	for(int i=low;i<=high;++i){
		if(i!=(idx-1) && (abs(a[i]-a[idx-1])<=laterst_k))
			cout<<a[i]<<"\t";
	}
	cout<<endl;
	delete[]b;
}

int main()
{
	srand((unsigned)time(NULL));
	int count;
	while (count=rand()%10,count<3);
	count=100;
	int *a=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%101-50;
		cout<<a[i]<<"\t";
	}
	cout<<endl;
	/*a[0]=-74,a[1]=93,a[2]=66,a[3]=-21,a[4]=-79,a[5]=22,a[6]=10,
	a[7]=-100,a[8]=37,a[9]=6;
	for(int i=0;i<count;++i){
	cout<<a[i]<<"\t";
	}
	cout<<endl;*/
	cpu_timer t1;
	t1.start();
	latest_k_value(a,0,count-1,20);//这里的20表示与a数组中的中位数最近的20个数，故数组大小一定要大于20
	t1.stop();
	cout<<endl;
	cout<<t1.format();
	//int v=random_select(a,0,count-1,3);
	//cout<<v<<endl;
	delete[]a;
}
