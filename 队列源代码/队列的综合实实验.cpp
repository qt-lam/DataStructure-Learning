//队列综合


#include <iostream>
#include <string.h>
using namespace std;

typedef int QElemType;

typedef struct {
	QElemType* base;//用来申请内存的基址地址
	int front;//队首
	int rear;//队尾
	int maxsize;//该队列的最大容量（自己添加
	int nowsize;//当前容量
}SqQueue;

//函数 initqueue
//功能 初始化建立一个新队列
//实现 从输入中获取最大容量，并且再申请时在此基础多申请一个元素单位空间来区分满和空
int initqueue(SqQueue& Q,int size) {

	//cin >> Q.maxsize;//从输入中获取最大值
	Q.maxsize = size;
	Q.maxsize++;//空出一个位置来区分满和空

	Q.base = (QElemType*)malloc(sizeof(QElemType)*Q.maxsize);
	if (Q.base == NULL)
		return 0;//初始化失败

	Q.front = Q.rear = 0;//一开始都在0
	Q.nowsize = 0;//当前为空队列
	return 1;
}

//函数 deletequeue
//功能 释放队列空间，将队列销毁
//实现 对申请的基地址释放内存
void deletequeue(SqQueue& Q) {
	free(Q.base);
}

//函数 clearqueue
//功能 将队列清空，变成空队列
//实现 令表头表尾都等于0，实现清空对列
void clearqueue(SqQueue& Q) {
	Q.front = Q.rear = 0;
	Q.nowsize = 0;
}

//函数 emptyqueue
//功能 判断队列是否为空，是则返回1
//实现 通过头是否等于尾判断
int emptyqueue(SqQueue& Q) {
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}

//函数 fullqueue
//功能 判断队列是否为满，是则返回1
int fullqueue(SqQueue &Q) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)
		return 1;
	else
		return 0;
}

//函数 returnsize
//功能 返回队列内的元素个数
//实现 返回Q.nowsize
int returnsize(SqQueue& Q) {
	return Q.nowsize;
}

//函数 enqueue
//功能 在队列中加入一个元素（入队），返回1则操作成功，返回0则队满
//实现 在尾指针指向的空间中插入元素，尾指针再+1循环
int enqueue(SqQueue& Q, QElemType e) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)//下标+1
		return 0;//队列已经满了，插入失败

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	Q.nowsize++;
	return 1;//成功 
}

//函数 dequeue
//功能 将队头元素弹出队列（出队）,返回1则操作成功，返回0则队空失败
//实现 获取头指针指向元素，再头指针+1循环
int dequeue(SqQueue& Q, QElemType& e) {
	if (Q.front == Q.rear)
		return 0;//空

	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % Q.maxsize;
	Q.nowsize--;
	return 1;
}


//函数 printqueue
//功能 从队头到队尾将队列中的元素依次输出
//实现 只要队不为空就输入头指针指向的元素，且头指针++
void printqueue(SqQueue& Q) {
	while (1) {
		if (Q.front == Q.rear)
			break;//已经空

		cout << Q.base[Q.front] << ' ';

		Q.front = (Q.front + 1) % Q.maxsize;
	}
	cout << endl;
}

//函数 simulation
//功能 模拟消息队列，简化问题规模
void simulation() {
	SqQueue severA, severB;//服务器端A/B 最多能处理十个请求（简化规模）
	SqQueue mes;//消息队列最大限制暂定100

	initqueue(severA, 10);
	initqueue(severB, 10);
	initqueue(mes, 100);

	QElemType e;

	cout << "开始简单模拟消息队列的过程" << endl;
	cout << "请输入请求/信息（输入任意个数整数代表不同请求,最后以-1结束）" << endl;
	while (1) {
		cin >> e;
		if (e == -1)
			break;

		enqueue(mes, e);
	}
	cout << "设定为当前一秒内接受到" << mes.nowsize << "个请求，存储到消息队列中" << endl;
	cout << "接下来由服务器到消息队列中获取" << endl;

	cout << "-----------------------------------------------------------------------" << endl;

	int second = 1;

	while (1) {
		while (1) {
			if (emptyqueue(mes) || fullqueue(severA))
				break;

			dequeue(mes, e);
			enqueue(severA, e);
		}

		while (1) {
			if (emptyqueue(mes) || fullqueue(severB))
				break;

			dequeue(mes, e);
			enqueue(severB, e);
		}
		 
		cout << "本次过程A服务器处理了" << severA.nowsize << "条请求,B服务器处理了" << severB.nowsize << "条请求" << endl;
		clearqueue(severA);//处理消息结束，清空服务器队列
		clearqueue(severB);//处理消息结束，清空服务器队列

		if (emptyqueue(mes)) {
			cout << "所有请求已处理" << endl;
			break;
		}
		else {
			cout << "第" << second << "秒处理过程已结束，消息队列中还剩" << mes.nowsize << "条请求" << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
		}

		second++;		
	}

}

int main() {
	simulation();
	return 0;
}