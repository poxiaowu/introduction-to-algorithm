//source here
#include<iostream>
#include<map>
#include<string>
using namespace std;

int main()
{
	int group;
	int m,n;
	map<string,string> mapStr;
	cin>>group;
	string strsrc,strdst;
	string sentence,substring;
	int pos=0,pos2=0;
	for(int num=0;num<group;++num){
		cin>>m>>n;
		for(int i=0;i<n;++i){
			cin>>strsrc>>strdst;
			mapStr[strsrc]=strdst;
		}
		cin.ignore();
		getline (cin,sentence);
		for(int j=0;j<m-1;++j){
			pos=0,pos2=0;
			while(pos2!=sentence.length()){
				pos=sentence.find_first_not_of(" ",pos2);
				pos2=sentence.find_first_of(" ",pos);
				if(pos2==-1){
					pos2=sentence.length();
				}
				substring=sentence.substr(pos,pos2-pos);
				if(mapStr.find(substring)!=mapStr.end()){
					sentence.replace(pos,pos2-pos,mapStr[substring]);
					pos2=pos2=sentence.find_first_of(" ",pos);
					if(pos2==-1){
						pos2=sentence.length();
					}
				}
			}
		}
		cout<<"Case #"<<num+1<<": "<<sentence<<endl;
		map<string,string>().swap(mapStr);
		mapStr.clear();
	}
	return 0;
}
