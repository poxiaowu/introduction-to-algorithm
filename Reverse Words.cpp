#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
	vector<string> vec;
	string strline;
	string str;
	int n;
	ifstream fin("B-large-practice.in");
	ofstream fout("B-large-practice.out",ios_base::app);
	fin>>n;
	for(int i=0;i<n;++i){
		if(!i){
			fin.ignore();
		}
		getline(fin,strline);
		int pos=0,pos2;
		while(pos!=string::npos){
			pos2=strline.find_first_of(" ",pos);
			str=strline.substr(pos,pos2-pos);
			pos=pos2+1;
			vec.push_back(str);
			if(pos2==string::npos){
				fout<<"Case #"<<i+1<<": ";
				for(int j=vec.size()-1;j>0;--j){
					fout<<vec[j]<<" ";
				}
				fout<<vec[0]<<endl;
				swap(vector<string>(),vec);
				vec.clear();
				break;
			}
		}		
	}
	return 0;
}
