#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

typedef struct list{
	int id;
	int left_time;
	list *next;
}list,*plist;

typedef struct queue{
	list *front;
	list *tail;
}queue,*pqueue;

void init(pqueue & qu)//队列初始化
{
	qu->front=NULL;
	qu->tail=NULL;
}

void enqueue(pqueue &qu,int id,int left_time)//入队列
{
	plist pl=new list;
	pl->id=id;
	pl->left_time=left_time;

	if(qu->front==NULL){//初始队列为空		
		qu->front=pl;
		qu->tail=pl;
		pl->next = NULL;
	}else{
		if(left_time<qu->front->left_time){
			pl->next=qu->front;
			qu->front=pl;
		}else{
			plist pt=qu->front->next;
			plist prev=qu->front;//前一个结点，初始指向队列
			while(pt){//按照剩余时间的多少插入到队列合适位置
				if(left_time > pt->left_time){
					prev=pt;
					pt=pt->next;
				}else{
					break;
				}
			}
			pl->next=pt;
			prev->next=pl;//如果应该插入到队列的第一个元素
		}
	}
}

plist dequeue(pqueue &qu)
{
	if(qu->front==NULL){
		cout<<"queue underflow"<<endl;
		return	NULL;
	}
	plist pl=qu->front;
	qu->front=qu->front->next;
	return pl;
}

void least_time_schedule_algorithm(int *r,int *p,int n,plist *&presult)//最小化完成时间
{
	pqueue qu=new queue;//任务调度队列
  	init(qu);//初始化队列
	plist pl;
	plist plnode;//作为存储运行时间的结果时，id是开始时间，left_time表示结束时间
	for(int i=1;i<n;++i){
		if(r[i-1]+p[i-1]>r[i]){
			plnode=new list;
			plnode->id=r[i-1];
			plnode->left_time=r[i];
			plnode->next=presult[i-1]->next;
			presult[i-1]->next=plnode;//将结点插入链表
			enqueue(qu,i-1,r[i-1]+p[i-1]-r[i]);
		}else{
			plnode=new list;//存储任务i-1的开始和截止时间,因为任务的开始和截止时间，不与其他时间冲突，可以顺利完成所有任务。
			plnode->id=r[i-1];
			plnode->left_time=r[i-1]+p[i-1];
			plnode->next=presult[i-1]->next;
			presult[i-1]->next=plnode;

			int ti=0;//在队列中的任务花费的时间
			pl=qu->front;
			while(pl){				
				if(pl->left_time<=r[i]-r[i-1]-p[i-1]-ti){
					plnode=new list;
					plnode->id=r[i-1]+p[i-1]+ti;
					plnode->left_time=r[i-1]+p[i-1]+ti+pl->left_time;
					plnode->next=presult[pl->id]->next;
					presult[pl->id]->next=plnode;
					ti+=pl->left_time;
					pl=dequeue(qu);
					delete pl;
					pl=qu->front;
				}else{
					if(r[i]-r[i-1]-p[i-1]-ti){
						pl->left_time-=(r[i]-r[i-1]-p[i-1]-ti);							
						plnode=new list;
						plnode->id=r[i-1]+p[i-1]+ti;
						plnode->left_time=r[i];
						plnode->next=presult[pl->id]->next;
						presult[pl->id]->next=plnode;
					}
					break;
				}
			}
		}
	}

	plnode=new list;
	plnode->id=r[n-1];
	plnode->left_time=r[n-1]+p[n-1];
	plnode->next=presult[n-1]->next;
	presult[n-1]->next=plnode;

	int btime=r[n-1]+p[n-1];
	pl=dequeue(qu);
	while(pl){
		plnode=new list;
		plnode->id=btime;//调度开始时间
		btime+=pl->left_time;
		plnode->left_time=btime;//调度结束时间
		plnode->next=presult[pl->id]->next;
		presult[pl->id]->next=plnode;
		delete pl;
		pl=dequeue(qu);
	}
	delete qu;
}

void reverse_print(plist result)//输出信息
{
	if(result){
		if(result->next){
			reverse_print(result->next);
		}
		cout<<"[ "<<result->id<<" , "<<result->left_time<<" ] ";
		delete result;//删除结点
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=7;
	int *r=new int[n];
	int *p=new int[n];
	r[0]=1,r[1]=4,r[2]=6,r[3]=7,r[4]=11;
	p[0]=3,p[1]=4,p[2]=2,p[3]=6,p[4]=1;
	
	for(int i=1;i<n;++i){
		r[i]=r[i-1]+rand()%5+1;
		p[i]=rand()%5+2;
	}

	for(int i=0;i<n;++i){
		cout<<r[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<p[i]<<" ";
	}
	cout<<endl;
	plist *presult=new plist[n];
	for(int i=0;i<n;++i){
		presult[i]=new list;
		presult[i]->id=r[i];
		presult[i]->left_time=p[i];
		presult[i]->next=NULL;
	}
	least_time_schedule_algorithm(r,p,n,presult);
	for(int i=0;i<n;++i){
		cout<<"task "<<i<<" : ";
		reverse_print(presult[i]->next);
		cout<<endl;
	}
	delete []r;
	delete []p;
}
