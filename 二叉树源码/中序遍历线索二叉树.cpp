//中序遍历线索二叉树
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


typedef BiThNode* selemtype;



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
//中序线索化二叉树，使用递归方法
void inthreading(BiThTree& T) {
	if (T) {
		inthreading(T->lchild);

		if (!T->lchild) {
			T->Ltag = Thread;//左结点为空，指向前驱
			T->lchild = pre;
		}

		if (!T->rchild)
			T->Rtag = Thread;//右结点为空，先使标识为线索

		if (pre&&pre->Rtag == Thread)//前驱存在且右结点为空，右孩子指向后继
			pre->rchild = T;

		pre = T;


		inthreading(T->rchild);
	}
}


//中序遍历线索二叉树,非递归
void inorder_Th(BiThTree& T) {
	BiThNode* p = T;

	while (1) {
		while (p->Ltag == Link) {
			p = p->lchild;
		}
		cout << p->data;

		if ((p->Rtag == Thread && p->rchild == NULL))
			break;

		while (p->Rtag == Thread) {
			p = p->rchild;
			cout << p->data;
			if ((p->Rtag == Thread && p->rchild == NULL))
				break;
		}

		if ((p->Rtag == Thread && p->rchild == NULL))
			break;
		p = p->rchild;
	}
	cout << endl;
}


void findneibor(BiThTree& T,datatype e) {
	BiThNode* p = T;

	BiThNode** s = (BiThNode**)malloc(sizeof(BiThNode*)*20);
	int i = 0;


	while (1) {
		while (p->Ltag == Link) {
			p = p->lchild;
		}

		s[i] = p;
		i++;

		if ((p->Rtag == Thread && p->rchild == NULL))
			break;

		while (p->Rtag == Thread) {
			p = p->rchild;

			s[i] = p;
			i++;

			if ((p->Rtag == Thread && p->rchild == NULL))
				break;
		}

		if ((p->Rtag == Thread && p->rchild == NULL))
			break;
		p = p->rchild;
	}


	int k = 0;
	for (int j = 0; j < i; j++) {
		if (s[j]->data == e) {
			k = 1;
			if (i == 1) {
				cout << "succ is NULL" << endl;
				cout << "prev is NULL" << endl;
			}
			else if (j == 0) {
				cout << "succ is " << s[j + 1]->data << s[j + 1]->Rtag << endl;
				cout << "prev is NULL" << endl;				
			}
			else if (j == i-1) {
				cout << "succ is NULL" << endl;
				cout << "prev is " << s[j - 1]->data << s[j - 1]->Ltag << endl;
			}
			else {
				cout << "succ is " << s[j + 1]->data << s[j + 1]->Rtag << endl;
				cout << "prev is " << s[j - 1]->data << s[j - 1]->Ltag << endl;
			}
			break;
		}
	}

	if (k == 0)
		cout << "Not found" << endl;
}

int main() {
	BiThTree T;
	creatbitree(T);
	inthreading(T);
	inorder_Th(T);
	datatype e;
	cin >> e;
	findneibor(T, e);
	return 0;
}