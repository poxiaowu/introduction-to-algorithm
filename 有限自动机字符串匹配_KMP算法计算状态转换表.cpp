#include <iostream>
#include <string>
#include <map>
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

int ** KMP_transition_function(string pattern,string alptable)//KMP算法计算状态转移表
{	
	int n=pattern.length();
	int m=alptable.length();
	int *prefix_table=compute_prefix_function(pattern);
	int **transTab=new int*[n+1];//状态转换表
	for(int i=0;i<n+1;++i){
		transTab[i]=new int [m];
	}
	int q;
	for(int i=0;i<n+1;++i){		
		for(int j=0;j<m;++j){
			q=i-1;
			while(q>-1 && pattern[q+1]!=alptable[j]){
				q=prefix_table[q];
			}
			if(pattern[q+1]==alptable[j]){
				++q;
			}
			transTab[i][j]=q+1;
		}
	}	
	delete [] prefix_table;

	for(int i=0;i<n+1;++i){
		for(int j=0;j<m;++j){
			cout<<transTab[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

	return transTab;
}

void finite_automaton_matcher(string text,int **transTab,map<char,int>ma,int m)//利用kmp算法计算状态转换表的有限自动机算法
{
	int n=text.length();
	int q=0;
	for(int i=0;i<n;++i){
		q=transTab[q][ma[text[i]]];
		if(q==m){
			cout<<"Pattern occurs with shift "<<i-m+1<<endl;
		}
	}
}

int main()
{
	string text="abababacaba";
	string pattern="ababaca";
	string alptable="abc";
	map<char,int>ma;
	for(int i=0;i<alptable.length();++i){
		ma[alptable[i]]=i;
	}
	int **transTab=KMP_transition_function(pattern,alptable);
	int m=pattern.length();
	finite_automaton_matcher(text,transTab,ma,m);
	for(int i=0;i<m+1;++i){
		delete []transTab[i];
	}
	delete [] transTab;
	swap(map<char,int>(),ma);
	return 0;
}
