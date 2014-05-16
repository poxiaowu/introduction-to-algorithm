#include <iostream>
#include <limits>
using namespace std;

void prim(int **matrix,int **edge_weight,int index,int *father,int n)//二维矩阵表示的prim算法
{
	int *weight=new int[n];
	for(int i=0;i<n;++i){
		weight[i]=edge_weight[index][i];
		father[i]=index;//父亲结点
	}
	weight[index]=0;
	int pos;
	for(int i=0;i<n-1;++i){
		int smallest=numeric_limits<int>::max();
		for(int j=0;j<n;++j){
			if(weight[j] && weight[j]<smallest){
				pos=j;
				smallest=weight[j];
			}			
		}
		weight[pos]=0;//将权重值设置为0，下次将以该结点作为初始结点
		for(int i=0;i<n;++i){//更新weight数组的值
			if(i!=pos && edge_weight[pos][i]<weight[i]){
				weight[i]=edge_weight[pos][i];
				father[i]=pos;//设置父亲结点
			}
		}
	}
	delete [] weight;
}

int main()
{
	int n=9;
	int **matrix=new int *[n];//存放结点之间的链接关系
	int **edge_weight=new int*[n];
	for(int i=0;i<n;++i){
		matrix[i]=new int [n];
		edge_weight[i]=new int [n];
		for(int j=0;j<n;++j){
			matrix[i][j]=0;
			edge_weight[i][j]=numeric_limits<int>::max();
		}
	}
	char *data=new char[n];//存放数据值
	for(int i=0;i<n;++i){
		data[i]='a'+i;
	}
	matrix[0][1]=1,matrix[0][7]=1,
	matrix[1][7]=1,matrix[1][2]=1,
	matrix[2][8]=1,matrix[7][8]=1,
	matrix[2][5]=1,matrix[6][7]=1,
	matrix[6][8]=1,matrix[2][3]=1,
	matrix[3][4]=1,matrix[3][5]=1,
	matrix[4][5]=1,matrix[5][6]=1;

	edge_weight[0][1]=4,edge_weight[0][7]=8,
	edge_weight[1][7]=11,edge_weight[1][2]=8,
	edge_weight[2][8]=2,edge_weight[7][8]=7,
	edge_weight[2][5]=4,edge_weight[6][7]=1,
	edge_weight[6][8]=6,edge_weight[2][3]=7,
	edge_weight[3][4]=9,edge_weight[3][5]=14,
	edge_weight[4][5]=10,edge_weight[5][6]=2;

	for(int i=0;i<n;++i){//创建无向图
		for(int j=0;j<n;++j){
			if(matrix[i][j]){
				matrix[j][i]=1;
				edge_weight[j][i]=edge_weight[i][j];
			}
		}
	}

	int *father=new int[n];//存放父亲结点的索引
	for(int i=0;i<n;++i){
		father[i]=i;
	}
	prim(matrix,edge_weight,0,father,n);//0表示最小生成树的开始结点

	for(int i=0;i<n;++i){
		if(father[i]!=i){
			cout<<data[i]<<"\t"<<data[father[i]]<<"\t"<<edge_weight[i][father[i]]<<endl;
		}
	}
	
	for(int i=0;i<n;++i){
		delete[]matrix[i];
		delete[]edge_weight[i];
	}
	delete []matrix;
	delete []
	delete []data;
	delete [] father;
}
