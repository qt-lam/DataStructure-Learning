//队列的应用-矩阵


#include <iostream>
#include <string.h>
using namespace std;


struct point {
	int x;
	int y;
};

typedef point QElemType;

typedef struct {
	QElemType* base;//用来申请内存的基址地址
	int front;//队首
	int rear;//队尾
	int maxsize;//该队列的最大容量（自己添加

}SqQueue;

//构造队列，最大容量外界获取
int initqueue(SqQueue& Q) {

	//cin >> Q.maxsize;

	Q.maxsize = 10000;
	Q.maxsize++;//空出一个位置来区分满和空

	Q.base = (QElemType*)malloc(sizeof(QElemType)*Q.maxsize);
	if (Q.base == NULL)
		return 0;//初始化失败

	Q.front = Q.rear = 0;//一开始都在0
	return 1;
}

//插入队尾
int enqueue(SqQueue& Q, QElemType e) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)//下标+1
		return 0;//队列已经满了，插入失败

	Q.base[Q.rear*2] = e;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	return 1;//成功 
}

//出队
int dequeue(SqQueue& Q, QElemType& e) {
	if (Q.front == Q.rear)
		return 0;//空

	e = Q.base[Q.front*2];
	Q.front = (Q.front + 1) % Q.maxsize;
	return 1;
}

int queque_empty(SqQueue& Q) {
	if (Q.front == Q.rear)
		return 1;//空
	return 0;
}


//事实上用堆栈更简单？
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