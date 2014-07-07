#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string decimal_2_binary(int b)//将10进制数转换成为2进制，并保存在字符串中
{
	string bina="";
	int tmp;
	while(b>0){
		tmp=(b%2);
		bina+=tmp+'0';
		b/=2;
	}
	//reverse(bina.begin(),bina.end());
	return bina;
}

int modular_exponentiation(int a,int b,int n)//幂取模
{
	int d=1;
	string bina=decimal_2_binary(b);//将b转换为二进制
	int k=bina.size();
	for(int i=k-1;i>=0;--i){
		d=(d*d)%n;
		if('1'==bina[i]){
			d=(d*a)%n;
		}
	}
	return d;
}

int modular_exponentiation_2(int a,int b,int n)//幂取模
{
	int d=1;
	int t=a;
	string bina=decimal_2_binary(b);//将b转换为二进制
	int k=bina.size();
	for(int i=0;i<k;++i){
		if('1'==bina[i]){
			d=(d*t)%n;
		}
		t=(t*t)%n;
		cout<<d<<"\t"<<t<<endl;
	}
	return d;
}

int main()
{
	int a=7,b=560,n=561;
	modular_exponentiation(a,b,n);
	modular_exponentiation_2(a,b,n);
}
