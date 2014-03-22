#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

class Link_graphic{//邻接链表
private:
	int value;
	Link_graphic *next;
	vector<int> vec_outdegree;
public:
	void set_value(int value){this->value=value;}
	int get_value(){return this->value;}
	void set_next(Link_graphic *next);
	Link_graphic *get_next();
	bool exist(int value);
	int indegree(Link_graphic *lg,int n);
	int outdegree();
	void set_vecoutdegree(int value);
	vector<int> get_vecoutdegree();
};
void Link_graphic::set_next(Link_graphic *next)
{
	Link_graphic *lg=this->next;
	this->next=next;
	if(next)
		next->next=lg;
}
Link_graphic* Link_graphic::get_next()
{
	return this->next;
}
bool Link_graphic::exist(int value)//判断元素值是否会重复
{
	Link_graphic *lgtmp=this;
	while (lgtmp){
		if(lgtmp->value==value){
			return true;
		}
		lgtmp=lgtmp->get_next();
	}
	return false;
}
int Link_graphic::indegree(Link_graphic *lg,int n)
{
	Link_graphic *lgtmp;
	int indegree=0;
	for(int i=0;i<n;++i){
		lgtmp=lg[i].get_next();
		while(lgtmp){
			if(lgtmp->value==this->value){
				++indegree;
				vec_outdegree.push_back(lg[i].get_value());
				break;
			}
			lgtmp=lgtmp->get_next();
		}		
	}
	return indegree;
}
int Link_graphic::outdegree()
{
	int degree=0;
	Link_graphic *lg=this;
	while(lg){
		++degree;
	}
	return degree;
}
vector<int> Link_graphic::get_vecoutdegree()
{
	return this->vec_outdegree;
}
int main()
{
	srand((unsigned)time(NULL));
	int n=10;
	Link_graphic *lg=new Link_graphic[n];
	Link_graphic *lgtmp;
	for(int i=0;i<n;i++){
		lg[i].set_value(i);
		lg[i].set_next(NULL);//初始置空
		int m=rand()%n;//生成随机数
		for(int j=0;j<m;++j){//构建邻接链表
			lgtmp=new Link_graphic;
			int value=rand()%n;
			if(!lg[i].exist(value)){//判断重复与否
				lgtmp->set_value(value);
				lgtmp->set_next(NULL);
				lg[i].set_next(lgtmp);
			}
		}
	}
	for(int i=0;i<n;++i){
		lgtmp=&lg[i];
		while(lgtmp){
			cout<<lgtmp->get_value()<<" ";
			lgtmp=lgtmp->get_next();
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<i<<"'s indegree is "<<lg[i].indegree(lg,n)<<" : ";
		vector<int> vec=lg[i].get_vecoutdegree();		
		for(vector<int>::iterator iter=vec.begin();iter!=vec.end();++iter){
			cout<<*iter<<" ";
		}
		cout<<endl;		
	}
	cout<<endl;
	
}
