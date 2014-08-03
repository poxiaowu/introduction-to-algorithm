#include <iostream>
#include <string>
#include <queue>
using namespace std;

static const int nt=26;
typedef struct tire{
	int id;//当前结点按层遍历编号
	bool flag;//标记当前结点是否是一个单词的结束
	tire *child[nt];
	tire *par;//父亲结点编号
	int next[nt];//
	int suffix;//当前结点的后缀结点标号
	int num;//当前结点是父亲的第num个结点
}tire,*pTire;

void make_set(pTire &pt,string str,int &co)//构建tire树
{
	int index;
	int j=0,len=str.length();
	pTire ptmp=pt;
	while(j<len){
		index=str[j]-'a';
		if(ptmp->child[index]==NULL){//如果子节点为空
			ptmp->child[index]=new tire;
			for(int i=0;i<nt;++i){//将子节点指针都赋值为NULL
				ptmp->child[index]->child[i]=NULL;
			}
			++co;//每次建立新的结点时，结点总数加1
			ptmp->child[index]->par=ptmp;//设置相应父结点
			ptmp->child[index]->flag=false;
			ptmp->child[index]->num=index;//当前结点是父亲结点的第num个结点
		}		
		ptmp=ptmp->child[index];
		++j;
	}
	ptmp->flag=true;//标记该结点为一个单词的结尾
}

pTire * level_suffix(pTire &pt,int co)//tire图按层遍历,对每个结点标号,并建立相应的tire图
{
	pTire *ptarr=new pTire[co];
	ptarr[0]=pt;
	queue<pTire>qupt;
	qupt.push(pt);
	int index=0;
	pTire ptmp=NULL;
	while(!qupt.empty()){
		ptmp=qupt.front();
		for(int i=0;i<nt;++i){
			if(ptmp->child[i]){
				qupt.push(ptmp->child[i]);
				++index;
				ptmp->child[i]->id=index;
				ptarr[index]=ptmp->child[i];
			}
			ptmp->next[i]=0;//将每个结点的next数组都初始化为0
		}

		if(!ptmp->par->id){
			ptmp->suffix=0;
		}else{
			ptmp->suffix=ptarr[ptmp->par->suffix]->next[ptmp->num];
			if(ptarr[ptmp->suffix]->flag){//后缀结点是标记结点的，当前结点已应该被标记
				ptmp->flag=true;
			}
		}
		for(int i=0;i<nt;++i){
			if(!ptmp->id){
				if(ptmp->child[i]){
					ptmp->next[i]=ptmp->child[i]->id;
				}
			}else if(!ptmp->child[i]){
				ptmp->next[i]=ptarr[ptmp->suffix]->next[i];
			}else{
				ptmp->next[i]=ptmp->child[i]->id;
			}
		}
		qupt.pop();
	}
	return ptarr;
}

bool kmp_tire_graphic(pTire &pt,string &str,int co)//tire图kmp匹配算法
{
	int len=str.length();
	pTire * ptarr = level_suffix(pt,co);
	pTire ptmp=pt;
	int index=0;
	for(int i=0;i<len;++i){
		index=str[i]-'a';
		ptmp=ptarr[ptmp->next[index]];
		if(ptmp->flag){
			return true;
		}
	}
	for(int i=0;i<co;++i){
		delete ptarr[i];
	}
	delete [] ptarr;
	return false;
}

int main()
{
	pTire pt=new tire;
	pt->par=pt;
	pt->flag=false;
	pt->id=0;
	for(int i=0;i<nt;++i){//将子节点指针都赋值为NULL
		pt->child[i]=NULL;
	}
	int words_time;
	cin>>words_time;
	string str;
	int co=1;//最后建立的结点总数
	for(int i=0;i<words_time;++i){
		cin>>str;
		make_set(pt,str,co);
	}
	cin>>str;
	if(kmp_tire_graphic(pt,str,co)){
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}
	return 0;
}
