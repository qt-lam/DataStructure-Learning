//二叉树的计算
#include <iostream>
using namespace std;

typedef char datatype;

typedef struct BitNode {
	datatype data;
	BitNode* lchild, *rchild;
}BitNode, *BitTree;


typedef BitNode *sqtype;

typedef struct {
	sqtype* base;
	int front, rear;
	int maxsize;
}SqQueue;

int creatqueue(SqQueue& Q) {

	Q.maxsize = 50;//暂定50
	Q.maxsize++;//空出一个来区分满和空
	Q.base = (sqtype*)malloc(sizeof(sqtype)*Q.maxsize);
	if (Q.base == NULL)
		return 0;
	Q.front = Q.rear = 0;
	return 1;
}

//插入队尾
int enqueue(SqQueue& Q, sqtype e) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)//下标+1
		return 0;//队列已经满了，插入失败

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	return 1;//成功 
}

//出队
int dequeue(SqQueue& Q, sqtype& e) {
	if (Q.front == Q.rear)
		return 0;//空

	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % Q.maxsize;
	return 1;
}

//空队列
int queue_empty(SqQueue&Q) {
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
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

//显示树形
void printree(BitTree& T, int n) {
	int i;
	char c = ' ';
	if (T) {
		printree(T->rchild, n + 1);
		for (i = 1; i <= n; i++)
			printf("%5c", c);//间隔5个
		cout << T->data << endl;
		printree(T->lchild, n + 1);
	}
}

//递归算法来统计叶子结点
int leafnode_num(BitTree& T) {
	if (T == NULL)
		return 0;
	else if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else
		return leafnode_num(T->lchild) + leafnode_num(T->rchild);
}

//递归算法求总的叶子结点
int allnode_num(BitTree& T) {
	if (T == NULL)
		return 0;
	else
		return (1 + allnode_num(T->lchild) + allnode_num(T->rchild));
}

//二叉树后序遍历计算二叉树深度--(!)
int Depth(BitTree& T) {
	int depl, depr;
	if (T) {
		depl = Depth(T->lchild);
		depr = Depth(T->rchild);
		if (depl >= depr)
			return depl + 1;
		else
			return depr + 1;
	}
	return 0;
}

//左右子树交换
void Exchange(BitTree& T) {
	BitTree S;
	if (T) {
		S = T->lchild;
		T->lchild = T->rchild;
		T->rchild = S;
		Exchange(T->lchild);
		Exchange(T->rchild);
	}
}

int main() {
	BitTree T;
	creatbitree(T);
	cout << leafnode_num(T) << endl;
	cout << allnode_num(T) << endl;
	cout << Depth(T) << endl;
	printree(T, 0);
	Exchange(T);
	printree(T, 0);
	return 0;
}