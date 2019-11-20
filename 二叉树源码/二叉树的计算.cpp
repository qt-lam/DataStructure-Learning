//�������ļ���
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

	Q.maxsize = 50;//�ݶ�50
	Q.maxsize++;//�ճ�һ�����������Ϳ�
	Q.base = (sqtype*)malloc(sizeof(sqtype)*Q.maxsize);
	if (Q.base == NULL)
		return 0;
	Q.front = Q.rear = 0;
	return 1;
}

//�����β
int enqueue(SqQueue& Q, sqtype e) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)//�±�+1
		return 0;//�����Ѿ����ˣ�����ʧ��

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	return 1;//�ɹ� 
}

//����
int dequeue(SqQueue& Q, sqtype& e) {
	if (Q.front == Q.rear)
		return 0;//��

	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % Q.maxsize;
	return 1;
}

//�ն���
int queue_empty(SqQueue&Q) {
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}


//��������������������
int creatbitree(BitTree& T) {
	char c;
	cin >> c;
	if (c == '#')
		T = NULL;
	else {
		T = (BitNode*)malloc(sizeof(BitNode));
		if (T == NULL)
			return 0;//����ʧ��,����ʧ��

		T->data = c;
		creatbitree(T->lchild);
		creatbitree(T->rchild);
	}
	return 1;
}

//��ʾ����
void printree(BitTree& T, int n) {
	int i;
	char c = ' ';
	if (T) {
		printree(T->rchild, n + 1);
		for (i = 1; i <= n; i++)
			printf("%5c", c);//���5��
		cout << T->data << endl;
		printree(T->lchild, n + 1);
	}
}

//�ݹ��㷨��ͳ��Ҷ�ӽ��
int leafnode_num(BitTree& T) {
	if (T == NULL)
		return 0;
	else if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else
		return leafnode_num(T->lchild) + leafnode_num(T->rchild);
}

//�ݹ��㷨���ܵ�Ҷ�ӽ��
int allnode_num(BitTree& T) {
	if (T == NULL)
		return 0;
	else
		return (1 + allnode_num(T->lchild) + allnode_num(T->rchild));
}

//�������������������������--(!)
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

//������������
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