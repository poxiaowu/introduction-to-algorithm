#include <iostream>
#include <string>
using namespace std;

int * compute_prefix_function(string pattern)//计算前缀函数
{
	int m=pattern.length();
	int *pre_func=new int[m];//前缀函数
	int k=-1;
	pre_func[0]=k;
	for(int q=1;q<m;++q){
		while(k>-1 && pattern[k+1]!=pattern[q]){
			k=pre_func[k];
		}
		if(pattern[k+1]==pattern[q]){
			++k;
		}
		pre_func[q]=k;
	}
	/*for(int i=0;i<m;++i){
		cout<<pre_func[i]<<endl;
	}*/
	return pre_func;
}

void kmp_matcher(string text,string pattern)//KMP字符串匹配算法
{
	int n=text.length();
	int m=pattern.length();
	int *pre_func=compute_prefix_function(pattern);
	int q=-1;
	for(int i=0;i<n;++i){
		while(q>-1 && pattern[q+1]!=text[i]){
			q=pre_func[q];
		}
		if(pattern[q+1]==text[i]){
			++q;
		}
		if(q==m-1){
			cout<<"pattern occurs with shift "<<i-m+1<<endl;
			q=pre_func[q];
		}
	}
	delete [] pre_func;
}

int main()
{
	string pattern="ababaca";
	string text="bacbababacabcbab";
	kmp_matcher(text,pattern);	
	return 0;
}
