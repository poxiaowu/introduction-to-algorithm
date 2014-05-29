#include <iostream>
#include <limits>
using namespace std;

void extend_shortest_paths(int **matrix,int **W,int **result,int n)//计算最短路径
{
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			int min=numeric_limits<int>::max();//保存最小值
			for(int k=0;k<n;++k){
				if(matrix[i][k]!=numeric_limits<int>::max() && W[k][j]!=numeric_limits<int>::max()){
					if(min>matrix[i][k]+W[k][j]){
						min=matrix[i][k]+W[k][j];
					}
				}
			}
			result[i][j]=min;
		}
	}
}

int ** faster_all_pairs_shortest_paths(int **matrix,int n)//重复平方技术计算所有结点对的最短路径
{
	int **result=new int *[n];
	for(int i=0;i<n;++i){
		result[i]=new int [n];
	}
	int **data=new int *[n];
	for(int i=0;i<n;++i){
		data[i]=new int [n];
		for(int j=0;j<n;++j){
			data[i][j]=matrix[i][j];
		}
	}

	int **mat;
	int m=1;
	while(m<n-1){
		mat=data;
		extend_shortest_paths(mat,mat,result,n);
		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				data[i][j]=result[i][j];
			}
		}
		m*=2;
	}
	for(int i=0;i<n;++i){
		delete [] data[i];
	}
	delete [] data;
	return result;
}

int ** slow_all_pairs_shortest_paths(int **matrix,int n)//一步一步计算
{
	int **result=new int *[n];
	for(int i=0;i<n;++i){
		result[i]=new int [n];
	}
	int **data=new int *[n];
	for(int i=0;i<n;++i){
		data[i]=new int [n];
		for(int j=0;j<n;++j){
			data[i][j]=matrix[i][j];
		}
	}

	int **mat;
	for(int i=0;i<n-2;++i){
		mat=data;
		extend_shortest_paths(mat,matrix,result,n);
		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				data[i][j]=result[i][j];
				cout<<data[i][j]<<"\t";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	for(int i=0;i<n;++i){
		delete [] data[i];
	}
	delete [] data;
	return result;
}

int ** print_precede_matrix(int **result,int **org,int n)//计算前驱子图
{
	int **pre_matrix=new int *[n];
	for(int i=0;i<n;++i){
		pre_matrix[i]=new int [n];
		pre_matrix[i][i]=i;
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(i!=j){
				for(int k=0;k<n;++k){	
					if(org[k][j]!=numeric_limits<int>::max() && k!=j){//判断在原始矩阵中结点k到结点j是否连通
						if(result[i][j]==result[i][k]+result[k][j]){
							pre_matrix[i][j]=k;
						}
					}
				}
			}
		}
	}
	return pre_matrix;
}
void print_short_paths(int **pre_matrix,int i,int j)
{
	if(i!=j){
		print_short_paths(pre_matrix,i,pre_matrix[i][j]);
		cout<<pre_matrix[i][j]<<"\t";
	}	
}
void print(int **result,int **pre_matrix,int n)
{
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(i!=j){
				cout<<"from node "<<i<<" to "<<j<<" : ";
				if(result[i][j]!=numeric_limits<int>::max()){
					print_short_paths(pre_matrix,i,j);
					cout<<j;
				}else{
					cout<<"no paths exist";
				}
				cout<<endl;
			}
		}
	}
}


int main()
{
	int max=numeric_limits<int>::max();//最大值
	int matrix[5][5]={0,3,8,max,-4,//邻接矩阵表示图
						max,0,max,1,7,
						max,4,0,max,max,
						2,max,-5,0,max,
						max,max,max,6,0};

	//int matrix[6][6]={0,max,max,max,-1,max,//邻接矩阵表示图
	//	1,0,max,2,max,max,
	//	max,2,0,max,max,-8,
	//	-4,max,max,0,3,max,
	//	max,7,max,max,0,max,
	//	max,5,10,max,max,0};
	int n=5;
	int **mat=new int *[n];
	for(int i=0;i<n;++i){
		mat[i]=new int [n];
		for(int j=0;j<n;++j){
			mat[i][j]=matrix[i][j];
		}
	}
	int **result=faster_all_pairs_shortest_paths(mat,n);//计算机结点间最短路径
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<result[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	int **pre_matrix=print_precede_matrix(result,mat,n);//计算前驱矩阵
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<pre_matrix[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	print(result,pre_matrix,n);
	for(int i=0;i<n;++i){
		delete [] mat[i];
		delete [] result[i];
		delete [] pre_matrix[i];
	}
	delete []mat;
	delete []result;
	delete []pre_matrix;
	return 0;
}
