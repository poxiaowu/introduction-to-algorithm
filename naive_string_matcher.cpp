#include <iostream>
#include <string>
using namespace std;

void naive_string_matcher(string strSrc,string strDst)//朴素字符串匹配算法
{
	int lenSrc=strSrc.length();
	int lenDst=strDst.length();
	for(int i=0;i<=lenSrc-lenDst;++i){
		int j;
		for(j=0;j<lenDst;++j){
			if(strSrc[i+j]!=strDst[j]){
				break;
			}
		}
		if(j==lenDst){
			cout<<"pattern occurs with shift "<<i<<endl;
		}
	}
}

void naive_fast_string_matcher(string strSrc,string strDst)
{//pattern里每个字符都不一样
	int lenSrc=strSrc.length();
	int lenDst=strDst.length();
	for(int i=0,j=0;i<lenSrc;++i){
		if(strSrc[i]==strDst[j] && j<lenDst){
			++j;
		}else{
			if(j){
				j=0;
				--i;
			}
		}
		if(j==lenDst){
			cout<<"pattern occurs with shift "<<i-lenDst+1<<endl;
		}
	}	
}

int main()
{
	string strSrc,strDst;
	strSrc="acaabc";
	strDst="aab";
	naive_string_matcher(strSrc,strDst);
	return 0;
}
