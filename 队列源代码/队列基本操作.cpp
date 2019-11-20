//循环队列的实现以及基本操作

#include <iostream>
#include <string.h>
using namespace std;

typedef int QElemType ;

typedef struct {
	QElemType* base;//用来申请内存的基址地址
	int front;//队首
	int rear;//队尾
	int maxsize;//该队列的最大容量（自己添加

}SqQueue;

//构造队列，最大容量外界获取
int initqueue(SqQueue& Q) {

	cin >> Q.maxsize;

	Q.maxsize++;//空出一个位置来区分满和空

	Q.base = (QElemType*)malloc(sizeof(QElemType)*Q.maxsize);
	if (Q.base == NULL)
		return 0;//初始化失败

	Q.front = Q.rear = 0;//一开始都在0
	return 1;
}

//插入队尾
int enqueue(SqQueue& Q,QElemType e) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)//下标+1
		return 0;//队列已经满了，插入失败

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	return 1;//成功 
}

//出队
int dequeue(SqQueue& Q, QElemType& e) {
	if (Q.front == Q.rear)
		return 0;//空

	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % Q.maxsize;
	return 1;
}


//输出所有元素
void printqueue(SqQueue& Q) {
	while (1) {
		if (Q.front == Q.rear)
			break;//已经空

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