#include <iostream>
#include <limits>
#include <ctime>
using namespace std;

typedef struct point{
	int x,y;
}point,*ppoint;
void quick_sort_partition(ppoint *pp,int low,int high)//快速排序
{
	while (low<high){	
		ppoint pKey=pp[high];//pivot
		int index=low-1;
		ppoint ptmp;
		for(int i=low;i<high;++i){
			if(pp[i]->x<pKey->x){
				index++;
				ptmp=pp[i];
				pp[i]=pp[index];
				pp[index]=ptmp;
			}
		}
		ptmp=pp[index+1];
		pp[index+1]=pKey;
		pp[high]=ptmp;

		quick_sort_partition(pp,low,index);
		low=index+2;
	}
}
double euclidean_distance(ppoint p1,ppoint p2)//计算欧式距离
{
	return (sqrtf((p1->x-p2->x)*(p1->x-p2->x)*1.0+(p1->y-p2->y)*(p1->y-p2->y)*1.0));
}

void euclidean_TSP(ppoint *pp,double **b,int **r,int n)//双调欧几里得旅行商
{
	double q;
	b[0][1]=euclidean_distance(pp[0],pp[1]);//保存最初的欧式距离
	//r[0][1]=0;
	for(int j=2;j<n;++j){
		for(int i=0;i<j-1;++i){
			b[i][j]=b[i][j-1]+euclidean_distance(pp[j-1],pp[j]);
			r[i][j]=j-1;
		}
		b[j-1][j]=numeric_limits<int>::max();
		for(int k=0;k<j-1;++k){
			q=b[k][j-1]+euclidean_distance(pp[k],pp[j]);
			if(q<b[j-1][j]){
				b[j-1][j]=q;
				r[j-1][j]=k;
			}
		}
	}
	b[n-1][n-1]=b[n-2][n-1]+euclidean_distance(pp[n-2],pp[n-1]);
}
void print_path(ppoint *pp,int **r,int i,int j)//递归遍历
{
	int k;
	if(i<j){
		k=r[i][j];
		if(k!=i){
			cout<<"["<<pp[k]->x<<","<<pp[k]->y<<"]"<<" ";
		}
		if(k>0){
			print_path(pp,r,i,k);
		}
	}else{
		k=r[j][i];
		if(k>0){
			print_path(pp,r,k,j);
			cout<<"["<<pp[k]->x<<","<<pp[k]->y<<"]"<<" ";
		}
	}
}
void print_tour(ppoint *pp,int **r,int n)//打印旅行商问题的路径
{
	cout<<"["<<pp[n-1]->x<<","<<pp[n-1]->y<<"]"<<" ";
	cout<<"["<<pp[n-2]->x<<","<<pp[n-2]->y<<"]"<<" ";
	int k=r[n-2][n-1];
	print_path(pp,r,k,n-2);
	cout<<"["<<pp[k]->x<<","<<pp[k]->y<<"]"<<" ";
}

int main()
{
	srand((unsigned)time(NULL));
	int n=20;

	ppoint *pp=new ppoint[n];//随机生成n个点

	for(int i=0;i<n;++i){
		pp[i]=new point;
		pp[i]->x=rand()%(n*2);
		pp[i]->y=rand()%(n*2);
		cout<<"["<<pp[i]->x<<","<<pp[i]->y<<"]\t";
	}
	/*pp[0]->x=0,pp[0]->y=6;
	pp[1]->x=1,pp[1]->y=0;
	pp[2]->x=2,pp[2]->y=3;
	pp[3]->x=5,pp[3]->y=4;
	pp[4]->x=6,pp[4]->y=1;
	pp[5]->x=7,pp[5]->y=5;
	pp[6]->x=8,pp[6]->y=2;*/

	cout<<endl;
	quick_sort_partition(pp,0,n-1);//根据x值进行快速排序
	for(int i=0;i<n;++i){
		cout<<"["<<pp[i]->x<<","<<pp[i]->y<<"]\t";
	}
	cout<<endl;
	double **b=new double  *[n];
	for(int i=0;i<n;++i){
		b[i]=new double [n];
	}
	int **r=new int *[n];
	for(int i=0;i<n;++i){
		r[i]=new int [n];
	}
	for(int i=0;i<n;++i){//初始化值
		for(int j=0;j<n;++j){
			b[i][j]=-1;
		}
	}
	for(int i=0;i<n;++i){//初始化值
		for(int j=0;j<n;++j){
			r[i][j]=-1;
		}
	}

	euclidean_TSP(pp,b,r,n);

	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<r[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	print_tour(pp,r,n);
	cout<<endl;
	for(int i=0;i<n;++i){
		delete[]r[i];
		delete[]b[i];
	}
	delete [] r;
	delete [] b;
	delete [] pp;
}
