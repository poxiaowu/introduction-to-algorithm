#include <iostream>
#include <ctime>
using namespace std;

#define BTree_T 2
#define BTree_N ((2*BTree_T)-1)
//BTree_T 表示B树的度,BTree_N表示B树的最大关键字个数
typedef struct BTree{
	int keyNum;//保存关键字的个数
	int key[BTree_N];//存储关键字
	BTree *children[BTree_N+1];//存储孩子结点的指针
	bool leaf;//是否是叶子结点标志位
}BTree,*pBTree;

void BTree_create(pBTree &tree)//B树的创建
{
	tree=new BTree;
	tree->keyNum=0;//关键字的总个数
	tree->leaf=true;//是否是叶子结点
	for(int i=0;i<BTree_N;++i){
		tree->key[i]=NULL;
	}
	for(int i=0;i<BTree_N+1;++i){
		tree->children[i]=NULL;
	}
}

void BTree_split_up(pBTree &px,int pos)//结点满，分割
{
	pBTree py=px->children[pos];
	pBTree pz=new BTree;
	pz->leaf=py->leaf;
	for(int i=0;i<BTree_N;++i){//初始化pz信息
		pz->key[i]=NULL;
	}
	for(int i=0;i<BTree_N+1;++i){
		pz->children[i]=NULL;
	}

	for(int i=0;i<BTree_T-1;++i){//更新Z结点的关键字指针域
		pz->key[i]=py->key[BTree_T+i];
		py->key[BTree_T+i]=NULL;
	}	
	if(!pz->leaf){//如果pz不是叶子结点,则复制子结点的相关信息
		for(int i=0;i<BTree_T;++i){//更新z结点子结点指针域
			pz->children[i]=py->children[BTree_T+i];
			py->children[BTree_T+i]=NULL;
		}	
	}	
	for(int i=px->keyNum;i>pos;--i){
		px->key[i]=px->key[i-1];
	}
	px->key[pos]=py->key[BTree_T-1];
	for(int i=px->keyNum+1;i>pos+1;--i){
		px->children[i]=px->children[i-1];
	}
	px->children[pos+1]=pz;
	py->keyNum=BTree_T-1;//改变py,pz和px的关键字个数
	pz->keyNum=BTree_T-1;
	px->keyNum++;
}

void BTree_not_full(pBTree &px,int key)//插入key值
{
	int num=px->keyNum-1;//索引下标值
	if(px->leaf){
		while(num>=0 && key<px->key[num]){
			px->key[num+1]=px->key[num];
			--num;	
		}
		px->key[++num]=key;
		++px->keyNum;
	}else{
		while(num>=0 && key<px->key[num]){
			--num;	
		}
		if(px->children[++num]->keyNum==BTree_N){
			BTree_split_up(px,num);
			if(key>px->key[num]){
				++num;
			}
		}
		BTree_not_full(px->children[num],key);
	}
}

void BTree_insert(pBTree &tree,int key)//插入关键字
{
	if(tree->keyNum==BTree_N){//如果根结点已满,则需要分裂
		pBTree px=new BTree;	
		px->leaf=false;
		for(int i=0;i<BTree_N;++i){//初始化关键字信息
			px->key[i]=NULL;
		}
		for(int i=0;i<BTree_N+1;++i){//初始化孩子结点信息
			px->children[i]=NULL;
		}
		px->keyNum=0;
		px->children[0]=tree;
		tree=px;
		BTree_split_up(tree,0);	
		BTree_not_full(tree,key);
	}else{
		BTree_not_full(tree,key);
	}
}

void release_space(pBTree &tree)
{
	if(!tree->leaf){
		for(int i=0;i<=tree->keyNum;++i){
			release_space(tree->children[i]);
			delete tree->children[i];
		}
	}
}

void print_info(pBTree &tree)
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

pBTree BTree_search(pBTree tree,int key)//B树结点搜索
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

void BTree_merge_child(pBTree &px,int pos,pBTree &py,pBTree &pz)//当父节点的个数为1个，且2个子节点的个数都为BTree_N，合并父节点和两个子节点
{
	py->keyNum=BTree_N;//合并后节点都放到py下
	for(int j=0;j<BTree_T-1;++j){
		py->key[BTree_T+j]=pz->key[j];
		pz->key[j]=NULL;
	}
	py->key[BTree_T-1]=px->key[pos];

	if(!pz->leaf){//如果不是叶结点，还需要复制其相应的子结点
		for(int j=0;j<BTree_T;++j){
			py->children[BTree_T+j]=pz->children[j];
			pz->children[j]=NULL;
		}
	}
	pz->keyNum=0;
	delete pz;//删除pz结点
	for(int j=pos+1;j<px->keyNum;++j){//删除pos位置的关键字之后需要将后面的关键字依次往前移一位
		px->key[j-1]=px->key[j];
	}
	px->key[px->keyNum-1]=NULL;
	for(int j=pos+1;j<px->keyNum;++j){
		px->children[j]=px->children[j+1];
	}
	px->children[px->keyNum]=NULL;
	px->keyNum=px->keyNum-1;	
}

int BTree_search_predecessor(pBTree  px,int pos)//查找当前结点的直接前驱结点,pos为当前结点的下标索引
{
	if(!px->leaf){//px不是叶子结点
		px=px->children[pos];
		while(!px->leaf){
			px=px->children[px->keyNum];
		}
		return px->key[px->keyNum-1];
	}
	return px->key[pos-1];
}

int BTree_search_successor(pBTree px,int pos)//查找当前结点的后继结点，pos为当前结点的下标索引
{
	if(!px->leaf){
		px=px->children[pos+1];
		while(!px->leaf){
			px=px->children[0];
		}
		return px->key[0];
	}
	return px->key[pos+1];
}

