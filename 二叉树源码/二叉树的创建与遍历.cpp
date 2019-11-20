//二叉树的创建与遍历
//本题主要使用递归遍历
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
	Q.front = Q.rear=0;
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

//先序遍历输出,无换行
void prioder_print(BitTree& T) {
	if (T) {
		cout << T->data;
		prioder_print(T->lchild);
		prioder_print(T->rchild);
	}
}

//中序遍历输出，无换行
void inorder_print(BitTree& T) {
	if (T) {
		inorder_print(T->lchild);
		cout << T->data;
		inorder_print(T->rchild);
	}
}

//后序遍历输出，无换行
void postorder_print(BitTree& T) {
	if (T) {
		postorder_print(T->lchild);
		postorder_print(T->rchild);
		cout << T->data;
	}
}

//层次遍历
void levelorder_print(BitTree& T) {
	SqQueue Q;
	creatqueue(Q);//队列初始化

	if (T) {
		enqueue(Q, T);
		while (!queue_empty(Q)) {
			BitNode* c;
			dequeue(Q, c);
			cout << c->data;

			if (c->lchild) 
				enqueue(Q, c->lchild);
			
			if (c->rchild) 
				enqueue(Q, c->rchild);			
		}
	}
}

//显示树形
void printree(BitTree& T,int n) {
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

int main()
{
	BitTree T;
	creatbitree(T);
	prioder_print(T);
	cout << endl;
	inorder_print(T);
	cout << endl;
	postorder_print(T);
	cout << endl;
	levelorder_print(T);
	cout << endl;
	printree(T, 0);

	return 0;
}