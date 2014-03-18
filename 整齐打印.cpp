#include <iostream>
#include <limits>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;
const static int  M = 80;
void print_neatly(vector<string>&vec,int **extras,int **lc,int *c,int *p,int n)//整齐打印
{
	for(int i=0;i<n;++i){
		extras[i][i]=M-vec[i].size();//存储剩余可用长度
		for(int j=i+1;j<n;++j){
			extras[i][j]=extras[i][j-1]-1-vec[j].size();
		}
	}
	for(int i=0;i<n;++i){
		for(int j=i;j<n;++j){
			if(extras[i][j]<0){
				lc[i][j]=numeric_limits<int>::max();
			}else if(j==n-1 && extras[i][j]>=0){
				lc[i][j]=0;
			}else{
				lc[i][j]=extras[i][j]*extras[i][j]*extras[i][j];
			}
		}
	}
	c[0]=0;//初始值为0
	int tmp;
	for(int j=1;j<=n;++j){
		c[j]=numeric_limits<int>::max();
		for(int i=1;i<=j;++i){
			tmp=c[i-1]+lc[i-1][j-1];//可能会溢出
			if(tmp<0)//当lc为正无穷的时候，tmp可能会产生溢出，防止溢出情况
				tmp=numeric_limits<int>::max();
			if(tmp<c[j]){
				c[j]=tmp;
				p[j-1]=i-1;
			}
		}
		cout<<c[j]<<" ";
	}
}

int give_lines(vector<string>&vec,int *p,int n)
{
	int k;
	int i=p[n-1];
	if(i==0){
		k=0;
	}else{
		k=give_lines(vec,p,i)+1;
	}
	//cout<<"("<<k<<","<<i<<","<<n-1<<") ";
	for(int m=i;m<n;++m){
		cout<<vec[m]<<" ";
	}
	cout<<endl;
	return k;
}

int main()
{
	ifstream fin("test.txt");
	string str;
	vector<string> vec;
	while(!fin.eof()){//将文本信息保存到vector中
		fin>>str;
		vec.push_back(str);
	}
	int n=vec.size();//字符个数
	int **extras=new int *[n];//存储剩余空格数
	for(int i=0;i<n;++i){
		extras[i]=new int [n];
	}
	int **lc=new int *[n];//存储立方代价值
	for(int i=0;i<n;++i){
		lc[i]=new int [n];
	}
	int *c=new int [n+1];//最小立方和
	int *p=new int [n];
	print_neatly(vec,extras,lc,c,p,n);

	for(int i=1;i<=n;++i){
		cout<<c[i]<<" ";
		if(i%20==0){
			cout<<endl;
		}
	}
	cout<<endl;
	cout<<endl;
	cout<<endl;

	for(int i=1;i<=n;++i){
		cout<<p[i-1]<<" ";
		if(i%20==0){
			cout<<endl;
		}
	}
	cout<<endl;

	give_lines(vec,p,n);
	for(int i=0;i<n;++i){
		delete[]extras[i];
		delete[]lc[i];
	}
	delete [] extras;
	delete [] lc;
	delete [] c;
	delete [] p;
}
