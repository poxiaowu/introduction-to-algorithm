#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void rabin_karp_matcher(string T,string P,int d,int q)//rabin-karp字符串匹配
{
	int n=T.length();
	int m=P.length();
	int h=static_cast<int>(pow(d*1.0,m-1))%q;
	int p=0;
	int t=0;
	for(int i=0;i<m;++i){
		p=(d*p+P[i])%q;
		t=(d*t+T[i])%q;
	}
	for(int s=0;s<=n-m;++s){
		if(p==t){
			int j=0;
			for(j=0;j<m;++j){
				if(T[s+j]!=P[j]){
					break;
				}
			}
			if(j==m){
				cout<<"pattern occurs with shift "<<s<<endl;
			}
		}	
		if(s<n-m){//利用霍纳法则计算下一个值
			//Ts+1=(d(Ts-T[s+1]h)+T[s+m+1])mod q
			int ts=(T[s]*h)%q;
			int t_ts=t-ts;
			while(t_ts<0){
				t_ts+=q;
			}
			t_ts=(t_ts*d)%q;
			t=t_ts+T[s+m];
			t=t%q;
		}
	}
}

int main()
{
	string T="23590231415267399213141531415";
	string P="31415";
	int d=10;
	int q=13;
	rabin_karp_matcher(T,P,d,q);
	return 0;
}
