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

int main()
{
	int a=99;
	int b=78;
	cout<<euclid(a,b)<<endl;
	int gcd=0,x=0,y=0;
	extended_euclid(a,b,gcd,x,y);
}
