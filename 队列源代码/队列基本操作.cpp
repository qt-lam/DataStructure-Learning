//ѭ�����е�ʵ���Լ���������

#include <iostream>
#include <string.h>
using namespace std;

typedef int QElemType ;

typedef struct {
	QElemType* base;//���������ڴ�Ļ�ַ��ַ
	int front;//����
	int rear;//��β
	int maxsize;//�ö��е�����������Լ����

}SqQueue;

//������У������������ȡ
int initqueue(SqQueue& Q) {

	cin >> Q.maxsize;

	Q.maxsize++;//�ճ�һ��λ�����������Ϳ�

	Q.base = (QElemType*)malloc(sizeof(QElemType)*Q.maxsize);
	if (Q.base == NULL)
		return 0;//��ʼ��ʧ��

	Q.front = Q.rear = 0;//һ��ʼ����0
	return 1;
}

//�����β
int enqueue(SqQueue& Q,QElemType e) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)//�±�+1
		return 0;//�����Ѿ����ˣ�����ʧ��

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	return 1;//�ɹ� 
}

//����
int dequeue(SqQueue& Q, QElemType& e) {
	if (Q.front == Q.rear)
		return 0;//��

	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % Q.maxsize;
	return 1;
}


//�������Ԫ��
void printqueue(SqQueue& Q) {
	while (1) {
		if (Q.front == Q.rear)
			break;//�Ѿ���

		cout << Q.base[Q.front] <<' ';

		Q.front = (Q.front + 1) % Q.maxsize;
	}
	cout << endl;
}

int main()
{
	SqQueue Q;
	initqueue(Q);

	char order[20];
	int k = 0;
	int value;

	while (1) {
		cin >> order;
		if (strcmp(order, "dequeue") == 0) {
			k = dequeue(Q, value);
			if (k == 0)
				cout << "Queue is Empty" << endl;
			else if (k == 1)
				cout << value << endl;
		}
		else if (strcmp(order, "enqueue")==0) {
			cin >> value;
			k = enqueue(Q, value);
			if (k == 0)
				cout << "Queue is Full" << endl;
		}
		else if (strcmp(order, "quit")==0) {
			printqueue(Q);
			break;
		}
	}


	return 0;
}