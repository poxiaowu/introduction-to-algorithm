#include <iostream>
#include <cstring>
using namespace std;
const int N=1000005;
int p[N<<1];
char s[N<<1];
char str[N];

int longest_palindrome(char * str)//Manacher算法
{
	int len=(strlen(str)<<1)+1;	
	for(int i=0;i<len;++i){
		s[i]='#';//插入间隔符
		p[i]=1;
	}
	for(int i=0;i<len/2;++i){
		s[(i<<1)+1]=str[i];
	}

	int mx=0,id=0;
	int max=0;
	for(int i=1;i<len;++i){
		p[i]=mx>i?min(p[2*id-i],mx-i):1;
		while(i>=p[i] && s[i+p[i]]==s[i-p[i]]){
			++p[i];
		}
		if(i+p[i]>mx){
			mx=i+p[i];
			id=i;
		}
		if (p[i]>max){
			max=p[i];
		}
	}
	return max-1;
}

int main()
{
	int len;
	int co=0;
	int C;
	cin>>C;
	for(int i=0;i<C;++i){
		cin>>str;
		len=longest_palindrome(str);
		++co;
		cout<<len<<endl;
	}
	return 0;
}
