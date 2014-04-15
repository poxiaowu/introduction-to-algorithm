#include <iostream>
#include <ctime>
using namespace std;

#define BTree_T 2
#define BTree_N ((BTree_T*2)-1)
//定义B树的最小度数，以及B树中关键字的最大数目

typedef struct BTNode{//B树结点
	int keyNum;//结点关键字个数
	int key[BTree_N];//B树结点关键字数组
	BTNode * children[BTree_T*2];//B树的孩子向量
	bool leaf;//结点是否是叶子结点

}BTNode,*pBTNode;

void BTree_create(pBTNode &tree)//创建结点
{
	pBTNode btnode=new BTNode;
	btnode->leaf=true;
	btnode->keyNum=0;
	tree=btnode;
	for(int i=0;i<=BTree_N;++i){
		tree->children[i]=NULL;//都指向空
	}
	for(int i=0;i<BTree_N;++i){
		tree->key[i]='\0';
	}	
}

void BTree_split_child(pBTNode &tree,int pos)//tree结点的pos子结点已满
{
	pBTNode pz=new BTNode;
	for(int i=0;i<=BTree_N;++i){
		pz->children[i]=NULL;//都指向空
	}
	for(int i=0;i<BTree_N;++i){
		pz->key[i]='\0';//初始化相关信息
	}	
	pBTNode py=tree->children[pos];
	pz->leaf=py->leaf;
	pz->keyNum=BTree_T-1;//pz存放元素的个数	
	for(int i=0;i<pz->keyNum;++i){
		pz->key[i]=py->key[BTree_T+i];
		py->key[BTree_T+i]='\0';
	}
	if(!py->leaf){//如果y结点不是叶子结点
  		for(int i=0;i<=pz->keyNum;++i){//存放子结点
			pz->children[i]=py->children[BTree_T+i];
			py->children[BTree_T+i]=NULL;
		}		
	}
	int j;
	for(j=tree->keyNum;j>pos;--j){
		tree->children[j+1]=tree->children[j];
		tree->key[j]=tree->key[j-1];
	}
	tree->children[pos+1]=pz;
	tree->key[pos]=py->key[BTree_T-1];
	py->key[BTree_T-1]='\0';
	py->keyNum=BTree_T-1;
	tree->keyNum++;
}

void BTree_insert_notfull(pBTNode &tree,int key)//将关键字key插入到结点tree
{
	int i=tree->keyNum-1;//最大的关键字的索引下标值
	if(tree->leaf){
		while(i>=0 && key<tree->key[i]){
			tree->key[i+1]=tree->key[i];
			--i;
		}
		tree->key[i+1]=key;
		tree->keyNum++;
	}else{
		while(i>=0 && key<tree->key[i]){
			--i;
		}
		i++;
		if(tree->children[i]->keyNum==BTree_N){
			BTree_split_child(tree,i);
			if(key>tree->key[i]){
				i++;
			}
		}
		BTree_insert_notfull(tree->children[i],key);
	}
}

void BTree_insert(pBTNode &tree,int key)//在B树中插入关键字key
{
	if(tree->keyNum==BTree_N){
		pBTNode btnode=new BTNode;
		for(int i=0;i<=BTree_N;++i){
			btnode->children[i]=NULL;//都指向空
		}
		for(int i=0;i<BTree_N;++i){
			btnode->key[i]='\0';//初始化相关信息
		}	
		btnode->leaf=false;
		btnode->keyNum=0;
		btnode->children[0]=tree;
		tree=btnode;
		BTree_split_child(tree,0);
		BTree_insert_notfull(tree,key);
	}else{
		BTree_insert_notfull(tree,key);
	}
}

void release_space(pBTNode &tree)
{
	if(!tree->leaf){
		for(int i=0;i<=tree->keyNum;++i){
			release_space(tree->children[i]);
			delete tree->children[i];
		}
	}
}

void print_info(pBTNode &tree)
{
	if(!tree->leaf){
		for(int i=0;i<=tree->keyNum;++i){
			print_info(tree->children[i]);
			if(i!=tree->keyNum){
				cout<<tree->key[i]<<" ";
			}
		}
	}else{
		for(int i=0;i<tree->keyNum;++i){
			cout<<tree->key[i]<<" ";
		}
	}
}

pBTNode BTree_search(pBTNode tree,int key)//B树结点搜索
{
	if(!tree){//如果树为空
		return NULL;
	}
	int i=0;
	while(i<tree->keyNum && key>tree->key[i]){
		++i;
	}
	if(i<tree->keyNum && key==tree->key[i]){
		return tree;
	}else if(tree->leaf){
		return NULL;
	}else{
		return BTree_search(tree->children[i],key);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	pBTNode tree;
	BTree_create(tree);//创建一个空的B树
	int n=20;
	int key;
	for(int i=0;i<n;++i){
		key=rand()%20;
		cout<<key<<" ";
		BTree_insert(tree,key);
	}	
	cout<<endl;
	print_info(tree);//打印排序后信息
	cout<<endl;
	int m=10;
	int valule;
	for(int i=0;i<m;++i){
		valule=rand()%20;
		if(BTree_search(tree,valule)){
			cout<<"node "<<valule<<" founded"<<endl;
		}	
	}	
	release_space(tree);//删除结点
}  
