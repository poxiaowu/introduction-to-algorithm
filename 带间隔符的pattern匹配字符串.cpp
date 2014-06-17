#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//算法导论第三版32.1-4
void string_matcher(string &strSrc,vector<string>vecStr,int index,int pos,vector<int> &vec_result)//查找所有出现的匹配模式
{
	int depth=vecStr.size();
	if(index<depth){
		string pat=vecStr[index];
		pos=strSrc.find(pat,pos);
		if(pos!=string::npos){
			pos+=pat.length();
		}
		while(pos!=string::npos){
			vec_result.push_back(pos-pat.length());//保存记录
			string_matcher(strSrc,vecStr,index+1,pos,vec_result);
			pos=strSrc.find(pat,pos);
			vec_result.pop_back();
			if(pos!=string::npos){
				pos+=pat.length();
			}
		}
	}	
	if(vecStr.size()==vec_result.size()){//输出所有符合匹配模式的结果
		for(int i=0;i<vec_result.size()-1;++i){
			cout<<vec_result[i]<<"\t";
		}
		cout<<vec_result[vec_result.size()-1]<<endl;
	}
}

void pattern_with_seperator_string_matcher(string strSrc,string pattern,string opt)//模式中带分隔符的字符串匹配算法
{	
	vector<string> vec;
	int pre=0,aft=0;
	string str;
	while(aft<=pattern.length()){//将间隔符分离出来
		pre=pattern.find_first_not_of(opt[0],aft);
		aft=pattern.find(opt,pre);
		if(string::npos==aft){
			aft=pattern.length()+1;
		}
		str=pattern.substr(pre,aft-pre);
		vec.push_back(str);
	}
	vector<int> vec_result;
	string_matcher(strSrc,vec,0,0,vec_result);//查找所有出现的匹配模式
	swap(vector<string>(),vec);
	swap(vector<int>(),vec_result);
}
	
int main()
{
	string strSrc,strDst;
	strSrc="cabccbacbacab";
	strDst="ab_ba_c";
	string opt="_";
	pattern_with_seperator_string_matcher(strSrc,strDst,opt);
	return 0;
}
