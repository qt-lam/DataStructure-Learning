//���е�Ӧ��-����


#include <iostream>
#include <string.h>
using namespace std;


struct point {
	int x;
	int y;
};

typedef point QElemType;

typedef struct {
	QElemType* base;//���������ڴ�Ļ�ַ��ַ
	int front;//����
	int rear;//��β
	int maxsize;//�ö��е�����������Լ����

}SqQueue;

//������У������������ȡ
int initqueue(SqQueue& Q) {

	//cin >> Q.maxsize;

	Q.maxsize = 10000;
	Q.maxsize++;//�ճ�һ��λ�����������Ϳ�

	Q.base = (QElemType*)malloc(sizeof(QElemType)*Q.maxsize);
	if (Q.base == NULL)
		return 0;//��ʼ��ʧ��

	Q.front = Q.rear = 0;//һ��ʼ����0
	return 1;
}

//�����β
int enqueue(SqQueue& Q, QElemType e) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)//�±�+1
		return 0;//�����Ѿ����ˣ�����ʧ��

	Q.base[Q.rear*2] = e;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	return 1;//�ɹ� 
}

//����
int dequeue(SqQueue& Q, QElemType& e) {
	if (Q.front == Q.rear)
		return 0;//��

	e = Q.base[Q.front*2];
	Q.front = (Q.front + 1) % Q.maxsize;
	return 1;
}

int queque_empty(SqQueue& Q) {
	if (Q.front == Q.rear)
		return 1;//��
	return 0;
}


//��ʵ���ö�ջ���򵥣�
int scanfmap() {


	int X, Y;
	cin >> Y >> X;
	int map[9][9];

	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			cin >> map[i][j];
		}
	}

	SqQueue sq;
	initqueue(sq);

	int num = 0;
	QElemType value;

	for (int i = 1; i < Y - 1; i++) {
		for (int j = 1; j < X - 1; j++) {
			if (map[i][j] == 1) {
				num++;
				value.x = j;
				value.y = i;

				map[i][j] = 0;
				enqueue(sq, value);

				while (1) {
					if (j + 1 < Y&&map[i][j + 1] == 1) {
						value.x = ++j;
						value.y = i;

						map[i][j] = 0;
						enqueue(sq, value);
					}
					else if (i + 1 < X&&map[i + 1][j] == 1) {
						value.x = j;
						value.y = ++i;

						map[i][j] = 0;
						enqueue(sq, value);
					}
					else {
						dequeue(sq, value);
						j = value.x;
						i = value.y;
					}

					if (queque_empty(sq))
						break;
				}
			}

		}
	}
	cout << num << endl;
	return 1;
}


int main()
{
	
	scanfmap();

	return 0;
}