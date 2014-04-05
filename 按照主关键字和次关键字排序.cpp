#include<iostream>
#include<ctime>
using namespace std;

void quick_sort(int *s,int *f,int low,int high)//快速排序，安装活动的开始时间升序排序
{
	while (low<high){
		int pivot=s[high];
		int k=low-1;
		int tmp;
		for(int i=low;i<high;++i){
			if(s[i]<=pivot){
				++k;
				tmp=s[i];
				s[i]=s[k];
				s[k]=tmp;
				tmp=f[i];
				f[i]=f[k];
				f[k]=tmp;
			}
		}
		tmp=s[high];
		s[high]=s[k+1];
		s[k+1]=tmp;
		tmp=f[high];
		f[high]=f[k+1];
		f[k+1]=tmp;
		if((k-low)<(high-k-2)){//栈深度为O(lgn)
			quick_sort(s,f,low,k);		
			low=k+2;
		}else{
			quick_sort(s,f,k+2,high);
			high=k;
		}
	}
}

void sort_final_time(int *s,int *f,int n)//按照结束时间排序
{
	int low=0,high=0,tmp;
	for(int i=1;i<=n;++i){
		if(s[i]!=s[i-1]){
			low=i;
		}else{
			high=i;
			tmp=f[i];
			while (high>low && tmp<f[high-1]){//开始时间相同，结束时间进行插入排序
				f[high]=f[high-1];
				--high;
			}
			f[high]=tmp;
			/*for(int j=low;j<=i;++j){
				cout<<s[j]<<" ";
			}
			cout<<endl;
			for(int j=low;j<=i;++j){
				cout<<f[j]<<" ";
			}
			cout<<endl;*/
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=10;
	int *s=new int[n];
	int *f=new int[n];
	/*s[0]=1,s[1]=3,s[2]=0,s[3]=5,s[4]=3,s[5]=5,s[6]=6,s[7]=8,s[8]=8,s[9]=2,s[10]=12;	
	f[0]=4,f[1]=5,f[2]=6,f[3]=7,f[4]=9,f[5]=9,f[6]=10,f[7]=11,f[8]=12,f[9]=14,f[10]=16;*/
	for(int i=0;i<n;++i){
		s[i]=rand()%n+1;//活动i开始时间
		f[i]=rand()%(n/2)+1+s[i];//活动i结束时间
	}
	quick_sort(s,f,0,n-1);//按照开始时间排序
	sort_final_time(s,f,n-1);//按照结束时间排序

	/*s[0]=0,s[1]=1,s[2]=2,s[3]=3,s[4]=3,s[5]=5,s[6]=5,s[7]=6,s[8]=8,s[9]=8,s[10]=12;	
	f[0]=6,f[1]=4,f[2]=14,f[3]=5,f[4]=9,f[5]=7,f[6]=9,f[7]=10,f[8]=11,f[9]=12,f[10]=16;*/
	for(int i=0;i<n;++i){
		cout<<s[i]<<"\t";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<f[i]<<"\t";
	}
	cout<<endl;
	delete []s;
	delete []f;
}
