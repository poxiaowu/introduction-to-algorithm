#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <string>
using namespace std;

const static enum cost{//枚举
	COPY=1,
	REPLACE=1,
	DELETE=4,
	INSERT=4,
	TWIDDLE=2,
	KILL=8
};
const static enum operation{//枚举
	OP_COPY=0,
	OP_REPLACE=1,
	OP_DELETE=2,
	OP_INSERT=3,
	OP_TWIDDLE=4,
	OP_KILL=5
};

void edit_distance(string &str1,string &str2,int **c,int ** op,int m,int n,int &kill_k)//编辑距离
{
	for(int i=1;i<=n;i++){
		c[0][i]=i*cost::INSERT;//代价
		op[0][i]=operation::OP_INSERT;//操作
	}
	for(int i=1;i<=m;++i){
		c[i][0]=i*cost::DELETE;
		op[i][0]=operation::OP_DELETE;
	}
	c[0][0]=0;
	op[0][0]=9;//任意赋不存在的值
	for(int i=1;i<=m;++i){//类似于最长公共子序列操作
		for(int j=1;j<=n;++j){
			c[i][j]=numeric_limits<int>::max();//初始为最大值
			if((str1[i-1]==str2[j-1])){
				c[i][j]=c[i-1][j-1]+cost::COPY;
				op[i][j]=operation::OP_COPY;
			}
			if((str1[i-1]!=str2[j-1])&&c[i-1][j-1]+cost::REPLACE<=c[i][j]){
				c[i][j]=c[i-1][j-1]+cost::REPLACE;
				op[i][j]=operation::OP_REPLACE;
			}
			if(i>=2 && j>=2 && str1[i-1]==str2[j-2] && str1[i-2]==str2[j-1] && c[i-2][j-2]+cost::TWIDDLE<=c[i][j]){
				c[i][j]=c[i-2][j-2]+cost::TWIDDLE;
				op[i][j]=operation::OP_TWIDDLE;
			}
			if(c[i-1][j]+cost::DELETE<=c[i][j]){
				c[i][j]=c[i-1][j]+cost::DELETE;
				op[i][j]=operation::OP_DELETE;
			}
			if(c[i][j-1]+cost::INSERT<=c[i][j]){
				c[i][j]=c[i][j-1]+cost::INSERT<c[i][j];
				op[i][j]=operation::OP_INSERT;
			}		
			cout<<i<<"\t"<<j<<"\t"<<c[i][j]<<"\t"<<op[i][j]<<endl;
		}		
	}
	for(int k=0;k<m;k++){//kill
		/*if(c[k][n]+KILL<=c[m][n]){
		c[m][n]=c[k][n]+KILL;
		op[m][n]=operation::OP_KILL;
		kill_k=k;
		}*/
		if(c[k][n]+(m-k)*cost::DELETE<=c[m][n]){
			c[m][n]=c[k][n]+(m-k)*cost::DELETE;
			op[m][n]=operation::OP_KILL;
			kill_k=k;
		}
	}
}

void edit_sequence(int **op,int m,int n,int kill_k)
{
	string str="";
	if(m==0 && n==0)
		return;
	if(op[m][n]==OP_COPY){
		m--,n--;
		str="copy";
	}else if(op[m][n]==OP_REPLACE){
		m--,n--;
		str="replace";
	}else if(op[m][n]==OP_TWIDDLE){
		m-=2,n-=2;
		str="twiddle";
	}else if(op[m][n]==OP_INSERT){
		n--;
		str="insert";
	}else if(op[m][n]==OP_DELETE){
		m--;
		str="delete";
	}else{
		m=kill_k;
		str="kill";
	}
	edit_sequence(op,m,n,kill_k);
	cout<<m<<"\t"<<n<<"\t"<<str<<endl;
}

int main()
{
	//srand((unsigned)time(NULL));
	string str1="algo";//gorithm
	string str2="alt";//truistic
	int m=str1.size();//字符串大小
	int n=str2.size();//字符串大小
	int **c=new int *[m+1];
	for(int i=0;i<m+1;++i){
		c[i]=new int [n+1];
	}
	int **op=new int *[m+1];
	for(int i=0;i<m+1;++i){
		op[i]=new int [n+1];
	}
	int kill_k=m;
	edit_distance(str1,str2,c,op,m,n,kill_k);
	for(int i=0;i<m+1;i++){
		for(int j=0;j<n+1;++j){
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}
	for(int i=0;i<m+1;i++){
		for(int j=0;j<n+1;++j){
			cout<<op[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	edit_sequence(op,m,n,kill_k);
	for(int i=0;i<m+1;++i){
		delete[]c[i];
		delete[]op[i];
	}
	delete[]c;
	delete[]op;
}
