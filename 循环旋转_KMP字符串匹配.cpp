#include <iostream>
#include <string>
using namespace std;


int * compute_prefix_function(string str)//计算字符串的前缀函数
{
	int m=str.length();
	int q=-1;
	int *prefix_table=new int[m];
	prefix_table[0]=q;
	for(int i=1;i<m;++i){
		while(q>-1 && str[q+1]!=str[i]){
			q=prefix_table[q];
		}		
		if(str[q+1]==str[i]){
			++q;
		}
		prefix_table[i]=q;
	}

	/*for(int i=0;i<m;++i){
		cout<<prefix_table[i]<<endl;
	}*/

	return prefix_table;
}

void KMP_matcher(string text,string pattern)//KMP字符串匹配算法
{
	int n=text.length();
	int m=pattern.length();
	int *prefix_table=compute_prefix_function(text);
	int q=-1;
	for(int i=0;i<n;++i){
		while(q>-1 && pattern[q+1]!=text[i]){
			q=prefix_table[q];
		}
		if(pattern[q+1]==text[i]){
			++q;
		}
		if(q==m-1){
			cout<<"pattern 是字符串的一个循环旋转"<<endl;
			q=prefix_table[q];
		}
	}
	delete [] prefix_table;
}


int main()
{
	string text="arc";
	string pattern="car";
	text+=text;//循环旋转测试，令S=T+T,那么如果T'是T的一个循环旋转的话，那么必然有T'和S匹配
	KMP_matcher(text,pattern);	
	return 0;
}
