//source here
#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath>
#include<limits>
using namespace std;

int main()
{
	int n;
	string substring,op;
	int pos=0,pos2=0;
	int num1,num2;
	int index=0;
	double max=numeric_limits<double>::max();
	cin>>n;
	double *result=new double[n];
	string *expression=new string[n];
	cin.ignore();
	for(int i=0;i<n;++i){		
		getline(cin,expression[i]);
		//cout<<expression[i]<<endl;
	}
	for(int i=0;i<n;++i){		
		pos=0,pos2=0;		
		pos=expression[i].find_first_not_of(" ",pos2);
		pos2=expression[i].find_first_of(" ",pos);
		substring=expression[i].substr(pos,pos2-pos);
		num1=atoi(substring.c_str());

		pos=expression[i].find_first_not_of(" ",pos2);
		pos2=expression[i].find_first_of(" ",pos);
		op=expression[i].substr(pos,pos2-pos);

		pos=expression[i].find_first_not_of(" ",pos2);
		substring=expression[i].substr(pos,expression[i].length()-pos);
		num2=atoi(substring.c_str());

		if(op=="+"){
			result[i]=num1+num2;
		}else if(op=="-"){
			result[i]=num1-num2;
		}else if(op=="*"){
			result[i]=num1*num2;
		}else{
			result[i]=1.0*num1/num2;
		}
		result[i]=fabs(9.0-result[i]);	
	}

	for(int i=0;i<n;++i){
		if(result[i]<max){
			max=result[i];
			index=i;
		}
	}
	cout<<index+1<<endl;
	delete [] result;
	return 0;
}
