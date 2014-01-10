#include <iostream>
#include <ctime>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;
void find_max_min(char **str,int &max,int &min,int index,int offset,int n)
{
	max=str[offset][index],min=str[offset][index];
	for(int i=1;i<n;++i){
		if(max<str[i+offset][index]){
			max=str[i+offset][index];
		}else if(min>str[i+offset][index]){
			min=str[i+offset][index];
		}
	}
}

int insertion_sort_stable(char **str,int index,int offset,int n){//插入排序版本，对元素按照长短进行排序
	int key,j;
	int num=(strlen(str[offset])==index)?1:0;
	for(int i=1;i<n;++i){
		if((key=strlen(str[i+offset]))==index){
			num++;
		}
		char *keystr=str[i+offset];
		j=i-1;
		while (j>=0 && strlen(str[j+offset])>key){
			str[j+1+offset]=str[j+offset];
			--j;
		}
		str[j+1+offset]=keystr;
	}
	return num;
}

int fast_sort_unstable(char **str,int index,int offset,int n)//快速排序版本,将字符串等于index的放在前面
{
	int p=-1;
	char *keystr;
	for(int i=0;i<n;++i){
		if(strlen(str[offset+i])==index){
			p++;
			keystr=str[i+offset];
			str[i+offset]=str[offset+p];
			str[offset+p]=keystr;
		}
	}
	return p+1;
}



void counting_sort(char **str,int index,int offset,int n)//计数排序
{
	char **strCpy=new char *[n];//临时存储字符串
	int max,min;
	find_max_min(str,max,min,index,offset,n);
	int count=max-min+1;
	int *c=new int[count];
	memset(c,0,count*sizeof(int));
	for(int i=0;i<n;++i){
		c[str[i+offset][index]-min]++;
	}
	int tmp=c[count-1];//存储最后一组的元素个数值

	for(int i=1;i<count;++i){
		c[i]=c[i]+c[i-1];
	}
	for(int i=n-1;i>=0;--i){
		//strCpy[c[str[i+offset][index]-min]-1]=new char[strlen(str[i+offset])+1];//初始化内存空间
		//memcpy(strCpy[c[str[i+offset][index]-min]-1],str[i+offset],strlen(str[i+offset])+1);
		strCpy[c[str[i+offset][index]-min]-1]=str[i+offset];		
		c[str[i+offset][index]-min]--;//每组字符个数减1
	}
	for(int i=0;i<n;++i){
		//memcpy(str[i+offset],strCpy[i],strlen(strCpy[i])+1);
		str[i+offset]=strCpy[i];
	}
	
	for(int i=0;i<count-1;++i){
		c[i]=c[i+1]-c[i];//恢复原始每组元素值
	}
	c[count-1]=tmp;

	int dd;//存储每组相同元素的个数
	for(int i=0;i<count;++i){
		if(i!=0){
			c[i]=c[i]+c[i-1];
		}
		dd=(i>0)?(c[i]-c[i-1]):c[0];
		if(dd>1){
			int k=(i>0)?c[i-1]:0;
			//int num = insertion_sort_stable(str,index+1,offset+k,dd);//返回可忽略的数字
			int num=fast_sort_unstable(str,index+1,offset+k,dd);//返回可忽略的数字			
			/*for(int j=0;j<dd;++j){				
			cout<<str[offset+k+j]<<"\t";
			}
			cout<<endl;*/
			counting_sort(str,index+1,offset+k+num,dd-num);//递归调用
		}
	}
	delete [] strCpy;
	delete[]c;
}


int main()
{
	srand(time(NULL));
	int count;
	while (count=rand()%100,count<50);
	count=40000000;
	char **str=new char*[count];
	int size;
	for(int i=0;i<count;++i){
		while (size=rand()%10,size<2);
		str[i]=new char[size];
		int j=0;
		while (j<size-1){//随机生成字符串
			str[i][j]=rand()%26+'A'+(rand()%2)*32;//随机生成字母
			++j;
		}
		str[i][j]='\0';
	}
	/*str[0]=new char [2];
	str[1]=new char [3];
	str[2]=new char [4];
	strcpy(str[2],"a");
	strcpy(str[0],"a");
	strcpy(str[1],"ab");

	for(int i=0;i<count;++i){
		cout<<str[i]<<"\t";
	}
	cout<<endl;*/
	cout<<endl<<"*******************************"<<endl;
	cout<<count<<" strings"<<endl;
	cpu_timer t1;
	t1.start();
	counting_sort(str,0,0,count);
	t1.stop();
	cout<<endl<<"*******************************"<<endl;
	//for(int i=0;i<count;++i){
	//	cout<<str[i]<<"\t";
	//}
	//cout<<endl;
	cout<<t1.format();
	for(int i=0;i<count;++i){
		delete [] str[i];
		//str[i]=NULL;
	}
	delete[] str;
}
