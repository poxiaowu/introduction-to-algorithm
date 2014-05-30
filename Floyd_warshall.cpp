#include <iostream>
#include <limits>
using namespace std;

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

int** floyd_warshall(int **matrix,int ** result_matrix, int n)//结点对最短路径
{
	int **result=new int *[n];
	int **pre=new int *[n];
	int **precede_matrix=new int*[n];//前驱矩阵
	//int **result_matrix=new int*[n];//存放矩阵的前驱结点
	for(int i=0;i<n;++i){
		result[i]=new int [n];
		pre[i]=new int [n];
		precede_matrix[i]=new int [n];
		//result_matrix[i]=new int [n];
		for(int j=0;j<n;++j){
			result[i][j]=matrix[i][j];
			if(matrix[i][j]!=numeric_limits<int>::max() && i!=j){
				result_matrix[i][j]=i;
			}else{
				result_matrix[i][j]=-1;//如果不存在相连，则标记为-1
			}
		}
	}

	for(int k=0;k<n;++k){

		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				pre[i][j]=result[i][j];
				precede_matrix[i][j]=result_matrix[i][j];//前驱结点矩阵
			}
		}

		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				if(pre[i][k]!=numeric_limits<int>::max() && pre[k][j]!=numeric_limits<int>::max()){
					result[i][j]=min(pre[i][j],pre[i][k]+pre[k][j]);
					
					if(pre[i][j]<=pre[i][k]+pre[k][j]){
						result_matrix[i][j]=precede_matrix[i][j];
					}else{
						result_matrix[i][j]=precede_matrix[k][j];
					}
				}
			}
		}

		for(int i=0;i<n;++i){//打印最短路径信息和权重信息
			for(int j=0;j<n;++j){
				if(result[i][j]==numeric_limits<int>::max()){
					cout<<"inf ";
				}else{
					cout<<result[i][j]<<" ";
				}
			}

			cout<<"\t\t";

			for(int j=0;j<n;++j){
				if(result_matrix[i][j]!=-1){
					cout<<result_matrix[i][j]<<" ";
				}else{
					cout<<"nil ";
				}
			}
			cout<<endl;
		}
		cout<<endl;
	}
	for(int i=0;i<n;++i){//删除矩阵
		delete []pre[i];
		delete [] precede_matrix[i];
	}
	delete [] pre;
	delete [] precede_matrix;

	return result;
}

int main()
{
	int max=numeric_limits<int>::max();//最大值
	//int matrix[5][5]={0,3,8,max,-4,//邻接矩阵表示图
	//					max,0,max,1,7,
	//					max,4,0,max,max,
	//					2,max,-5,0,max,
	//					max,max,max,6,0};

	int matrix[6][6]={0,max,max,max,-1,max,//邻接矩阵表示图
		1,0,max,2,max,max,
		max,2,0,max,max,-8,
		-4,max,max,0,3,max,
		max,7,max,max,0,max,
		max,5,10,max,max,0};
	int n=6;
	int **mat=new int *[n];
	for(int i=0;i<n;++i){
		mat[i]=new int [n];
		for(int j=0;j<n;++j){
			mat[i][j]=matrix[i][j];
		}
	}
	int **precede=new int *[n];
	for(int i=0;i<n;++i){
		precede[i]=new int [n];
	}
	int **result=floyd_warshall(mat,precede,n);

	cout<<"print the shortest weight and precede matrix"<<endl;

	for(int i=0;i<n;++i){//打印最短路径信息和权重信息
		for(int j=0;j<n;++j){
			if(result[i][j]==numeric_limits<int>::max()){
				cout<<"inf ";
			}else{
				cout<<result[i][j]<<" ";
			}
		}

		cout<<"\t\t";

		for(int j=0;j<n;++j){
			if(precede[i][j]!=-1){
				cout<<precede[i][j]<<" ";
			}else{
				cout<<"nil ";
			}
		}
		cout<<endl;
	}
	cout<<endl;

	print(result,precede,n);	
	
	for(int i=0;i<n;++i){
		delete [] mat[i];
		delete [] precede[i];
		delete [] result[i];
	}
	delete []mat;
	delete []precede;
	delete []result;
	return 0;
}
