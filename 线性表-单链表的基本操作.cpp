//单链表的基本操作
//2025.11.10

#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

//线性表-单链表存储表示
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;       //LinkList L等价于LNode *L;

//操作1：求线性表的长度
int ListLength_L(LinkList L){   //L是链表的头指针，代指整个链表 
    LinkList p=L;
    int k=0;
    while(p){
        k++;
        p=p->next;  //指针后移
    }
    return k;
}

//操作2：查找元素（返回指向所查找元素的指针）
LNode* LocateElem_L(LinkList L,ElemType e){
    LinkList p=L;
    while(p){
        if(p->data==e)return p;
        else p=p->next;
    }
    return NULL;
}

//操作3：插入节点操作
void ListInsert_L(LinkList &L,LNode *p,LNode *s){
    //将s结点插入到p结点之前
    //特殊情况处理：p为头节点，要插入到头节点之前
    if(p==L){
        s->next=L;
        L=s;
    }else{
        LinkList q=L;
        while(q&&q->next!=p){
            q=q->next;  //找到q的前驱节点q,最后插入后顺序应为q->s->p
        }
        q->next=s;
        s->next=p;
    }
}

//操作4：删除节点操作
void ListDelete_L(LinkList &L,LNode *p,ElemType e){
    //L为链表头指针，删除链表中p所指节点，并由e返回其元素
    if(p==L){   //特殊情况处理，删除链表头节点，修改链表头指针
        L=p->next;
    }else{
    //找到p的前驱节点
    LinkList q=L;
    while(q->next!=p) q=q->next;
    q->next=p->next;    //让p的前驱节点q与p的后继节点接上
    }
    e=p->data;
    delete p;
}

//操作5：逆序创建链表
void CreateList_L(LinkList &L,ElemType A[],int n){
    //已知一维数组A[n]中存有线性表的n个数据元素，逆序创建单链表L；
    //所指的"逆序"并不是让元素顺序逆序，而是指从后面开始一个个创建节点
    L=NULL; //初始化头指针（置空）
    for(int i=n-1;i>=0;i--){
        LinkList s=new LNode;   //new一个新节点
        s->data=A[i];   //节点数据域赋值
        //先让新节点指针域指向头节点，再把新节点更新为头节点
        s->next=L;  
        L=s;
    }
}

//操作6：逆置单链表
void InvertLinkedList(LinkList &L){
    //逆置头指针L所指单链表
    LinkList p=L;L=NULL; 
    //从第一个节点开始，不断将节点插入到空表表头，实现逆序(类似逆序创建单链表)   
    while(p){
        LinkList s=p;
        p=p->next;
        s->next=L;
        L=s;
    }
}

//操作6：将链表Lb中所有在La中不存在的元素插入到La(在末尾插入即可),并释放Lb中多余结点
//相当于求两个链表的并集（用La表示）
void union_L(LinkList &La,LinkList &Lb){
    if(!La)La=Lb;   //特殊情况处理
    else {
        while(Lb){
            //从头结点开始，逐个拿出Lb所指链表的节点
            LinkList s=Lb;
            Lb=Lb->next;
            LinkList p=La;
            //在La中查找看是否在La中存在
            LinkList pre;
            while(p&&p->data!=s->data){
                pre=p; 
                p=p->next;  //循环至最后一个节点如果还没找到，则p=NULL；
            }
            if(p) delete s; //如果p存在，说明找到了，那就不需要，直接删除
            else{
                //这时候p空了，pre才是最后一个节点,将s插入到末尾即pre后面
                pre->next=s;
                s->next=NULL;
            }

        }
    }
}

//输出函数
void PrintList(LinkList L,const char *name){
    //cout遇到const char*（以'\0'结尾的C字符串指针）时，它不会输出地址，而是输出字符串的内容
    cout<<name<<"单链表为:";
    while(L){
        cout<<L->data<<" ";
        L=L->next;
    }
    cout<<endl;
}

int main(){
    LinkList L1,L2;
    ElemType A[]={1,2,3,4,5};
    ElemType B[]={4,5,6,7};
    cout<<"创建链表："<<endl;
    CreateList_L(L1,A,5);
    CreateList_L(L2,B,4);
    PrintList(L1,"L1");
    PrintList(L2,"L2");
    int k=ListLength_L(L1);
    cout<<"L1的长度为："<<k<<endl;
    //查找元素3
    LNode *p=LocateElem_L(L1,3);
    if(p)cout<<"找到，地址="<<p<<",值="<<p->data<<endl;
    //在元素3前插入新节点99
    LNode *s=new LNode; //创建新节点（即创建一个指向新节点的指针s）
    s->data=99;
    ListInsert_L(L1,p,s);
    PrintList(L1,"L1");
    //删除结点3
    ElemType e;
    ListDelete_L(L1,p,e);
    PrintList(L1,"L1");
    //逆置L1
    InvertLinkedList(L1);
    cout<<"逆置后";
    PrintList(L1,"L1");
    //求L1和L2的并集（合并在L1中）
    union_L(L1,L2);
    cout<<"L1和L2求并集得到的";
    PrintList(L1,"L1");

    return 0;
}
