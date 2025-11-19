//循环链表的基本操作
//2025.11.11

#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

//线性表-循环链表存储表示（和单链表一样，因为循环链表就是特殊的单链表）
//只是在初始化的时候不同，尾指针要指向头结点
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;       //LinkList L等价于LNode *L;

// 初始化循环链表（带头结点）
void InitList(LinkList &R) {
    R = new LNode;  // 创建头结点
    R->next = R;    // 头结点指向自己
}

//判断是否为空表
bool ListEmpty(LinkList L){
    return (L->next == L);
}

// 尾插法创建循环链表（用尾指针表示）（从头结点后面一个一个插）
void CreateList_L(LinkList &R, ElemType A[], int n) {
    InitList(R);    //R既是头结点也是尾结点
    for (int i = 0; i < n; i++) {
        LinkList s = new LNode; 
        s->data = A[i];
        s->next = R->next;  // 新结点指向头结点
        R->next = s;        // 原尾结点指向新结点
        R = s;              // 更新尾指针
    }
}

//算法1：带尾指针的循环链表的合并（一个尾指针为Ta，一个尾指针为Tb，尾指针也代指整个循环链表）
/*注：尾指针是指向尾结点的指针，而不是尾结点的指针域。
将Tb表头连接在Ta表尾（Ta尾指针指针域指向Tb第一个数据节点），释放Tb的头结点，
同时Tb的尾结点的指针域指向Ta的头结点*/
LinkList Connect(LinkList Ta,LinkList Tb){
    LinkList p=Ta->next;
    Ta->next=Tb->next->next;    //连接，让Ta尾结点指针域指向Tb第一个数据节点
    delete Tb->next;    //释放Tb的头结点
    Tb->next=p; //让Tb尾结点指针域指向Ta头结点
    return Tb;  //Tb为合并后循环链表的尾指针，代指整个循环链表
}

//打印循环链表
void PrintList(LinkList R,const char *name){
    //cout遇到const char*（以'\0'结尾的C字符串指针）时，它不会输出地址，而是输出字符串的内容
     if (R->next == R) {
        cout << name << "是空表\n";
        return;
    }
    cout<<name<<"循环单链表为:";
    LinkList p=R->next->next;   //第一个数据节点
    while (p != R->next) {       // p到头结点就停，不输出头结点
        cout << p->data << " ";
        p = p->next;
    }
    cout<<endl;
}

int main(){
    LinkList L1,L2;
    InitList(L1);
    InitList(L2);
    ElemType A[]={1,2,3,4,5};
    ElemType B[]={6,7,8};
    CreateList_L(L1,A,5);
    CreateList_L(L2,B,3);
    Connect(L1,L2);
    PrintList(L2,"L2");
    cout<<"第一个数据节点为"<<L2->next->next->data<<endl;

    return 0;
}


