#include <iostream>
#include<ctime>
using namespace std;
typedef struct list{
	int value;
	list *next;
}list, *pList;

pList build_cirle_list(int n)//创建单向循环链表
{
	pList head=new list;
	pList pl,pp=head;
	for(int i=0;i<n;++i){
		pl=new list;
		pl->value=i+1;
		pp->next=pl;
		pp=pl;
	}
	pp->next=head;
	return head;
}

void josephus_permutation(pList & pl,int m)//josephus 排列
{
	pList pp=pl;
	pList pt;//存放输出元素的上一个元素指针
	while (pp!=pp->next){//判断是否已经是头指针，如果是，则所有元素都已经访问，结束循环		
		for(int i=0;i<m;++i){
			pt=pp;
			pp=pp->next;
			if(pp==pl){//若结点是头指针，则 继续访问下一个元素
				pt=pp;
				pp=pp->next;
			}
		}		
		cout<<pp->value<<"\t";
		pt->next=pp->next;
		delete pp;//删除已经访问过的元素
		pp=pt;//重置pp为已访问元素的上一个指针
	}
	cout<<endl;	
}

int main()
{
	srand((unsigned)time(NULL));
	int n;
	while(n=rand()%20,n<7);
	int m;
	while(m=rand()%10,m<2 && m>n);
	n=10000,m=20;
	cout<<"Josephus permutation : n = "<<n<<" ,m = "<<m<<endl; 
	pList head=build_cirle_list(n);	
	josephus_permutation(head,m);
	
}
