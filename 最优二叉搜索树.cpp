#include <iostream>
#include <ctime>
#include<algorithm>
#include <vector>
#include <limits>
#include <boost/timer/timer.hpp>
using namespace std;
using namespace boost::timer;
int compare(const void *a,const void *b)//qsort比较函数
{
	if ( *(double*)a <  *(double*)b ) return -1;
	if ( *(double*)a == *(double*)b ) return 0;
	if ( *(double*)a >  *(double*)b ) return 1;		
	return -2;
}
void rnd(double* drnd,int n)//生成指定数目的（0,1]之间随机数
{
	double d;
	int tmp;
	int count=0;
	srand((unsigned)time(NULL));
	vector<double> vec;
	while(true){	//生成大量的随机数，直到最大值为1
		d=rand()/(RAND_MAX*1.0);
		tmp=static_cast<int>((d*100+0.5));//保留2位小数取整
		d=tmp/100.0;//变成浮点数
		vec.push_back(d);
		//cout<<d<<endl;
		count++;
		if(d==1.0){
			if(count>=n)
				break;
			else
				vec.pop_back();
		}
	}
	int size=vec.size();//容器的大小
	for(int i=0;i<n;++i){
		drnd[i]=vec[size-i-1];
	}
	/*for(int i=0;i<n;++i){
		cout<<drnd[i]<<" ";
	}
	cout<<endl;*/
	qsort(drnd,n,sizeof(double),compare);//调用系统快速排序算法
	for(int i=n-1;i>0;--i){
		drnd[i]=drnd[i]-drnd[i-1];
	}
	/*for(int i=n-1;i>=0;--i){
		cout<<drnd[i]<<"\t";
	}
	cout<<endl;*/

	vector<double>().swap(vec);//删除内容并回收空间
	//vec.clear();
}

void optimal_binary_search_tree(double *p,double *q,double ** e,double **w,int **r,int n)//最优二叉搜索树
{
	for(int i=1;i<n+2;i++){
		e[i][i-1]=q[i-1];
		w[i][i-1]=q[i-1];
	}
	int j=0;
	double c;
	for(int l=1;l<n+1;++l){//处理的结点数
		for(int i=1;i<n-l+2;++i){
			j=i+l-1;
			e[i][j]=numeric_limits<double>::max();
			w[i][j]=w[i][j-1]+p[j]+q[j];
   			for(int k=i;k<j+1;++k){
				c=e[i][k-1]+e[k+1][j]+w[i][j];
				if(c<e[i][j]){
					e[i][j]=c;
					r[i-1][j-1]=k;
				}
			}
		}
	}
}

void construct_optimal_BST(int **root,int low,int high)//重建最优二叉树
{
	if(low<root[low][high]-1/*&&root[low][root[low][high]-2]!=root[low][high]*/){//重构左子树
		cout<<"k"<<root[low][root[low][high]-2]<<"为"<<"k"<<root[low][high]<<"的左孩子"<<endl;
		construct_optimal_BST(root,low,root[low][high]-2);
	}else{
		cout<<"d"<<root[low][high]-1<<"为"<<"k"<<root[low][high]<<"的左孩子"<<endl;
	}
	if(root[low][high]<=high){//重构右子树
		cout<<"k"<<root[root[low][high]][high]<<"为"<<"k"<<root[low][high]<<"的右孩子"<<endl;
		construct_optimal_BST(root,root[low][high],high);	
	}else{
		cout<<"d"<<root[low][high]<<"为"<<"k"<<root[low][high]<<"的右孩子"<<endl;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=21;
	double *drnd=new double[n];
	rnd(drnd,n);
	for(int i=0;i<n;++i){
		cout<<drnd[i]<<"\t";
	}
	cout<<endl;
	int np=(n-1)/2;
	int nq=np+1;
	double *p=new double[np+1];
	//p[0]=0,p[1]=0.15,p[2]=0.10,p[3]=0.05,p[4]=0.10,p[5]=0.20;
	p[0]=0;
	for(int i=1;i<np+1;++i){
		p[i]=drnd[i];
		cout<<p[i]<<"\t";
	}
	cout<<endl;
	double *q=new double[nq];
	//q[0]=0.05,q[1]=0.10,q[2]=0.05,q[3]=0.05,q[4]=0.05,q[5]=0.10;
	for(int i=0;i<nq;++i){
		q[i]=drnd[np+i];
		cout<<q[i]<<"\t";
	}
	cout<<endl;
	double **e=new double*[nq+1];
	for (int i=0;i<nq+1;++i){
		e[i]=new double [nq];
	}
	double **w=new double *[nq+1];
	for(int i=0;i<nq+1;++i){
		w[i]=new double [nq];
	}
	int **r=new int *[np];
	for(int i=0;i<np;++i){
		r[i]=new int [np];
	}
	optimal_binary_search_tree(p,q,e,w,r,np);

	for(int i=0;i<nq+1;++i){
		for(int j=0;j<nq;++j){
			cout<<e[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<nq+1;++i){
		for(int j=0;j<nq;++j){
			cout<<w[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<np;++i){
		for(int j=0;j<np;++j){
			cout<<r[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

	cout<<r[0][np-1]<<"为根"<<endl;
	construct_optimal_BST(r,0,np-1);

	delete [] drnd;
	delete [] e;
	delete [] w;
	delete [] r;
	delete []p;
	delete []q;
}   
