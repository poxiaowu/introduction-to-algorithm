#include <iostream>
#include <algorithm>
#include <boost/timer/timer.hpp>
#include <ctime>
using namespace std;
using namespace boost::timer;

int compar_words(const void *p, const void *q)
{
	return strcmp(*(char **)p, *(char **)q);
}
int main()
{
	srand(time(NULL));
	int count;
	while (count=rand()%100,count<50);
	count=40000000;
	char **str=new char*[count];
	int size=5;
	for(int i=0;i<count;++i){
		while (size=rand()%20,size<2);
		size=5;
		str[i]=new char[size];
		int j=0;
		while (j<size-1){//随机生成字符串
			str[i][j]=rand()%26+'A'+(rand()%2)*32;//随机生成字母
			++j;
		}
		str[i][j]='\0';
	}
	cout<<"*******************************"<<endl;
	cout<<count<<" strings"<<endl;
	cpu_timer t1;
	t1.start();
	qsort(str,count,sizeof(str[0]),compar_words);
	cout<<"*******************************"<<endl;
	t1.stop();
	cout<<t1.format();
	for(int i=0;i<count;++i){
		delete[] str[i];
	}
	delete[] str;
}
