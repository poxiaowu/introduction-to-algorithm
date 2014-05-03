#include <iostream>
#include <map>
using namespace std;
//不相交集合森林
typedef struct disjoint_set_forest_node{
	int value;//结点值
	disjoint_set_forest_node *parent;//父亲结点
	int rank;//结点的秩
}disjoint_set_forest_node,*pDisjoint_set_forest_node;

pDisjoint_set_forest_node make_set(int value)
{
	pDisjoint_set_forest_node pdfn=new disjoint_set_forest_node;
	pdfn->rank=0;
	pdfn->parent=pdfn;
	pdfn->value=value;
	return pdfn;
}

pDisjoint_set_forest_node find_set(map<int,pDisjoint_set_forest_node>ma,int key)//递归版本
{
	if(ma[key]!=ma[key]->parent){
		ma[key]->parent=find_set(ma,ma[key]->parent->value);
	}
	return ma[key]->parent;
}

pDisjoint_set_forest_node find_set_iterator(map<int,pDisjoint_set_forest_node>ma,int key)//非递归版本
{
	pDisjoint_set_forest_node pdfn=ma[key];
	while(pdfn!=pdfn->parent){
		pdfn=pdfn->parent;		
	}//找根结点

	pDisjoint_set_forest_node pt=ma[key];
	pDisjoint_set_forest_node ptmp=pt;

	while(ptmp!=pdfn){
		ptmp=ptmp->parent;
		pt->parent=pdfn;
		pt=ptmp;
	}
	return pdfn;
}


void link(pDisjoint_set_forest_node px,pDisjoint_set_forest_node py)//合并2个结点
{
	if(px->rank<py->rank){
		px->parent=py;
	}else{
		py->parent=px;
		if(px->rank==py->rank){
			++px->rank;
		}
	}
}

void union_dis(int x,int y,map<int,pDisjoint_set_forest_node>ma)//合并两颗树
{
	link(find_set(ma,x),find_set(ma,y));
}

int main()
{
	int n=16;
	pDisjoint_set_forest_node *pdf=new pDisjoint_set_forest_node[n];
	map<int,pDisjoint_set_forest_node>ma;//保存值和其对应的地址之间的关系
	for(int i=0;i<n;++i){
		pdf[i]=make_set(i);
		ma[i]=pdf[i];
	}
	for(int i=0;i<n;i+=2){
		union_dis(i,i+1,ma);
	}
	for(int i=0;i<n-3;i+=4){
		union_dis(i,i+2,ma);
	}
	union_dis(0,4,ma);
	union_dis(10,12,ma);
	union_dis(0,9,ma);		
	cout<<find_set(ma,10)->value<<endl;
	cout<<find_set(ma,15)->value<<endl;
	for(int i=0;i<n;++i){
		delete ma[i];
	}
	delete [] pdf;
}
