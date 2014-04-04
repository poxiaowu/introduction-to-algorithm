#include<iostream>
#include <limits>
#include<ctime>
using namespace std;

void recursive_activity_selector(int *s,int *f,int l,int h)//递归贪心算法
{
	int m=l+1;
	while (m<h && s[m]<f[l]){
		++m;
	}
	if(m<h){
		cout<<m<<"\t";
		recursive_activity_selector(s,f,m,h);
	}
}

void recursive_activity_selector_reverse(int *s,int *f,int l,int h)//从活动开始时间比较晚的活动开始选择
{
	int m=h-1;
	while (m>l &&f[m]>s[h]){
		--m;
	}
	if(m>l){
		cout<<m<<"\t";
		recursive_activity_selector_reverse(s,f,l,m);
	}
}

void greedy_activity_selector(int *s,int *f,int h)//迭代贪心算法
{
	int m=0;
	for(int i=1;i<h;++i){
		if(s[i]>=f[m]){
			cout<<i<<"\t";
			m=i;
		}
	}
}
void dynamic_activity_selector(int *s,int *f,int **c,int **act,int n)//动态规划-自底向上
{
	for(int i=0;i<n;++i){
		c[i][i]=0;//如果只有一个元素，则两者之间最长的活动只有0个
		c[i][i+1]=0;
	}
	c[n][n]=0;
	int j,k;
	for(int l=2;l<=n;++l){//活动区间
		for(int i=0;i<n-l+1;++i){
			j=i+l;
			k=j-1;
			c[i][j]=0;
			while (f[k]>f[i]){
				if(f[i]<=s[k] && f[k]<=s[j] && c[i][k]+c[k][j]+1>c[i][j]){
					 c[i][j]=c[i][k]+c[k][j]+1;
					 act[i][j]=k;
				}
				--k;
			}
		}
	}
}
void print_activity(int **act,int l,int h)
{
	int k=act[l][h];
	if(k){
		print_activity(act,l,k);
		cout<<k<<"\t";
		print_activity(act,k,h);
	}
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main()
{
	srand((unsigned)time(NULL));
	int n=20;
	int *s=new int[n];
	int *f=new int[n];
	//s[0]=0,s[1]=1,s[2]=3,s[3]=0,s[4]=5,s[5]=3,s[6]=5,s[7]=6,s[8]=8,s[9]=8,s[10]=2,s[11]=12,s[12]=numeric_limits<int>::max();	
	//f[0]=0,f[1]=4,f[2]=5,f[3]=6,f[4]=7,f[5]=9,f[6]=9,f[7]=10,f[8]=11,f[9]=12,f[10]=14,f[11]=16,f[12]=numeric_limits<int>::max();
	s[0]=0,f[0]=0,s[n-1]=numeric_limits<int>::max(),f[n-1]=numeric_limits<int>::max();
	for(int i=1;i<n-1;++i){
		s[i]=rand()%101;
		f[i]=rand()%201;
	}
	qsort(s,n,sizeof(int),compare);
	qsort(f,n,sizeof(int),compare);
	int tmp;
	for(int i=1;i<n-1;++i){
		if(s[i]>f[i]){
			tmp=f[i];
			f[i]=s[i];
			s[i]=tmp;
		}
	}
	for(int i=0;i<n;++i){
		cout<<s[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<f[i]<<" ";
	}
	cout<<endl;

	int *r=new int[n];
	for(int i=0;i<n;++i){
		r[i]=0;
	}
	recursive_activity_selector(s,f,0,n-1);
	cout<<endl;
	recursive_activity_selector_reverse(s,f,0,n-1);
	cout<<endl;
	greedy_activity_selector(s,f,n-1);
	cout<<endl;

	int **c=new int*[n];//
	for(int i=0;i<n;++i){
		c[i]=new int[n];
	}
	int **act=new int*[n];//
	for(int i=0;i<n;++i){
		act[i]=new int[n];
		for(int j=0;j<n;++j){
			act[i][j]=0;
		}
	}
	dynamic_activity_selector(s,f,c,act,n-1);//动态规划-自底向上
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<act[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	print_activity(act,0,n-1);
	cout<<endl;
	delete []s;
	delete []f;
	for(int i=0;i<n;++i){
		delete [] c[i];
		delete [] act[i];
	}
	delete [] c;
	delete [] act;
}
