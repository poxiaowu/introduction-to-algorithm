#include<iostream>
#include <limits>
#include<ctime>
using namespace std;

typedef struct list{
	int tag;//教室编号
	int time;//活动的结束时间
	list *next;//下一个活动
}list ,*plist;

void minimum_lecture_hall(plist &busing,plist &free,int *s,int *f,int * lecture_hall,int &lecture_hall_no,int n)//最小教室问题与区间图着色问题类似
{//busing指向正在有活动的教室，free指向当前无活动的教室
	plist tmpnode,tnode,prenode;
	for(int i=0;i<n;++i){
		tmpnode=busing->next;//指向有活动的教室的首节点
		prenode=busing;//前一节点
		while(tmpnode){
			if(tmpnode->time<=s[i]){
				tnode=tmpnode->next;
				tmpnode->next=free->next;
				free->next=tmpnode;
				prenode->next=tnode;
				tmpnode=prenode;
			}
			prenode=tmpnode;
			tmpnode=tmpnode->next;
		}
		if(free->next){//free链表中有空余的教室
			tmpnode=free->next;
			tmpnode->time=f[i];//活动结束时间
			free->next=free->next->next;
			tmpnode->next=busing->next;
			busing->next=tmpnode;//将其添加到活动的链表
			lecture_hall[i]=tmpnode->tag;//存储当前活动所在的教室编号
		}else{//否则无多余教室，则需要另外添加教室,并将其添加到活动链表中
			tmpnode=new list;
			tmpnode->time=f[i];
			tmpnode->tag=lecture_hall_no++;//教室编号
			tmpnode->next=busing->next;
			busing->next=tmpnode;
			lecture_hall[i]=tmpnode->tag;//存储当前活动所在的教室编号
		}
	}	
}
void quick_sort(int *s,int *f,int low,int high)//快速排序，安装活动的开始时间升序排序
{
	while (low<high){
		int pivot=s[high];
		int k=low-1;
		int tmp;
		for(int i=low;i<high;++i){
			if(s[i]<=pivot){
				++k;
				tmp=s[i];
				s[i]=s[k];
				s[k]=tmp;
				tmp=f[i];
				f[i]=f[k];
				f[k]=tmp;
			}
		}
		tmp=s[high];
		s[high]=s[k+1];
		s[k+1]=tmp;
		tmp=f[high];
		f[high]=f[k+1];
		f[k+1]=tmp;
		if((k-low)<(high-k-2)){//栈深度为O(lgn)
			quick_sort(s,f,low,k);		
			low=k+2;
		}else{
			quick_sort(s,f,k+2,high);
			high=k;
		}
	}
}

void sort_final_time(int *s,int *f,int n)//按照结束时间排序
{
	int low=0,high=0,tmp;
	for(int i=1;i<=n;++i){
		if(s[i]!=s[i-1]){
			low=i;
		}else{
			high=i;
			tmp=f[i];
			while (high>low && tmp<f[high-1]){//开始时间相同，结束时间进行插入排序
				f[high]=f[high-1];
				--high;
			}
			f[high]=tmp;
			/*for(int j=low;j<=i;++j){
				cout<<s[j]<<" ";
			}
			cout<<endl;
			for(int j=low;j<=i;++j){
				cout<<f[j]<<" ";
			}
			cout<<endl;*/
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int n=11;
	int *s=new int[n];
	int *f=new int[n];
	/*s[0]=1,s[1]=3,s[2]=0,s[3]=5,s[4]=3,s[5]=5,s[6]=6,s[7]=8,s[8]=8,s[9]=2,s[10]=12;	
	f[0]=4,f[1]=5,f[2]=6,f[3]=7,f[4]=9,f[5]=9,f[6]=10,f[7]=11,f[8]=12,f[9]=14,f[10]=16;*/
	for(int i=0;i<n;++i){
		s[i]=rand()%n+1;//活动i开始时间
		f[i]=rand()%(n/2)+1+s[i];//活动i结束时间
	}
	quick_sort(s,f,0,n-1);//按照开始时间排序
	sort_final_time(s,f,n-1);//按照结束时间排序

	/*s[0]=0,s[1]=1,s[2]=2,s[3]=3,s[4]=3,s[5]=5,s[6]=5,s[7]=6,s[8]=8,s[9]=8,s[10]=12;	
	f[0]=6,f[1]=4,f[2]=14,f[3]=5,f[4]=9,f[5]=7,f[6]=9,f[7]=10,f[8]=11,f[9]=12,f[10]=16;*/
	for(int i=0;i<n;++i){
		cout<<s[i]<<"\t";
	}
	cout<<endl;
	for(int i=0;i<n;++i){
		cout<<f[i]<<"\t";
	}
	cout<<endl;
	plist busing=new list;//指向正有活动的教室
	busing->next=NULL;
	plist free=new list;//指向无活动的教室
	free->next=NULL;
	int lecture_hall_no=0;//当前使用的教室编号
	int *lecture_hall=new int[n];//为每个活动存储教室编号
	minimum_lecture_hall(busing,free,s,f,lecture_hall,lecture_hall_no,n);

	for(int i=0;i<n;++i){
		cout<<"active "<<i<<" : [ "<<s[i]<<" , "<<f[i]<<" )"<<" is arranged in lecture hall "<<lecture_hall[i]<<endl;
	}

	delete []s;
	delete []f;
	delete [] lecture_hall;
	plist ls=busing;
	while(ls){
		busing=busing->next;
		delete ls;
		ls=busing;		
	}
	ls=free;
	while(ls){
		free=free->next;
		delete ls;
		ls=free;		
	}
}
