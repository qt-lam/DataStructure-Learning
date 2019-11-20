//ջģ��ݹ����
#include <iostream>
#include <string.h>
using namespace std;

const int maxsize = 50;//��ջ����������ݶ�50

//ģ��ݹ��еı���¼�ھֲ������洢������Ϣ����ջ�Ļ���Ԫ�ؽṹ
typedef struct {
	int n; //�������������
	//��������getter��setter
}Data;


//��ջ�Ļ����ṹ
typedef struct {
	Data* base;
	Data* top;
	int stacksize;
}SqStack;

//��ʼ����ջ,��ʼ��������������л�ȡ
int initstack(SqStack& L) {

	L.stacksize = maxsize;//�������
	L.base = L.top = (Data*)malloc(sizeof(Data)*L.stacksize);//һ��ʼջ������ջ��
	if (L.base == NULL)
		return 0;//����ʧ��
	return 1;
}

//�ж�ջ�Ƿ�Ϊ�գ��Ƿ���1�����Ƿ���0
int stackempty(SqStack& L) {
	if (L.top == L.base)
		return 1;//ջ������ջ��
	else
		return 0;//�ǿ�
}

//���� stackfull
//���� �ж�ջ�Ƿ�Ϊ�����Ƿ���1�����Ƿ���0
int stackfull(SqStack& L) {
	if (L.base + L.stacksize == L.top)//ջ��ָ�����һ��λ�ó����Ķ�ջ���ڴ淶Χ
		return 1;
	else
		return 0;
}


//���� stackpush
//���� ��Ԫ��valueѹջ������1������ɹ�������0��ջ��ʧ��
int stackpush(SqStack& L, Data value) {
	if (stackfull(L) == 0) {
		*L.top = value;
		L.top++;
		return 1;//�ɹ�
	}
	else
		return 0;//ʧ��

}

//���� stackpop
//���� ��ջ��Ԫ�س�ջ������value������1������ɹ�������0��ջ��ʧ��
int stackpop(SqStack& L, Data& value) {
	if (stackempty(L) == 0) {
		L.top--;
		value = *L.top;
		return 1;//�ɹ�
	}
	else {
		return 0;//ʧ��
	}
}

//���� simulation
//���� ʹ��ջ��ģ��n�׳˵ĵݹ����
int simulation(int n) {
	//�൱��main�����ڣ���δ��ʼ���á��ݹ顱
	SqStack L;
	initstack(L);

	Data element;

	element.n = n;//��ʼ����

	while (element.n > 1) {
		//��ʽ����ݹ麯��
		stackpush(L, element);//�������ͷ��صĵ�ַѹ��ջ
		element.n--;//n-1		
	}
	int sum = 1;
	//�ݹ麯����ʼ����
	while (!stackempty(L)) {
		stackpop(L, element);
		sum = sum * element.n;		
	}

	cout << sum << endl;
	return 1;
}

int main() {

	simulation(1000000000);

	return 0;
}
