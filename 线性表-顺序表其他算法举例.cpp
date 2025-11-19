//线性表的其他算法举例
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

//线性表初始化
Status InitList_Sq(SqList &L){
    L.elem=new ElemType[MAXSIZE];   //分配空间
    if(!L.elem) return ERROR;
    L.length=0;     //长度置零
    return OK;
}

//线性表插入操作
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

//输入线性表
void InpushList(SqList &L,int n){
    int m;
    cout<<"请输入插入的元素:"<<endl;
    for(int i=1;i<=n;i++){
        cin>>m;
        ListInsert_Sq(L,i,m);
    }
}

//打印线性表
void PrintList(SqList L,int n){ //n为元素个数
    cout<<"线性表为：";
    for(int i=1;i<=n;i++){
        cout<<L.elem[i-1]<<" ";
    }
    cout<<endl;
}

//算法1：顺序表比较(返回-1,0,1三个值代表<,=,>)
/*描述：只有长度相等且每个位置元素相等顺序表才相等，A[j]和B[j]比较，相等则j++，逐个比较
循环条件为j不大于任何一个表的表长
循环正常跳出后得分三种情况，即长度相等，A.length>B.length,A.length<B.length*/
int Compare(SqList A,SqList B){
    int j=0;    //j属于[0,length-1]
    while(j<A.length&&j<B.length){
        if(A.elem[j]<B.elem[j])return -1;
        else if(A.elem[j]>B.elem[j])return 1;
        else j++;
    }
    if(A.length==B.length)return 0;
    else if(A.length<B.length)return -1;
    else return 1;
}

//算法2：交换顺序表前m个元素和后n个元素（开辟辅助空间法）
//描述：把后面n个元素从左至右一个个往前移，后移的接在先移的元素后面，每拿出一个元素，前面的元素整体右移一位
void Exchang1(SqList &L,int m,int n){
    int k,w;
    for(k=1;k<=n;k++){      //外层循环次数即为后n个元素的个数n
        w=L.elem[m+k-1];     //[m]~[m+n-1]需要移的n个元素(第m+1个元素~第m+n个元素)
        //拿出来之后，前面的元素从右到左逐个右移
        //难点：内层循环条件
        for(int j=m+k-1;j>=k;j--){
            L.elem[j]=L.elem[j-1];      //[j-1]其实就是第j个元素
        }
        //再把拿出来的待移元素前移
        L.elem[k-1]=w;  //下标一定是从0到n-1，结合k范围易知[]填k-1
        
    }
}

//算法3：交换顺序表前m个元素和后n个元素（双逆置法）
//描述：先整体逆置(得到bn,...b2,b1,am,...a2,a1)，再把前n个元素和后m个元素逆置
//得到b1,b2...bn,a1,a2,...,am
//先写逆置线性表的算法
void invert(SqList &L,int s,int t){
    //将线性表下标自s到t的元素逆置
    for(int k=s;k<=(s+t)/2;k++){
        int w=L.elem[k];
        L.elem[k]=L.elem[t-k+s];
        L.elem[t-k+s]=w;
    }
}
//再写Exchang2
void Exchang2(SqList &L,int m,int n){
    invert(L,0,m+n-1);  //整体逆置
    invert(L,0,n-1);    //前n个元素逆置
    invert(L,n,n+m-1);   //后m个元素逆置
}

//主函数测试
int main(){
    SqList L;
    int n;
    cout<<"请输入数组大小："<<endl;
    cin>>n;
    L.length=n;
    InitList_Sq(L);
    InpushList(L,n);
    PrintList(L,n);
    Exchang1(L,3,2);
    PrintList(L,n);
    Exchang2(L,1,4);
    PrintList(L,n);

    return 0;


}
