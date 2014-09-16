#include <iostream>
#include <vector>
using namespace std;

typedef struct node{//孩子兄弟链表法
	int val;
	node *child;
	node *sibling;
	int maxDist;
	int maxDepth;
}node,*pNode;

void create(pNode*&pn,int root,int chi)//创建树
{
	if(!pn[root]){
		pn[root]=new node;
		pn[root]->val=root+1;
		pn[root]->child=NULL;
		pn[root]->sibling=NULL;
		pn[root]->maxDist=0;
		pn[root]->maxDepth=0;
	}
	if(!pn[chi]){
		pn[chi]=new node;
		pn[chi]->val=chi+1;
		pn[chi]->child=NULL;			
		pn[chi]->sibling=NULL;
		pn[chi]->maxDist=0;
		pn[chi]->maxDepth=0;
	}
	if(!(pn[root]->child)){
		pn[root]->child=pn[chi];
	}else{
		pn[chi]->sibling=pn[root]->child;
		pn[root]->child=pn[chi];
	}
}

void longest_path(pNode &pn)//树中的最长路径
{
	pNode ptmp=pn->child;
	if(!ptmp){
		return;
	}
	while(ptmp){
		longest_path(ptmp);
		ptmp=ptmp->sibling;
	}
	ptmp=pn->child;
	int maxDepth1=0,maxDepth2=0,maxDist=0;
	while(ptmp){
		if(ptmp->maxDepth>maxDepth1){
			int tmp=maxDepth1;
			maxDepth1=ptmp->maxDepth;
			maxDepth2=tmp;
		}else{
			if(ptmp->maxDepth>maxDepth2){
				maxDepth2=ptmp->maxDepth;
			}
		}
		if(ptmp->maxDist>maxDist){
			maxDist=ptmp->maxDist;
		}
		ptmp=ptmp->sibling;
	}	
	pn->maxDepth=max(maxDepth1,maxDepth2)+1;
	pn->maxDist=max(maxDist,maxDepth1+maxDepth2+2);
}

int main()
{
	int n;
	pNode *pn;
	vector<int>vec;
	while(cin>>n){
		pn=new pNode[n];
		for(int i=0;i<n;++i){
			pn[i]=NULL;
		}
		int root,chi;
		for(int t=0;t<n-1;++t){			
			cin>>root>>chi;			
			create(pn,root-1,chi-1);
		}
		longest_path(pn[0]);
		cout<<pn[0]->maxDist<<endl;

		for(int i=0;i<n;++i){
			delete[]pn[i];
		}
		delete[]pn;
	}
	return 0;
}
