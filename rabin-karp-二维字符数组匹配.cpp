#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void two_d_rabin_karp_matcher(char **T,int n1,int n2,char **P,int m1,int m2,int d,int q)//二维模式匹配
{
	int *pattern=new int[m2];
	int *text=new int[n2];
	for(int i=0;i<m2;++i){//将2维模式转换为1维
		pattern[i]=0;		
		for(int j=0;j<m1;++j){
			pattern[i]=(d*pattern[i]+P[j][i])%q;
		}
	}
	for(int i=0;i<n2;++i){//列数
		text[i]=0;
		for(int j=0;j<m1;++j){//和模式行数一样
			text[i]=(d*text[i]+T[j][i])%q;
		}
	}

	int h=static_cast<int>(pow(d*1.0,m2-1))%q;
	int p=0;
	int t=0;
	for(int i=0;i<m2;++i){//将一维数组转换成单元素值
		p=(d*p+pattern[i])%q;
		t=(d*t+text[i])%q;
	}
	delete []pattern;
	for(int he=0;he<=n1-m1;++he){//T数组的行
		if(he<=n1-m1 && he>0){
			for(int c=0;c<n2;++c){
				int th=(T[he-1][c]*h)%q;
				int t_th=text[c]-th;
				while(t_th<0){
					t_th+=q;
				}
				t_th=(t_th*d)%q;
				t_th=t_th+T[he+m1-1][c];
				text[c]=t_th%q;
			}
			t=0;//初始值为0
			for(int i=0;i<m2;++i){//将一维数组转换成单元素值
				t=(d*t+text[i])%q;
			}
		}
		for(int w=0;w<=n2-m2;++w){
			if(p==t){
				int i=0,j=0;
				bool flag=false;//判断是否存在不相等的情况
				for(i=0;i<m1;++i){
					if(flag){
						break;
					}
					for(j=0;j<m2;++j){
						if(P[i][j]!=T[he+i][w+j]){
							flag=true;
							break;
						}
					}
				}
				if(!flag){
					cout<<"pattern occurs with shift ("<<he<<" , "<<w<<") "<<endl;
				}
			}	
			if(w<n2-m2){//利用霍纳法则计算下一个值
				//Ts+1=(d(Ts-T[s+1]h)+T[s+m+1])mod q
				int ts=(text[w]*h)%q;
				int t_ts=t-ts;
				while(t_ts<0){
					t_ts+=q;
				}
				t_ts=(t_ts*d)%q;
				t=t_ts+text[w+m2];
				t=t%q;
			}
		}
	}
	
	delete []text;
}


int main()
{
	int n1=5,n2=5,m1=2,m2=2;
	char text[5][5] = {
                       { 'a', 'b', 'a', 'b', 'a' },
                       { 'a', 'b', 'a', 'b', 'a' },
                       { 'a', 'b', 'b', 'a', 'a' },
                       { 'a', 'b', 'a', 'a', 'b' },
                       { 'b', 'b', 'a', 'b', 'a' }};
	char **pt=new char *[n1];
	for(int i=0;i<n1;++i){
		pt[i]=new char[n2];
		for(int j=0;j<n2;++j){
			pt[i][j]=text[i][j];
		}
	}

   char pattern[2][2] = {
					   { 'a', 'b' },
					   { 'b', 'a' }};

   char **pp=new char *[m1];
   for(int i=0;i<m1;++i){
		pp[i]=new char[m2];
		for(int j=0;j<m2;++j){
			pp[i][j]=pattern[i][j];
		}
   }
	int d=10;
	int q=13;
	two_d_rabin_karp_matcher(pt,5,5,pp,2,2,d,q);

	for(int i=0;i<n1;++i){
		delete[]pt[i];
	}
	delete[]pt;
	for(int i=0;i<m1;++i){
		delete [] pp[i];
	}
	delete [] pp;
	return 0;
}
