#include <iostream>

using namespace std;

int euclid(int a,int b)//欧几里得辗转相除法
{
	if(b==0){
		return a;
	}else{
		return euclid(b,a%b);
	}	
}

int euclid_iterator(int a,int b)//欧几里得辗转相除，迭代算法
{
	int tmp;
	while(b){
		tmp=b;
		b=a % b;
		a=tmp;
	}
	return a;
}

void extended_euclid(int a,int b,int &gcd,int &x,int &y)
{
	if(b==0){
		gcd=a,x=1,y=0;
		cout<<gcd<<"\t"<<x<<"\t"<<y<<endl;
	}else{
		extended_euclid(b,a%b,gcd,x,y);
		int xx=y,yy=x-a/b*y;
		x=xx,y=yy;
		cout<<gcd<<"\t"<<x<<"\t"<<y<<endl;
	}
}

int lcm(int a,int b)//计算n个元素的最小公倍数
{
	int gcd=euclid_iterator(a,b);
	return a*b/gcd;	
}
int modular_linear_equation_solver(int a,int b ,int n)//为计算中国剩余定理，改变求模运算
{
	int gcd,x,y;
	extended_euclid(a,n,gcd,x,y);
	if(b%gcd==0){
		int x0=(x*(b/gcd))%n;
		while(x0<0){
			x0+=n;
		}
		return x0;
	}else{
		cout<<"no solutions"<<endl;
		return -1;
	}
}

int chinese_remainder_theorem(int a[],int n[],int num)//中国剩余定理
{
	int s=1;
	int tmp;
	for(int i=0;i<num;++i){//求除数之和
		s*=n[i];
	}
	int *m=new int[num];
	int *c=new int[num];
	for(int i=0;i<num;++i){
		m[i]=s/n[i];
	}
	for(int i=0;i<num;++i){		
		if(-1==(tmp=modular_linear_equation_solver(m[i],1,n[i]))){
			cout<<"no solutions"<<endl;
			return -1;
		}else{
			c[i]=m[i]*tmp;
		}
	}
	tmp=0;
	for(int i=0;i<num;++i){
		tmp+=c[i]*a[i];
	}
	tmp=tmp%s;
	delete []m;
	delete []c;
	return tmp;
}

int main()
{
	int num=3;
	int a[3]={1,2,3};
	int n[3]={9,8,7};
	cout<<chinese_remainder_theorem(a,n,num)<<endl;
}
