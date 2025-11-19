//线性表的基本操作
//2025.11.10

#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

typedef struct{
    ElemType *elem;     //elem指向一段连续内存的基地址，每个元素：L.elem[i];
    int length;
}SqList; 

//操作1：线性表的初始化
Status InitList_Sq(SqList &L){
    L.elem=new ElemType[MAXSIZE];   //分配空间
    if(!L.elem) return ERROR;
    L.length=0;     //长度置零
    return OK;
}

//操作2：销毁线性表
void DestoryList(SqList &L){
    if(L.elem) delete[] L.elem;   //释放存储空间
}

//操作3：清空线性表
void ClearList(SqList &L){
    L.length=0; //长度置零即为清空
}

//操作4：求线性表长度
int GetLength(SqList &L){
    return L.length;
}

//操作5：判断线性表是否为空
bool IsEmpty(SqList &L){
    if(L.length==0){
        return true;
    }else{
        return false;
    }
}

//操作6：线性表的取值（根据位置i获取相应位置数据元素的内容）
//获取的第i个元素在数组中的下标是i-1
int GetElem(SqList &L,int i,ElemType &e){
    if(i<1||i>L.length) return ERROR;   //异常判断
    e=L.elem[i-1];
    return OK;
}

//操作7：顺序表的顺序查找
//在线性表中查找值为e的数据元素并返回其序号（是第几个元素）（return i+1）
Status LocateElem(SqList &L,ElemType e){
    for(int i=0;i<L.length;i++){
        if(e==L.elem[i])  return i+1;   //查找成功，返回序号（不是下标）
    }
    return 0;   //查找失败返回0
}

//操作8:插入元素
//核心思路：把插入位置后面的元素（包括插入位置的元素）整体后移，再把需要插入的元素放到空出来的位置
//所谓的整体后移其实是从最后一个元素开始逐个后移
Status ListInsert_Sq(SqList &L,int i,ElemType e){
    if(i<1||i>L.length+1)return ERROR;    //插入位置不合法（1~length+1才合法）
    if(L.length==MAXSIZE)return ERROR;  //当前存储空间已满
    //这里的j就是下标了
    //插入位置i，下标为i-1,把下标[i-1,L.length-1]的元素后移
    for(int j=L.length-1;j>=i-1;j--){
        L.elem[j+1]=L.elem[j];  //后移
    }
    //插入
    L.elem[i-1]=e;
    //长度加1
    L.length++;
    return OK;
}

//辅助函数：打印顺序表
void PrintSqList(SqList L){
    cout<<"顺序表为：";
    for(int i=0;i<L.length;++i){
        cout<<L.elem[i]<<" ";
    }
    cout<<endl;
}

int main(){
    SqList L;
    InitList_Sq(L);
    int n;
    int m;
    cout<<"请输入数组大小："<<endl;
    cin>>n;
    L.length=n;
    cout<<"请输入"<<n<<"个元素:"<<endl;
    for(int i=0;i<L.length;i++){
        cin>>m;
        L.elem[i]=m;
    }
    PrintSqList(L);
    
    cout<<"请输入插入的单个元素:"<<endl;
    cin>>m;
    cout<<"请输入插入位置(第几个元素之前):"<<endl;
    int k;
    cin>>k;
    ListInsert_Sq(L,k,m);
    PrintSqList(L);
    
    cout<<endl;
    
    return 0;
}
