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

int main()
{
	int a=899;
	int b=493;
	cout<<euclid(a,b)<<endl;
	cout<<euclid_iterator(a,b)<<endl;
	int gcd=0,x=0,y=0;
	extended_euclid(a,b,gcd,x,y);
	cout<<lcm(a,b)<<endl;
}