void BTree_shift_to_right(pBTree &px,int pos,pBTree &py,pBTree &pz)//如果右边的结点pz有BTree_T-1个关键字，左边结点py个数大于等于BTree_T，则将左边py的结点通过父亲结点px转移到右结点pz
{
	pz->keyNum=pz->keyNum+1;//pz的关键字个数加1
	for(int i=pz->keyNum;i>0;--i){
		pz->key[i]=pz->key[i-1];
	}
	pz->key[0]=px->key[pos];
	if(!pz->leaf){
		for(int i=pz->keyNum+1;i>0;--i){
			pz->children[i]=pz->children[i-1];
		}
		pz->children[0]=py->children[py->keyNum];//因为py少一个元素，故将py中的最后一个子结点的指针赋值给pz->children[0]
		py->children[py->keyNum]=NULL;
	}
	px->key[pos]=py->key[py->keyNum-1];
	py->key[py->keyNum-1]=NULL;
	--py->keyNum;
}

void BTree_shift_to_left(pBTree &px,int pos,pBTree &py,pBTree &pz)//如果右边结点py大于等于BTree_T个关键字，左边的结点pz只要BTree_T-1个关键字，则将右边的pz的关键字通过父亲结点px转移到左结点py
{
	py->keyNum=py->keyNum+1;//py结点个数加1
	py->key[py->keyNum-1]=px->key[pos];
	px->key[pos]=pz->key[0];
	for(int i=0;i<pz->keyNum-1;++i){
		pz->key[i]=pz->key[i+1];
	}
	pz->key[pz->keyNum-1]=NULL;
	if(!pz->leaf){
		py->children[py->keyNum]=pz->children[0];
		for(int i=0;i<pz->keyNum;++i){
			pz->children[i]=pz->children[i+1];
		}
		pz->children[pz->keyNum]=NULL;
	}
	--pz->keyNum;
}

void BTree_delete_full(pBTree &px,int key)//满足条件的删除
{
	int index=0;
	if(px->leaf){
		while(index<px->keyNum && key>px->key[index]){
			++index;
		}
		if(index<px->keyNum && key==px->key[index]){//case 1
			while(index<px->keyNum-1){
				px->key[index]=px->key[index+1];
				++index;
			}
			px->key[px->keyNum-1]=NULL;//最后一个设置为0
			--px->keyNum;
		}else{
			cout<<"don't exist the key."<<endl;
		}
	}else{
		while(index<px->keyNum && key>px->key[index]){
			++index;
		}
		if(index<px->keyNum && key==px->key[index]){//case 2
			int k;
			if(px->children[index]->keyNum>=BTree_T){//case 2a
				k=BTree_search_predecessor(px,index);//寻找前驱
				BTree_delete_full(px->children[index],k);//删除前驱k
				px->key[index]=k;
			}else if(px->children[index+1]->keyNum>=BTree_T){//case 2b
				k=BTree_search_successor(px,index);
				BTree_delete_full(px->children[index+1],k);
				px->key[index]=k;
			}else{//case 2c
				pBTree py=px->children[index];
				pBTree pz=px->children[index+1];
				BTree_merge_child(px,index,py,pz);//合并左右结点
				BTree_delete_full(py,key);
			}
		}else{//case 3
			if(px->children[index]->keyNum==BTree_T-1){
				pBTree py;
				if(index<px->keyNum && px->children[index+1]->keyNum>=BTree_T){//case 3a
					BTree_shift_to_left(px,index,px->children[index],px->children[index+1]);//将右边的结点通过父节点传到左边结点
					py=px->children[index];
				}else if(index>=1&& px->children[index-1]->keyNum >= BTree_T){//case 3a
					BTree_shift_to_right(px,index-1,px->children[index-1],px->children[index]);
					py=px->children[index];
				}else if(index>0){
					BTree_merge_child(px,index-1,px->children[index-1],px->children[index]);//case 3b
					py=px->children[index-1];
				}else{
					BTree_merge_child(px,index,px->children[index],px->children[index+1]);//case 3b
					py=px->children[index];
				}
				BTree_delete_full(py,key);
			}else{
				BTree_delete_full(px->children[index],key);
			}
		}
	}
}

void BTree_delete(pBTree &px,int key)//删除结点
{
	if(px->keyNum==1){
		pBTree py,pz;
		py=px->children[0];
		pz=px->children[1];
		if(py&&pz&&py->keyNum==BTree_T-1 && pz->keyNum==BTree_T-1){
			BTree_merge_child(px,0,py,pz);
			delete px;
			px=py;
		}
		BTree_delete_full(px,key);
	}else{
		BTree_delete_full(px,key);
	}
}


int main()
{
	srand((unsigned)time(NULL));
	pBTree tree;
	BTree_create(tree);//创建一个空的B树
	int n=50;
	int key;
	//int a[10]={2,19,4,18,4,14,10,7,18,19};
	for(int i=0;i<n;++i){
		key=rand()%20;
		//key=a[i];
		cout<<key<<" ";
		BTree_insert(tree,key);
	}	
	cout<<endl;
	print_info(tree);//打印排序后信息
	cout<<endl;
	//int m=10;
	int valule;	
	//int b[5]={4,14,7,2,10};
	for(int i=0;i<n;++i){
		valule=rand()%20;
		//valule=b[i];
		if(BTree_search(tree,valule)){
			cout<<"node "<<valule<<" founded.";
			BTree_delete(tree,valule);
			cout<<" And delete the node"<<endl;
		}	
	}	
	cout<<"after delete the nodes : "<<endl;
	print_info(tree);//打印删除节点后信息
	release_space(tree);//删除结点	
}  
