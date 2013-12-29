#include <iostream>
#include <ctime>
#include <utility>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;

void randomize_in_place(int *a,int n)
{
	for(int i=0;i<n;++i){
		swap(a[i],a[rand()%(n-i)+i]);
	}
}



int main()
{
	srand(time(NULL));
	int count=0;
	while((count=rand()%50)<7);
	count=5;
	int *a =new int[count];

	for (int i=0;i<count;++i){
		a[i]=i;
		cout<<a[i]<<" ";
	}
	cout<<endl;
	cpu_timer t1;
	t1.start();
	randomize_in_place(a,count);
	t1.stop();
	cout<<t1.format();
	
	for (int i=0;i<count;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;

	delete[]a;

}
