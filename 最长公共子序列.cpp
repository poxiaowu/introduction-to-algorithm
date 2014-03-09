#include <iostream>
#include <ctime>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;

void lcs_length(char *a,int m,char *b,int n,int **c)//最长公共子序列
{//自底向上法
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j){
			if(a[i-1]==b[j-1]){
				c[i][j]=c[i-1][j-1]+1;
			}else if(c[i-1][j]>=c[i][j-1]){
				c[i][j]=c[i-1][j];
			}else{
				c[i][j]=c[i][j-1];
			}
		}
	}
}

int memo_lcs_length(char *a,int m,char *b,int n,int **c)
{//递归的，自上而下
	if(c[m][n]!=numeric_limits<int>::min())
		return c[m][n];
	if(a[m-1]==b[n-1]){
		c[m][n]=memo_lcs_length(a,m-1,b,n-1,c)+1;
	}else{
		c[m][n]=max(memo_lcs_length(a,m-1,b,n,c),memo_lcs_length(a,m,b,n-1,c));
	}
	return c[m][n];
}


void print_lcs_recursive(char *a,char *b,int **c,int m,int n)
{
	if(m==0 || n==0)
		return;
	if(c[m][n]==c[m-1][n-1]+1){
		print_lcs_recursive(a,b,c,m-1,n-1);
		cout<<a[m-1];
	}else if(c[m][n]==c[m-1][n]){
		print_lcs_recursive(a,b,c,m-1,n);
	}else{
		print_lcs_recursive(a,b,c,m,n-1);
	}
}

void print_lcs_iterator(char *a,char *b,int **c,int m,int n)
{
	while (m!=0 && n!=0){
		if(c[m][n]==c[m-1][n-1]+1){
			m-=1;
			n-=1;
			cout<<a[m-1];
		}else if(c[m][n]==c[m-1][n]){
			m-=1;
		}else{
			n-=1;
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int m,n;
	while (m=rand()%53,m<30);
	while(n=rand()%53,n<30);
	m=10000,n=10500;
	/*m=8,n=9;
	char a[8]={'1','0','0','1','0','1','0','1'};
	char b[9]={'0','1','0','1','1','0','1','1','0'};*/
	char *a=new char[m];
	char *b=new char[n];
	for(int i=0;i<m;++i){//随机生成字符数组
		if(rand()%2)
			a[i]=rand()%26+'A';
		else
			a[i]=rand()%26+'a';
	}
	for(int i=0;i<n;++i){
		if(rand()%2)
			b[i]=rand()%26+'A';
		else
			b[i]=rand()%26+'a';
	}
	/*for(int i=0;i<m;++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<b[i]<<" ";
	}
	cout<<endl;*/

	int **c=new int *[m+1];
	for(int i=0;i<m+1;++i){
		c[i]=new int [n+1];
	}
	for(int i=0;i<m+1;++i){
		c[i][0]=0;
	}
	for(int j=0;j<n+1;++j){
		c[0][j]=0;
	}
	for(int i=1;i<m+1;++i){
		for(int j=1;j<n+1;++j){
			c[i][j]=numeric_limits<int>::min();
		}
	}
	cpu_timer t1;
	t1.start();
	lcs_length(a,m,b,n,c);
	t1.stop();
	cout<<t1.format();
	/*for(int i=0;i<m+1;++i){
		for(int j=0;j<n+1;++j){
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}*/
	cout<<c[m][n]<<endl;
	print_lcs_iterator(a,b,c,m,n);
	cout<<endl;

	for(int i=0;i<m+1;++i){
		c[i][0]=0;
	}
	for(int j=0;j<n+1;++j){
		c[0][j]=0;
	}
	for(int i=1;i<m+1;++i){
		for(int j=1;j<n+1;++j){
			c[i][j]=numeric_limits<int>::min();
		}
	}
	cpu_timer t2;
	t2.start();
	memo_lcs_length(a,m,b,n,c);
	t2.stop();
	cout<<t2.format();
	/*for(int i=0;i<m+1;++i){
		for(int j=0;j<n+1;++j){
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}*/
	cout<<c[m][n]<<endl;
	print_lcs_iterator(a,b,c,m,n);
	cout<<endl;
	delete[]a;
	delete[]b;
	delete[]c;
}   
