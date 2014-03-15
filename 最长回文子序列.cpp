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

void print_longest_palindrome(int **p,char *c,int n)//打印最长回文字符串
{
	int length=p[0][n-1];
	char *cc=new char[length+1];
	cc[length]='\0';
	int i=0,j=n-1;//保存位置
	int low=0,high=length-1;//回文字符串中的上下下标	
	while (i<j){
		while (p[i][j]==p[i+1][j]){
			++i;
		}
		cc[low++]=c[i];
		while(p[i][j]==p[i][j-1]){
			--j;
		}
		cc[high--]=c[j];
		++i;
		--j;
	}	
	if(low==high){
		cc[low]=c[i];
	}
	for(int k=0;k<length;++k){
		cout<<cc[k];
	}
	cout<<endl;
	delete []cc;
}

int main()
{
	srand((unsigned)time(NULL));
	int n=23;
	n=rand()%20+20;
	char *s=new char[n];
	/*s[0]='n',s[1]='m',s[2]='g',s[3]='s',s[4]='v',s[5]='g',
	s[6]='r',s[7]='i',s[8]='s',s[9]='m',s[10]='y',s[11]='g',s[12]='x',
	s[13]='p',s[14]='p',s[15]='e',s[16]='j',s[17]='x',s[18]='p',s[19]='q',
	s[20]='j',s[21]='a',s[22]='i';*/
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
