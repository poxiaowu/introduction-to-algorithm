#include<iostream>
#include<ctime>
using namespace std;

void selection_sort(int *a,int n)
{
	int index=0;
	int inner=1;
	for(int i=1;i<n;++i){
		index=i-1;
		inner=i;
		while (inner<n){
			if(a[inner]<a[index])
				index=inner;
			++inner;
		}

		if(index!=i-1){//防止anchor就是最小值的情况
			a[i-1]=a[i-1]^a[index];//异或法交换元素
			a[index]=a[i-1]^a[index];
			a[i-1]=a[i-1]^a[index];

			/*a[i-1]=a[i-1]+a[index];//加减分交换元素
			a[index]=a[i-1]-a[index];
			a[i-1]-=a[index];*/

			/*int temp=a[i-1];//临时变量交换元素
			a[i-1]=a[index];
			a[index]=temp;*/
		}
	}
}


int main()
{
	srand(time(NULL));
	int n;
	while((n= rand()%20)<3);

	int * a=new int[n];

	for(int i=0;i<n;i++){
		a[i]=rand()%1000;
		cout<<a[i]<<" ";
	}
	cout<<endl;
	selection_sort(a,n);
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	delete [] a;

}
