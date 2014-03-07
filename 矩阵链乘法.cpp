#include <iostream>
#include <limits>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;

void matrix_multiply(int **a,int **b,int **c,int m,int n,int q)//矩阵乘法
{//m,n表示矩阵a的行数和列数，n,q表示矩阵b的行数和列数，c的行数和列数应该为m,q
	/*for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;

	for(int i=0;i<n;++i){
		for(int j=0;j<q;++j){
			cout<<b[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;*/

	for(int i=0;i<m;++i){
		for(int j=0;j<q;++j){
			c[i][j]=0;//初始化为0
			for(int k=0;k<n;++k){
				c[i][j]+=a[i][k]*b[k][j];//矩阵乘法
			}
		}
	}
	/*for(int i=0;i<m;++i){
	for(int j=0;j<q;++j){
	cout<<c[i][j]<<"\t";
	}
	cout<<endl;
	}
	cout<<endl;*/
}

void matrix_chain_order(int *p,int n,int **m,int **s)//计算矩阵连乘的最小代价值
{
	for(int i=0;i<n-1;++i){//n-1个矩阵连乘
		m[i][i]=0;
	}
	for(int l=2;l<n;l++){//l个矩阵连乘
		for(int i=0;i<n-l;++i){//最大为n-1个矩阵连乘
			int j=i+l-1;//j为第j个矩阵的下标
			m[i][j]=numeric_limits<int>::max();//初始时默认代价为最大值
			for(int k=i;k<j;++k){
				int q=m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1];//当k为分割点是，矩阵连乘的代价
				if(q<m[i][j]){
					m[i][j]=q;//更新代价值
					s[i][j-1]=k;//
				}
			}
		}
	}
}

void print_optimal_parens(int **s,int i,int j)//构造最优解
{
	if(i==j){
		cout<<"A"<<i+1;
	}else{
		cout<<"(";
		print_optimal_parens(s,i,s[i][j-1]);
		print_optimal_parens(s,s[i][j-1]+1,j);
		cout<<")";
	}
}

int ** optimal_matrix_multiply(int *** matrix,int **s,int *p,int i,int j)//最优矩阵连乘
{//matrix所有矩阵，s是最优的划分，i,j表示下标索引
	if(i==j){
		return matrix[i];
	}else{
		int **mat_left =optimal_matrix_multiply(matrix,s,p,i,s[i][j-1]);
		int **mat_right=optimal_matrix_multiply(matrix,s,p,s[i][j-1]+1,j);	
		int **mat_result=new int*[p[i]];//矩阵的行数
		for(int k=0;k<p[i];++k){
			mat_result[k]=new int [p[j+1]];//矩阵列数
		}	
		//cout<<p[i]<<"\t"<<p[s[i][j-1]+1]<<"\t"<<p[j+1]<<endl;
		matrix_multiply(mat_left,mat_right,mat_result,p[i],p[s[i][j-1]+1],p[j+1]);
		for(int a=0;a<p[i];++a){//删除相关的中间数组以及数组本身
			delete []mat_left[a];
		}
		delete mat_left;
		for(int b=0;b<p[s[i][j-1]+1];++b){
			delete[]mat_right[b];
		}
		delete mat_right;
		return mat_result;
	}		
}
void brute_matrix_multiply(int ***matrix,int* p,int n,int ** res)//暴力乘法
{
	int ***result=new int **[n-1];//存放结果矩阵数组
	result[0]=matrix[0];//result[0]为第一个矩阵，初始赋值
	for(int i=0;i<n-2;++i){
		result[i+1]=new int*[p[0]];//创建乘积数组,row
		for(int j=0;j<p[0];++j){
			result[i+1][j]=new int[p[i+2]];
		}
		//cout<<p[0]<<"\t"<<p[i+1]<<"\t"<<p[i+2]<<endl;
		matrix_multiply(result[i],matrix[i+1],result[i+1],p[0],p[i+1],p[i+2]);
		for(int a=0;a<p[0];++a){
			if(i!=0)//不要删除matrix里第一个矩阵
				delete result[i][a];
		}
		if(i!=0)//不要删除matrix里第一个矩阵
			delete [] result[i];//删除数组
	}
	for(int a=0;a<p[0];++a){
		for(int b=0;b<p[n-1];++b){
			res[a][b]=result[n-2][a][b];
		}
	}
	delete [] result[n-2];
	delete []result;//删除数组
}


