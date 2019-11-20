//先序遍历线索二叉树
#include <iostream>
using namespace std;

typedef char datatype;

enum PointerTag {
	Link, Thread//link==0,指针 thread==1,线索
};

typedef struct BiThNode {
	datatype data;//数据
	BiThNode *lchild, *rchild;//左右孩子结点
	PointerTag Ltag, Rtag;//左右标识
}BiThNode, *BiThTree;


//先序输入来创建二叉树,尚未线索化
int creatbitree(BiThTree& T) {
	char c;
	cin >> c;
	if (c == '#')
		T = NULL;
	else {
		T = (BiThNode*)malloc(sizeof(BiThNode));
		if (T == NULL)
			return 0;//申请失败,创建失败

		T->data = c;
		T->Ltag = T->Rtag = Link;//先全部定为LINK ，线索化时再分
		creatbitree(T->lchild);
		creatbitree(T->rchild);
	}
	return 1;
}



BiThTree pre = NULL;//全局指针变量，指向前驱结点
//递归方法先序线索化
void prethreading(BiThTree& T){
	if (T) {
		if (!T->lchild) {
			T->Ltag = Thread;//左结点为空，指向前驱
			T->lchild = pre;
		}
		if (!T->rchild)
			T->Rtag = Thread;//右结点为空，先使标识为线索

		if (pre&&pre->Rtag == Thread)//前驱存在且右结点为空，右孩子指向后继
			pre->rchild = T;

		pre = T;


		if (T->Ltag == Link)
			prethreading(T->lchild);
		if (T->Rtag == Link)
			prethreading(T->rchild);

	}
}

//显示先序线索二叉树的树型图
void printree(BiThTree& T, int n) {
	int i;
	char c = ' ';
	if (T) {
		if(T->Rtag==Link)
			printree(T->rchild, n + 1);
		for (i = 1; i <= n; i++) {
			printf("%5c", c);//间隔5个
			
		}		
		cout << T->data;
		printf("%d%d\n", T->Ltag, T->Rtag);
		if(T->Ltag==Link)
			printree(T->lchild, n + 1);
	}
}

//先序遍历线索二叉树
void preorder_Th(BiThTree& T) {
	BiThNode* p = T;
	cout << p->data;
	while (p->rchild) {//这样判断比判断RTAG好一些
		if (p->Ltag == Link)
			p = p->lchild;
		else
			p = p->rchild;
		cout << p->data;
	}
}

int main()
{
	BiThTree T;
	creatbitree(T);
	prethreading(T);
	printree(T,0);
	preorder_Th(T);

	return 0;
}