#include <iostream>
#include <ctime>
#include <boost/timer/timer.hpp>
using namespace boost::timer;
using namespace std;

int addrARA[4]={0,0,1,1},addrACA[4]={0,0,0,0},
	addrBRA[4]={0,0,0,0},addrBCA[4]={0,1,0,1};
int addrARA2[4]={0,0,1,1},addrACA2[4]={1,1,1,1},
	addrBRA2[4]={1,1,1,1},addrBCA2[4]={0,1,0,1};//矩阵乘法对应关系
//addrARA[0]=0,addrACA[0]=0,addrBRA[0]=0,addrBCA[0]=0;
//addrARA2[0]=0,addrACA2[0]=1,addrBRA2[0]=1,addrBCA2[0]=0;
//addrARA[1]=0,addrACA[1]=0,addrBRA[1]=0,addrBCA[1]=1;
//addrARA2[1]=0,addrACA2[1]=1,addrBRA2[1]=1,addrBCA2[1]=1;
//addrARA[2]=1,addrACA[2]=0,addrBRA[2]=0,addrBCA[2]=0;
//addrARA2[2]=1,addrACA2[2]=1,addrBRA2[2]=1,addrBCA2[2]=0;
//addrARA[3]=1,addrACA[3]=0,addrBRA[3]=0,addrBCA[3]=1;
//addrARA2[3]=1,addrACA2[3]=1,addrBRA2[3]=1,addrBCA2[3]=1;

void square_matrix_multiply(int **a,int **b,int **c,int n)//naive method
{
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			c[i][j]=0;
			for(int k=0;k<n;++k){
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
}
/***********/
/* addrAr：子矩阵在大矩阵A中的row偏移  */    
/* addrAc：子矩阵在大矩阵A中的col偏移  */ 
/* addrBr：子矩阵在大矩阵B中的row偏移  */    
/* addrBc：子矩阵在大矩阵B中的col偏移  */ 
/* addrAR：在A中2x2子矩阵中的row偏移  */    
/* addrAC：在A中2x2子矩阵中的col偏移  */ 
/* addrBR：在B中2x2子矩阵中的row偏移  */    
/* addrBC：在B中2x2子矩阵中的col偏移  */ 
/***********/
int ** recursive_square_matrix_multiply(int **a,int **b,int addrAr,int addrAc,int addrBr,int addrBc,int addrAR,int addrAC,int addrBR,int addrBC,int n)//
{
	int **result=new int *[n];
	for(int p=0;p<n;++p){
		result[p]=new int [n];
	}	
	if(n==1){
		result[0][0]= a[addrAr+addrAR][addrAc+addrAC]*b[addrBr+addrBR][addrBc+addrBC];
	}else{
		int **xx=new int *[n/2];
		for(int p=0;p<n/2;++p){
			xx[p]=new int [n/2];
		}
		int **yy=new int *[n/2];
		for(int p=0;p<n/2;++p){
			yy[p]=new int [n/2];
		}
		
		for(int i=0;i<4;++i){

			bool flag=(n>=4)?1:0;
			xx=recursive_square_matrix_multiply(a,b,addrAr+addrARA[i]*flag*(n/2),addrAc+addrACA[i]*flag*(n/2),
													addrBr+addrBRA[i]*flag*(n/2),addrBc+addrBCA[i]*flag*(n/2),
													addrARA[i],
													addrACA[i],
													addrBRA[i],
													addrBCA[i],n/2);
			yy=recursive_square_matrix_multiply(a,b,addrAr+addrARA2[i]*flag*(n/2),addrAc+addrACA2[i]*flag*(n/2),
													addrBr+addrBRA2[i]*flag*(n/2),addrBc+addrBCA2[i]*flag*(n/2),
													addrARA2[i],
													addrACA2[i],
													addrBRA2[i],
													addrBCA2[i],n/2);

			for(int k=0;k<n/2;++k){
				for(int m=0;m<n/2;++m){
					result[(i/2)*(n/2)+k][(i%2)*(n/2)+m]=xx[k][m]+yy[k][m];
					//cout<<xx[k][m]+yy[k][m]<<endl;
				}
			}
		}
		delete[]xx;
		delete [] yy;
	}
	return result;
}

int main()
{
	srand(time(NULL));
	int n=8;
	int **a=new int *[n];
	int **b=new int *[n];
	int **c=new int *[n];
	for(int i=0;i<n;++i){
		a[i]=new int [n];
		b[i]=new int [n];
		c[i]=new int [n];
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			a[i][j]=rand()%41-20;
			b[i][j]=rand()%41-20;
		}
	}

	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;

	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<b[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	cpu_timer t1;
	t1.start();
	square_matrix_multiply(a,b,c,n);//naive method
	t1.stop();
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<c[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<t1.format();

	cpu_timer t2;
	t2.start();
	c=recursive_square_matrix_multiply(a,b,0,0,0,0,0,0,0,0,n);//recursvie naive method
	t2.stop();
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<c[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<t2.format();
	for(int i=0;i<n;++i){
		delete[]a[i];
		delete[]b[i];
		delete[]c[i];
	}
	delete[]a;
	delete[]b;
	delete[]c;
}
