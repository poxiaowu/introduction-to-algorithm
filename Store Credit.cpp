#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

typedef struct sc{
	int index;
	int value;
}sc,*pSc;

bool compare(sc a,sc b)
{
	return a.value<b.value;
}

void sum2credit(pSc &ps,int credit,int ca,int itnum)
{
	int low=0,high=itnum-1;
	while(low!=high){
		if(ps[low].value+ps[high].value>credit){
			--high;
		}else if(ps[low].value+ps[high].value<credit){
			++low;
		}else{
			int ind1=ps[low].index,ind2=ps[high].index;
			if(ind1>ind2){
				int tmp=ind1;ind1=ind2;	ind2=tmp;
			}
			ofstream fout("A-large-practice.out",ios_base::app);
			fout<<"Case #"<<ca<<": "<<ind1<<" "<<ind2<<endl;
			break;
		}
	}
}

int main()
{
	int n;
	int credit;
	int itnum;
	pSc item;
	ifstream fin("A-large-practice.in");
	fin>>n;
	for(int t=0;t<n;++t){
		fin>>credit;
		fin>>itnum;
		item=new sc[itnum];
		for(int i=0;i<itnum;++i){
			item[i].index=i+1;
			fin>>item[i].value;
		}
		sort(item,item+itnum,compare);
		sum2credit(item,credit,t+1,itnum);
		delete [] item;
	}
}
