//ջ�Ļ�������
//ջ��Ҫ��˳��ջ������ջ������ʹ��˳��ջʵ��ջ�Ļ���caoz

#include <iostream>
#include <string.h>
using namespace std;


typedef int selemtype;

//��ջ
typedef struct {
	selemtype* base;
	selemtype* top;
	int stacksize;
}SqStack;

//��ʼ����ջ,��ʼ��������������л�ȡ
int initstack(SqStack& L) {
	int maxsize = 0;
	cin >> maxsize;

	L.stacksize = maxsize;//�������
	L.base = L.top = (selemtype*)malloc(sizeof(selemtype)*L.stacksize);//һ��ʼջ������ջ��
	if (L.base == NULL)
		return 0;//����ʧ��
	return 1;
}


//�ж�ջ�Ƿ�Ϊ�գ��Ƿ���1�����Ƿ���0
int stackepmty(SqStack& L) {
	if (L.top == L.base)
		return 1;//ջ������ջ��
	else
		return 0;//�ǿ�
}

//�ж�ջ�Ƿ�Ϊ�����Ƿ���1�����Ƿ���0
int stackfull(SqStack& L) {
	if (L.base + L.stacksize == L.top)//ջ��ָ�����һ��λ�ó����Ķ�ջ���ڴ淶Χ
		return 1;
	else
		return 0;
}

//��ֵvalueѹջ������1������ɹ�������0��ջ��ʧ��
int stackpush(SqStack& L,int& value) {
	if (stackfull(L) == 0) {
		*L.top = value;
		L.top++;
		return 1;//�ɹ�
	}
	else
		return 0;//ʧ��
	
}

//��ջ����ֵ����value������1������ɹ�������0��ջ��ʧ��
int stackpop(SqStack& L, int& value) {
	if (stackepmty(L) == 0) {
		L.top--;
		value = *L.top;
		return 1;//�ɹ�
	}
	else {
		return 0;//ʧ��
	}
}

//���ջ������Ԫ��
void printstack(SqStack& L) {
	selemtype* p = L.top;

	while (p != L.base) {
		p--;
		cout << *p << ' ';
	}
	cout << endl;
}

//��ȡ�ַ��������ջ����1����ջ����2���������3�������Ƿ���0
int chooseact() {
	char order[10];
	cin >> order;//��ȡ��ջ����ջ�����������

	if (strcmp(order, "push") == 0)
		return 1;
	else if (strcmp(order, "pop") == 0)
		return 2;
	else if (strcmp(order, "quit") == 0)
		return 3;
	
	return 0;
}

void freestack(SqStack& L) {
	free(L.base);
}

int main() {
	SqStack L;
	initstack(L);

	int value = 0;
	int act = 0;
	int k = 0;
	while (1) {
		act = chooseact();
		if (act == 1) {
			cin >> value;
			k = stackpush(L, value);
			if (k == 0)
				cout << "Stack is Full" << endl;
		}
		else if (act == 2) {
			k = stackpop(L, value);
			if (k == 0)
				cout << "Stack is Empty" << endl;
			else
				cout << value << endl;			
		}
		else if (act == 3) {
			printstack(L);
			break;
		}
	}

	freestack(L);
	return 0;
}