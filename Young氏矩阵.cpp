#include<iostream>
#include <limits>
#include <ctime>
using namespace std;

void young_tableau(int **a,int i,int j,int m,int n)//维护杨氏矩阵
{
	int min_row=i,min_col=j;
	if(i+1<m && j<n &&(a[i][j]>a[i+1][j])){//比较当前元素与下边元素值的大小
		min_row=i+1;
	}
	if(i<m && j+1<n && a[i][j+1]<a[min_row][min_col]){//比较当前元素与右边元素值的大小
		min_row=i;
		min_col=j+1;
	}
	if((min_row!=i)||(min_col!=j)){
		int tmp=a[i][j];
		a[i][j]=a[min_row][min_col];
		a[min_row][min_col]=tmp;
		young_tableau(a,min_row,min_col,m,n);
	}
}

int extrace_young_tableau_min(int **a,int m,int n)//获取杨氏矩阵最小值
{
	int min=a[0][0];
	a[0][0]=a[m-1][n-1];
	a[m-1][n-1]=numeric_limits<int>::max();
	young_tableau(a,0,0,m,n);
	return min;	
}

void delete_young_tableau_elem(int **a,int i,int j,int m,int n)//删除杨氏矩阵的某一个元素
{
	if(i<0 || i>=m || j<0||j>=n)
		cout<<"out of young tableau";
	a[i][j]=numeric_limits<int>::max();
	young_tableau(a,i,j,m,n);
}


void find_young_tableau_elem(int **a,int m,int n,int &i,int &j,int key)//查找某个元素
{
	i=0,j=n-1;
	while (i<m && j>=0)
	{
		if(key==a[i][j]){
			return;
		}else if(key<a[i][j]){
			--j;
		}else{
			i++;
		}
	}
	cout<<"could not found the elem."<<endl;

}

void insert_young_tableau(int **a,int m,int n,int key)//在杨氏矩阵中插入值
{
	if(a[m-1][n-1]==numeric_limits<int>::max()){
		a[m-1][n-1]=key;
		int i=m-1,j=n-1;
		int max_row=i,max_col=j;
		int tmp;
		/*while ((i>0 && (a[i-1][j]>key)) || (j>0&&(a[i][j-1]>key))){
		if(i>0 && (a[i][j]<a[i-1][j])){
		max_row=i-1;
		}
		if(j>0 && a[max_row][max_col]<a[i][j-1]){
		max_row=i;
		max_col=j-1;
		}
		tmp=a[i][j];
		a[i][j]=a[max_row][max_col];
		a[max_row][max_col]=tmp;
		i=max_row,j=max_col;
		}*/

		while (true){
			if(i>0 && (a[i][j]<a[i-1][j])){
				max_row=i-1;
			}
			if(j>0 && a[max_row][max_col]<a[i][j-1]){
				max_row=i;
				max_col=j-1;
			}
			if(max_row==i && max_col==j)
				break;
			tmp=a[i][j];
			a[i][j]=a[max_row][max_col];
			a[max_row][max_col]=tmp;
			i=max_row,j=max_col;
		}
	}
}

int main()
{
	srand(time(NULL));
	int ma=numeric_limits<int>::max();//矩阵中的最大值
	int *p[4];
	int a[4][4]={2,3,4,5,//算法导论，杨氏矩阵
				8,9,12,14,
				16,ma,ma,ma,
				ma,ma,ma,ma};

	for(int i=0;i<4;++i){//双重指针
		p[i]=(&a[i][0]);
	}

	for(int i=0;i<4;++i){//输出原始值
		for(int j=0;j<4;++j){
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;

	
	int count;//随机生成值

	for(int i=0;i<7;++i){
		count=rand()%101-50;
		//count=-17;
		insert_young_tableau(p,4,4,count);
		for(int i=0;i<4;++i){//输出插入操作后的值
			for(int j=0;j<4;++j){
				cout<<a[i][j]<<"\t";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
	int i,j;
	while((i=rand()%4),(i<0 || i>=4));
	while((j=rand()%4),(j<0 || j>=4));
	delete_young_tableau_elem(p,i,j,4,4);
	for(int i=0;i<4;++i){//输出删除操作后的值
		for(int j=0;j<4;++j){
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;

	int rei,rej;
	find_young_tableau_elem(p,4,4,rei,rej,20/*p[2][2]*/);
	cout<<"( "<<rei<<","<<rej<<")"<<endl;
}