int main()
{
	srand((unsigned)time(NULL));
	int n=100;
	int *p=new int[n];
	for(int i=0;i<n;++i){
		p[i]=rand()%5+5;
		//p[i]=10;
	}
	//p[0]=30,p[1]=35,p[2]=15,p[3]=5,p[4]=10,p[5]=20,p[6]=25;
	/*for(int i=0;i<n;++i){//p中存放矩阵维度
		cout<<p[i]<<"\t";
	}
	cout<<endl<<endl;*/

	int **m=new int *[n-1];
	int **s=new int *[n-2];
	for(int i=0;i<n-1;++i){
		m[i]=new int [n-1];		
	}
	for(int i=0;i<n-2;++i){
		s[i]=new int [n-2];	
	}	
	//给矩阵随机赋值
	int ***matrix=new int **[n-1];//n-1个矩阵
	for(int i=0;i<n-1;++i){//n-1个矩阵
		matrix[i]=new int *[p[i]];
		for(int j=0;j<p[i];++j){
			matrix[i][j]=new int [p[i+1]];
			for(int k=0;k<p[i+1];++k){
				matrix[i][j][k]=rand()%5-3;
			}
		}
	}
	//for(int i=0;i<n-1;++i){//显示n-1个矩阵的元素
	//	for(int j=0;j<p[i];++j){
	//		for(int k=0;k<p[i+1];++k){
	//			cout<<matrix[i][j][k]<<" ";
	//		}
	//		cout<<endl;
	//	}
	//	cout<<endl;
	//}
	
	int **res=new int *[p[0]];//存储最后结果
	for(int i=0;i<p[0];++i){
		res[i]=new int [p[n-1]];
	}
	cpu_timer t1;
	t1.start();
	brute_matrix_multiply(matrix,p,n,res);
	t1.stop();
	cout<<t1.format();
	for(int i=0;i<p[0];++i){
		for(int j=0;j<p[n-1];++j){
			cout<<res[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<p[0];++i){//删除结果的矩阵
		delete []res[i];
	}
	delete []res;
	
	cpu_timer t2;
	t2.start();
	matrix_chain_order(p,n,m,s);//计算矩阵连乘的最优解
	cout<<m[0][n-2]<<endl;
	/*for(int i=0;i<n-1;++i){//打印代价数组
		for(int j=0;j<n-1;++j){		
			cout<<m[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<n-2;++i){//打印最优组合数组
		for(int j=0;j<n-2;++j){
			cout<<s[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;*/
	for(int i=0;i<n-1;++i){
		delete[] m[i];
	}
	delete []m;//删除代价数组	
	print_optimal_parens(s,0,n-2);	
	cout<<endl;
	int **result=optimal_matrix_multiply(matrix,s,p,0,n-2);
	t2.stop();
	cout<<t2.format();
	for(int i=0;i<p[0];++i){
		for(int j=0;j<p[n-1];++j){
			cout<<result[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<n-2;++i){//删除矩阵相乘分割数组
		delete[]s[i];
	}
	delete[]s;
	for(int i=0;i<p[0];++i){//删除存储结果的二维数组
		delete[]result[i];
	}
	delete []result;
	

	//for(int i=0;i<n-1;++i){//删除各个矩阵数组
	//	for(int j=0;j<p[i];++j){
	//		delete [] matrix[i][j];
	//	}
	//	delete []matrix[i];
	//}
	//delete []matrix;
	delete []p;
}
