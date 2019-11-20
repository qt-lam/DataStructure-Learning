//�������Ĵ��������
//������Ҫʹ�õݹ����
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
	Q.front = Q.rear=0;
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

//����������,�޻���
void prioder_print(BitTree& T) {
	if (T) {
		cout << T->data;
		prioder_print(T->lchild);
		prioder_print(T->rchild);
	}
}

//�������������޻���
void inorder_print(BitTree& T) {
	if (T) {
		inorder_print(T->lchild);
		cout << T->data;
		inorder_print(T->rchild);
	}
}

//�������������޻���
void postorder_print(BitTree& T) {
	if (T) {
		postorder_print(T->lchild);
		postorder_print(T->rchild);
		cout << T->data;
	}
}

//��α���
void levelorder_print(BitTree& T) {
	SqQueue Q;
	creatqueue(Q);//���г�ʼ��

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

//��ʾ����
void printree(BitTree& T,int n) {
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