#include <iostream>
#include <limits>
#include <stack>
using namespace std;


bool dfs(int **residual,bool *flag,int index,stack<int> &path ,int n)//深度优先遍历,求图中是否存在从起点到终点的路径
{
	if(index!=n-1){
		flag[index]=true;
		path.push(index);
		int i;
		bool re_f=true;
		for(i=0;i<n;++i){
			if(index != i && !flag[i] && residual[index][i]!=numeric_limits<int>::max()){		
				re_f = dfs(residual,flag,i,path,n);
				if(re_f){
					return re_f;
				}				
			}			
		}	
		path.pop();
		flag[index]=false;
		return false;
	}
	//当index==n-1时存在一条路径
	path.push(index);
	return true;
}

void ford_fulkerson(int **matrix,int n)//ford_fulkerson
{
	stack<int> path;//存放路径的栈
	bool *flag=new bool[n];
	for(int i=0;i<n;++i){
		flag[i]=false;
	}
	int min_flow=numeric_limits<int>::max();
	while(dfs(matrix,flag,0,path,n)){		
		for(int i=0;i<n;++i){
			flag[i]=false;
		}
		int size=path.size();
		int *arr_path=new int[size];
		for(int i=size-1;i>=0;--i){
			arr_path[i]=path.top();
			path.pop();
		}
		min_flow=numeric_limits<int>::max();
		for(int i=0;i<size-1;++i){//求最小流
			if(matrix[arr_path[i]][arr_path[i+1]]<min_flow){
				min_flow=matrix[arr_path[i]][arr_path[i+1]];
			}
		}

		for(int i=0;i<size-1;++i){//更改增广路径的值
			if(!(matrix[arr_path[i]][arr_path[i+1]]-=min_flow)){
				matrix[arr_path[i]][arr_path[i+1]]=numeric_limits<int>::max();
			}
			if(matrix[arr_path[i+1]][arr_path[i]]==numeric_limits<int>::max()){
				matrix[arr_path[i+1]][arr_path[i]]=0;
			}
			matrix[arr_path[i+1]][arr_path[i]]+=min_flow;
		}

		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				if(matrix[i][j]==numeric_limits<int>::max()){
					cout<<"max ";
				}else{
					cout<<matrix[i][j]<<" ";
				}
			}
			cout<<endl;
		}
		cout<<endl;
		swap(stack<int>(),path);
		delete [] arr_path;
	}
}


int main()
{
	int max=numeric_limits<int>::max();//最大值
	//int matrix_edge[5][5]={0,3,8,max,-4,//邻接矩阵表示图
	//					max,0,max,1,7,
	//					max,4,0,max,max,
	//					2,max,-5,0,max,
	//					max,max,max,6,0};

	int matrix[6][6]={0,16,max,13,max,max,//邻接矩阵表示图
		max,0,12,max,max,max,
		max,max,0,9,max,20,
		max,4,max,0,14,max,
		max,max,7,max,0,4,
		max,max,max,max,max,0};
	int n=6;
	int **mat=new int *[n];
	for(int i=0;i<n;++i){
		mat[i]=new int [n];
		for(int j=0;j<n;++j){
			mat[i][j]=matrix[i][j];
		}
	}
	ford_fulkerson(mat,n);

	for(int i=0;i<n;++i){
		delete [] mat[i];		
	}
	delete []mat;
	return 0;
}
