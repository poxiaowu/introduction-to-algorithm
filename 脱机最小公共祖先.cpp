#include<iostream>
#include <limits>
#include <ctime>
#include <map>
#include <utility>
#include <vector>
using namespace std;

typedef struct node{//二叉树节点
	int value;
	node *left;
	node *right;
}node,*pnode;

typedef struct dis_set_forest_node{//不相交集合森林
	int key;
	dis_set_forest_node *parent;
	bool visited;
}dis_set_forest_node,*pDis_set_forest_node;
struct queue;

pDis_set_forest_node make_set(int key)//创建结点
{
	pDis_set_forest_node pdsf=new dis_set_forest_node;
	pdsf->key=key;
	pdsf->parent=pdsf;
	pdsf->visited=false;
	return pdsf;
}

void link(pDis_set_forest_node px,pDis_set_forest_node py)//合并2个结点
{
	if(px && py){		
		py->parent=px;
	}
}

pDis_set_forest_node& find_set(map<int,pDis_set_forest_node>ma,int key)//查找结点
{
	if(ma[key]!=ma[key]->parent){
		ma[key]->parent=find_set(ma,ma[key]->parent->key);
	}
	return ma[key]->parent;
}

void union_dsf(pDis_set_forest_node &px,pDis_set_forest_node &py)//合并
{	
	link(px,py);
}

void least_common_ancestor(map<int,pDis_set_forest_node>&ma,pnode pn,vector<pair<int,int>>vec_pairs,int *a,int n)//脱机最小公共祖先
{	
	ma[pn->value]=make_set(pn->value);	
	pnode pc=pn->left;//孩子结点
	find_set(ma,pn->value)=ma[pn->value];//更新父亲结点 
	while(pc){
		least_common_ancestor(ma,pc,vec_pairs,a,n);//对子结点递归
		union_dsf(ma[pn->value],ma[pc->value]);//合并
		pc=pc->right;
	}
	ma[pn->value]->visited=true;
	for(int i=0;i<n;++i){
		for(int j=0;j<vec_pairs.size();++j){
			if((a[i]==vec_pairs[j].first && pn->value==vec_pairs[j].second)){
				if(ma.count(a[i])){
					if (ma[a[i]]->visited){
						cout<<"The least common ancestor of "<<a[i]<<" and "<<pn->value<<" is "<<find_set(ma,a[i])->parent->key<<endl;
						vec_pairs.erase(vec_pairs.begin()+j);
					}
				}				
			}else if((a[i]==vec_pairs[j].second && pn->value==vec_pairs[j].first)){
				if(ma.count(a[i])){
					if (ma[a[i]]->visited){
						cout<<"The least common ancestor of "<<pn->value<<" and "<<a[i]<<" is "<<find_set(ma,a[i])->parent->key<<endl;
						vec_pairs.erase(vec_pairs.begin()+j);
					}
				}			
			}
		}
	}	
}

void build_binary_tree(pnode &pn,int depth,int maxDep,int *a)//创建一个二叉树
{
	static int index=0;
	if(depth<maxDep){
		//创建根节点
		pn=new node;
		pn->value=a[index++];
		pn->left=NULL;
		pn->right=NULL;
		cout<<pn->value<<"\t";

		build_binary_tree(pn->left,depth+1,maxDep,a);
		build_binary_tree(pn->right,depth+1,maxDep,a);
	}
}

void convert_2_child_sibling(pnode &pn)//将二叉树转化为孩子兄弟链表表示
{
	if(pn){
		pnode ptmp=pn->right;//结点pn的右孩子结点
		if(pn->left){
			convert_2_child_sibling(pn->left);
			pn->left->right=ptmp;
			pn->right=NULL;
		}
		convert_2_child_sibling(ptmp);
	}
}

void random(int *a,int n)//生成随机数
{
	int index;
	int tmp;
	for(int i=0;i<n;++i){
		index=rand()%((n-i))+i;
		tmp=a[index];//交换元素
		a[index]=a[i];
		a[i]=tmp;
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	int maxDep;
	while(maxDep=rand()%10,maxDep<3);
	pnode pn;
	maxDep=4;
	cout<<"创建一个二叉树"<<endl;
	int n=static_cast<int>(pow(2.0,maxDep*1.0))-1;
	int *a=new int[n];
	for(int i=0;i<n;++i){
		a[i]=i;
	}
	random(a,n);
	//a[0]=6,a[1]=0,a[2]=3,a[3]=4,a[4]=1,a[5]=2,a[6]=5;
	cout<<endl;
	build_binary_tree(pn,0,maxDep,a);//构建二叉树	
	cout<<endl;
	convert_2_child_sibling(pn);//转换为孩子兄弟结点表示

	//-------生成离线查询集合--------
	vector<pair<int,int>>vec_pairs;//存放结合对
	for(int i=0;i<n;++i){
		int rnd1=rand()%n;
		int rnd2=rand()%n;
		vec_pairs.push_back(make_pair(rnd1,rnd2));
		cout<<"query "<<rnd1<<" and "<<rnd2<<endl;
	}

	//--------脱机最小公共祖先-------
	map<int,pDis_set_forest_node>ma;
	bool *visited=new bool[n];
	least_common_ancestor(ma,pn,vec_pairs,a,n);//脱机最小公共祖先
	delete []a;
	vector<pair<int,int>>().swap(vec_pairs);
	vec_pairs.clear();
	map<int,pDis_set_forest_node>().swap(ma);
	ma.clear();
}
