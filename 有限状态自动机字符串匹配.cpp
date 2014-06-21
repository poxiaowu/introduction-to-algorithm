#include <iostream>
#include <map>
#include <string>
using namespace std;

bool suffix_verify(string pattern,char ch,int k,int q)//检验P_k 是否是P_q_ch的最大前缀
{
	if(k<0){
		return true;
	}
	if(pattern[k]!=ch){
		return false;
	}else{
		while(k>=1){
			if(pattern[k-1]!=pattern[q]){
				return false;
			}
			--k;--q;
		}
	}
	return true;
}

int ** compute_transition_function(string pattern,string altab)//计算转业函数
{
	int n=pattern.length()+1;//状态转换表的大小；
	int m=altab.length();
	int **transTab=new int *[n];
	for(int i=0;i<n;++i){
		transTab[i]=new int [m];//状态转移表
	}
	int k=n;
	for(int q=0;q<n;++q){
		for(int j=0;j<m;++j){
			k=min(n,q+1);
			do{
				--k;
			}while(!suffix_verify(pattern,altab[j],k,q-1));
			transTab[q][j]=k+1;
		}
	}
	/*for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			cout<<transTab[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;*/
	return transTab;
}

void finite_automaton_matcher(string text,int **transTab,map<char,int>ma,int m)//有限状态自动机字符串匹配
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
	string pattern="ab";
	string altab="abc";
	string text="abababacaba";
	map<char,int>ma;
	for(int i=0;i<altab.length();++i){
		ma[altab[i]]=i;
	}
	int **transTab=compute_transition_function(pattern,altab);
	int m=pattern.length();
	finite_automaton_matcher(text,transTab,ma,m);
	for(int i=0;i<m+1;++i){
		delete[]transTab[i];
	}
	delete [] transTab;
	return 0;
}
