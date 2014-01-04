#include <iostream>
#include <ctime>
#include <utility>
#include <boost/timer/timer.hpp>
using namespace boost::timer;
using namespace std;


void same_elem_quick_sort(int *a,int low,int high)//考虑相同元素的情况
{
	if(low<high){
		int pivot=a[low];
		int i=low,h=low;
		for(int j=low+1;j<high;++j){
			if(a[j]<pivot){
				int y=a[j];
				a[j]=a[h+1];
				a[h+1]=a[i];
				a[i]=y;
				++h,++i;
			}else if(a[j]==pivot){
				int y=a[j];
				a[j]=a[h+1];
				a[h+1]=y;
				++h;
			}
		}
		same_elem_quick_sort(a,low,i);
		same_elem_quick_sort(a,h+1,high);
	}

}



void same_elem_quick_sort2(int *a,int low,int high)//考虑相同元素的情况,小的放在pivot左边，
{                                                 //大的放在pivot右边，相等的不变，最后相等的就可以连在一起
	if(low<high){
		int pivot=a[low];
		int i=low-1;
		int k=high;
		for(int j=low+1;j<k;++j){
			if(a[j]<pivot){
				++i;
				int y=a[j];				
				a[j]=a[i];
				a[i]=y;
			}else if(a[j]>pivot){
				--k;
				int y=a[k];
				a[k]=a[j];
				a[j]=y;
				--j;
			}
		}
		//if(i-low<high-h){
			same_elem_quick_sort(a,low,i);
			//low=h+1;
		//}else{
			same_elem_quick_sort(a,k,high);
			//high=i;
		//}
	}

}


int main()
{
	srand(time(NULL));
	int count;
	while((count=(rand()%30))<10);
	count=100000000;  
	int *a=new int[count];
	int *b=new int[count];
	for(int i=0;i<count;++i){
		a[i]=rand()%100000001-50000000;  
		b[i]=a[i];		
		//cout<<a[i]<<" ";
	}
	//cout<<endl;

	cpu_timer t1;
	t1.start();
	same_elem_quick_sort(a,0,count);
	t1.stop();
	//for(int i=0;i<count;++i){
	//	cout<<a[i]<<" ";
	//} 
	//cout<<endl;
	cout<<t1.format();

	cpu_timer t2;
	t2.start();
	same_elem_quick_sort2(b,0,count);
	t2.stop();
	/*for(int i=0;i<count;++i){
		cout<<b[i]<<" ";
	}
	cout<<endl;*/
	cout<<t2.format();

	delete[]a;
	delete[] b;
	
}
