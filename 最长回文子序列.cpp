#include <iostream>
#include <ctime>
#include <limits>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;

void longest_palindrome(char *s,int **p,int length)
{
	for(int i=0;i<length-1;++i){//初始化数组相关信息
		p[i][i]=1;
		int j=i+1;
		if(s[i]==s[j]){
			p[i][j]=2;
		}else{
			p[i][j]=1;
		}
	}
	p[length-1][length-1]=1;
	//for(int i=length-3;i>=0;--i){//从后往前
	//	for(int l=i+2;l<length;l++){
	//		if(s[i]==s[l]){
	//			p[i][l]=p[i+1][l-1]+2;
	//		}else if(p[i+1][l]>p[i][l-1]){
	//			p[i][l]=p[i+1][l];
	//		}else{
	//			p[i][l]=p[i][l-1];
	//		}
	//	}
	//}	
	for(int l=3;l<=length;l++){//长度1和2都已记录，此处长度由3开始，从前往后
		for(int i=0;i<length-l+1;i++){
			int j=i+l-1;
			if(s[i]==s[j]){
				p[i][j]=p[i+1][j-1]+2;
			}else if(p[i+1][j]>p[i][j-1]){
				p[i][j]=p[i+1][j];
			}else{
				p[i][j]=p[i][j-1];
			}
		}
	}
}

void print_longest_palindrome(int **p,char *c,int n)
{
	int length=p[0][n-1];
	int k=length/2;
	char *cc=new char[k];
	int i,j=0;//保存位置
	for(i=n-1;i>0 && j<k ;--i){
		if(p[0][i]!=p[0][i-1]){
			cc[j]=c[i];
			j++;
		}
	}
	char *cr=new char[length];
	cr[k]=c[i];//回文字符串中间值
	j=0;
	for(int m=0;m<k;++m,++j){
		cr[m]=cc[j];
		cr[length-m-1]=cc[j];
	}
	delete [] cc;
	for(int m=0;m<length;++m){
		cout<<cr[m];
	}
	cout<<endl;
	delete[]cr;
}

int main()
{
	srand((unsigned)time(NULL));
	int n;
	n=rand()%20+20;
	char *s=new char[n];
	for(int i=0;i<n;++i){
		//if(rand()%2){
			s[i]=rand()%26+'a';
			cout<<s[i];
		/*}else{
			s[i]=rand()%26+'A';
			cout<<s[i];
		}*/
	}
	cout<<endl;
	
	int **p=new int*[n];
	for(int i=0;i<n;++i){//存储最长回问字符长度信息，并用此构建最长回文字符串
		p[i]=new int [n];
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			p[i][j]=0;
		}
	}

	longest_palindrome(s,p,n);
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<p[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	print_longest_palindrome(p,s, n);
	delete[]s;
	for(int i=0;i<n;++i){
		delete []p[i];
	}
	delete[]p;
}
