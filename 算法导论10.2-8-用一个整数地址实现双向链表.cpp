#include<iostream>
#include <limits>
#include <ctime>
using namespace std;

typedef struct dlist{//双向链表
	int value;//存储值
	unsigned int np;//存储地址值
}dlist, *pdlist;

void insert(pdlist &d,pdlist cur)//双链表插入元素
{
	d->np^=(unsigned int)(&(*cur));
	d=cur;
}
//双向链表，顺序显示
void display_in_order(dlist &dl)//传递引用
{
	if(dl.np==0){
		cout<<"no elements display."<<endl;
		return;
	}
	pdlist pd=(pdlist)(dl.np);//利用头结点 获取 首结点指针
	unsigned int prev=(unsigned int)(&dl);//上一个节点的地址
	unsigned int cur;//临时存放当前结点的地址
	while (pd->np != prev){
		cur=(unsigned int) pd;//保存当前结点的指针
		//cout<<endl<<prev<<"\t"<<cur<<endl;
		cout<<pd->value<<"\t";
		pd=(pdlist)(pd->np ^ prev);//下一个节点的指针
		prev=cur;
	}
	cout<<pd->value;
	cout<<endl;
}

void display_inverse(pdlist &pd)//双向链表，逆序显示
{
	if(pd->np==0){
		cout<<"no elements display."<<endl;
		return;
	}
	unsigned int addrnext=0;//pd后一个节点初始值为0
	unsigned int addrpd;//pd节点的地址值
	pdlist pp;//临时存放pd前一个节点的指针
	cout<<pd->value<<"\t";
	while((pp=(pdlist)(pd->np ^addrnext)), pp->np!=(unsigned int)pd){//头结点的np里存放着首结点的地址值，故相等时，即结束
		addrpd=(unsigned int)pd;//存放当前元素的地址
		pd=(pdlist)(pd->np ^addrnext);
		cout<<pd->value<<"\t";
		addrnext=addrpd;//临时存放后一元素的地址值
	}
	cout<<endl;
}


void del(dlist &dl,int elem)//删除元素
{
	//双向链表，顺序显示
	pdlist pd=(pdlist)(dl.np);//利用头结点 获取 首结点指针
	unsigned int prev=(unsigned int)(&dl);//上一个节点的地址
	unsigned int cur;//临时存放当前结点的指针
	int tmp,tmp2,tmp3;
	while (pd->np != prev){
		cur=(unsigned int) pd;//保存当前结点的地址
		tmp2=pd->np^prev;//pd下一个节点的地址值

		if(pd->value==elem){//如果找到需要删除的值			
			tmp=cur^((pdlist)prev)->np;//上一结点的前向结点地址		
			((pdlist)prev)->np=tmp^tmp2;//更新上一节点的np值
			tmp3=((pdlist)tmp2)->np^cur;//pd下二个结点的地址值
			((pdlist)tmp2)->np=prev^tmp3;//更新pd下一个结点的np值
			delete pd;//删除当前结点			
		}else{
			prev=cur;
		}
		pd=(pdlist)tmp2;
	}
	if(pd->value==elem){
		cur=(unsigned int) pd;//保存当前结点的地址
		tmp2=pd->np^prev;//pd下一个节点的地址值
		tmp=cur^((pdlist)prev)->np;//上一结点的前向结点地址		
		((pdlist)prev)->np=tmp^tmp2;//更新上一节点的np值
		delete pd;
	}
}


int main()
{
	dlist dl;//头结点
	dl.value=numeric_limits<int>::min();
	dl.np=0;//头结点，初始值为零

	srand((unsigned)time(NULL));
	int count;
	while(count=rand()%6,count<5);
	count=100;

	pdlist pd=&dl;//存放当前结点
	pdlist pp=&dl;//存储上一个结点的指针
	int tmp;//存放当前结点的值
	for(int i=0;i<count;++i){
		pd=new dlist;
		tmp=rand()%51-25;
		pd->value=tmp;
		pd->np=(unsigned int)pp;//初始时，当前结点存放前一结点的地址
		insert(pp,pd);
		pp=pd;//上一个结点指针
		cout<<tmp<<"\t";
	}
	cout<<endl;
	display_inverse(pd);

	//双向链表，顺序显示 
	display_in_order(dl);

	int num=rand()%51-25;
	cout<<num<<" were be deleted."<<endl;
	del(dl,num);
	display_in_order(dl);
}
