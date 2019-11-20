//�����ۺ�


#include <iostream>
#include <string.h>
using namespace std;

typedef int QElemType;

typedef struct {
	QElemType* base;//���������ڴ�Ļ�ַ��ַ
	int front;//����
	int rear;//��β
	int maxsize;//�ö��е�����������Լ����
	int nowsize;//��ǰ����
}SqQueue;

//���� initqueue
//���� ��ʼ������һ���¶���
//ʵ�� �������л�ȡ�������������������ʱ�ڴ˻���������һ��Ԫ�ص�λ�ռ����������Ϳ�
int initqueue(SqQueue& Q,int size) {

	//cin >> Q.maxsize;//�������л�ȡ���ֵ
	Q.maxsize = size;
	Q.maxsize++;//�ճ�һ��λ�����������Ϳ�

	Q.base = (QElemType*)malloc(sizeof(QElemType)*Q.maxsize);
	if (Q.base == NULL)
		return 0;//��ʼ��ʧ��

	Q.front = Q.rear = 0;//һ��ʼ����0
	Q.nowsize = 0;//��ǰΪ�ն���
	return 1;
}

//���� deletequeue
//���� �ͷŶ��пռ䣬����������
//ʵ�� ������Ļ���ַ�ͷ��ڴ�
void deletequeue(SqQueue& Q) {
	free(Q.base);
}

//���� clearqueue
//���� ��������գ���ɿն���
//ʵ�� ���ͷ��β������0��ʵ����ն���
void clearqueue(SqQueue& Q) {
	Q.front = Q.rear = 0;
	Q.nowsize = 0;
}

//���� emptyqueue
//���� �ж϶����Ƿ�Ϊ�գ����򷵻�1
//ʵ�� ͨ��ͷ�Ƿ����β�ж�
int emptyqueue(SqQueue& Q) {
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}

//���� fullqueue
//���� �ж϶����Ƿ�Ϊ�������򷵻�1
int fullqueue(SqQueue &Q) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)
		return 1;
	else
		return 0;
}

//���� returnsize
//���� ���ض����ڵ�Ԫ�ظ���
//ʵ�� ����Q.nowsize
int returnsize(SqQueue& Q) {
	return Q.nowsize;
}

//���� enqueue
//���� �ڶ����м���һ��Ԫ�أ���ӣ�������1������ɹ�������0�����
//ʵ�� ��βָ��ָ��Ŀռ��в���Ԫ�أ�βָ����+1ѭ��
int enqueue(SqQueue& Q, QElemType e) {
	if ((Q.rear + 1) % Q.maxsize == Q.front)//�±�+1
		return 0;//�����Ѿ����ˣ�����ʧ��

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	Q.nowsize++;
	return 1;//�ɹ� 
}

//���� dequeue
//���� ����ͷԪ�ص������У����ӣ�,����1������ɹ�������0��ӿ�ʧ��
//ʵ�� ��ȡͷָ��ָ��Ԫ�أ���ͷָ��+1ѭ��
int dequeue(SqQueue& Q, QElemType& e) {
	if (Q.front == Q.rear)
		return 0;//��

	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % Q.maxsize;
	Q.nowsize--;
	return 1;
}


//���� printqueue
//���� �Ӷ�ͷ����β�������е�Ԫ���������
//ʵ�� ֻҪ�Ӳ�Ϊ�վ�����ͷָ��ָ���Ԫ�أ���ͷָ��++
void printqueue(SqQueue& Q) {
	while (1) {
		if (Q.front == Q.rear)
			break;//�Ѿ���

		cout << Q.base[Q.front] << ' ';

		Q.front = (Q.front + 1) % Q.maxsize;
	}
	cout << endl;
}

//���� simulation
//���� ģ����Ϣ���У��������ģ
void simulation() {
	SqQueue severA, severB;//��������A/B ����ܴ���ʮ�����󣨼򻯹�ģ��
	SqQueue mes;//��Ϣ������������ݶ�100

	initqueue(severA, 10);
	initqueue(severB, 10);
	initqueue(mes, 100);

	QElemType e;

	cout << "��ʼ��ģ����Ϣ���еĹ���" << endl;
	cout << "����������/��Ϣ���������������������ͬ����,�����-1������" << endl;
	while (1) {
		cin >> e;
		if (e == -1)
			break;

		enqueue(mes, e);
	}
	cout << "�趨Ϊ��ǰһ���ڽ��ܵ�" << mes.nowsize << "�����󣬴洢����Ϣ������" << endl;
	cout << "�������ɷ���������Ϣ�����л�ȡ" << endl;

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
		 
		cout << "���ι���A������������" << severA.nowsize << "������,B������������" << severB.nowsize << "������" << endl;
		clearqueue(severA);//������Ϣ��������շ���������
		clearqueue(severB);//������Ϣ��������շ���������

		if (emptyqueue(mes)) {
			cout << "���������Ѵ���" << endl;
			break;
		}
		else {
			cout << "��" << second << "�봦������ѽ�������Ϣ�����л�ʣ" << mes.nowsize << "������" << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
		}

		second++;		
	}

}

int main() {
	simulation();
	return 0;
}