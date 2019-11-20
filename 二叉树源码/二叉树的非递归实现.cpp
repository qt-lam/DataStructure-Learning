//二叉树的非递归实现
#include <iostream>
using namespace std;

typedef char datatype;

//链式二叉树
typedef struct BitNode {
	datatype data;
	BitNode* lchild, *rchild;
}BitNode, *BitTree;


typedef BitNode* selemtype;

//堆栈
typedef struct {
	selemtype* base;
	selemtype* top;
	int stacksize;
}SqStack;

//初始化堆栈,[初始最大容量由输入中获取]
int initstack(SqStack& L) {
	int maxsize = 50;
	//cin >> maxsize;

	L.stacksize = maxsize;//最大容量
	L.base = L.top = (selemtype*)malloc(sizeof(selemtype)*L.stacksize);//一开始栈顶等于栈底
	if (L.base == NULL)
		return 0;//申请失败
	return 1;
}


//判断栈是否为空，是返回1，不是返回0
int stackepmty(SqStack& L) {
	if (L.top == L.base)
		return 1;//栈顶等于栈底
	else
		return 0;//非空
}

//判断栈是否为满，是返回1，不是返回0
int stackfull(SqStack& L) {
	if (L.base + L.stacksize == L.top)//栈顶指向的下一个位置超过的堆栈的内存范围
		return 1;
	else
		return 0;
}

//将值value压栈，返回1则操作成功，返回0则栈满失败
int stackpush(SqStack& L, selemtype value) {
	if (stackfull(L) == 0) {
		*L.top = value;
		L.top++;
		return 1;//成功
	}
	else
		return 0;//失败

}

//出栈，将值赋给value，返回1则操作成功，返回0则栈空失败
int stackpop(SqStack& L, selemtype& value) {
	if (stackepmty(L) == 0) {
		L.top--;
		value = *L.top;
		return 1;//成功
	}
	else {
		return 0;//失败
	}
}

//先序输入来创建二叉树
int creatbitree(BitTree& T) {
	char c;
	cin >> c;
	if (c == '#')
		T = NULL;
	else {
		T = (BitNode*)malloc(sizeof(BitNode));
		if (T == NULL)
			return 0;//申请失败,创建失败

		T->data = c;
		creatbitree(T->lchild);
		creatbitree(T->rchild);
	}
	return 1;
}

//先序输入建立二叉树，使用非递归
//int CreatTree(BitTree& T) {
//	SqStack S;
//	initstack(S);
//
//	char c;
//	while (1) {
//		cin >> c;
//		if (c == '#')
//			T = NULL;
//		else {
//			T = (BitNode*)malloc(sizeof(BitNode));
//			T->data = c;
//			stackpush(S, T);
//		}
//
//		if (T == NULL && stackepmty(S))
//			return 0;
//
//		T = T->lchild;
//	}
//}

//非递归中序遍历
void inorder_print(BitTree& T) {
	SqStack S;
	initstack(S);
	BitTree TP = T;
	while (TP || !stackepmty(S)) {
		if (TP) {
			stackpush(S, TP);
			cout << "push " << TP->data << endl;
			TP = TP->lchild;
		}
		else {
			stackpop(S, TP);
			cout << "pop" << endl;
			cout << TP->data << endl;
			TP = TP->rchild;
		}
	}
}

int main()
{
	BitTree T;
	creatbitree(T);
	inorder_print(T);
	return 0;
}