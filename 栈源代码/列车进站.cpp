//�г����� ��ջ�����

#include <iostream>
#include <string.h>
using namespace std;

const int maxsize = 50;//��ʱ�趨��ջ���������50

typedef char selemtype;//������Ҫ���ַ�����

//��ջ
typedef struct {
	selemtype* base;
	selemtype* top;
	int stacksize;
}SqStack;

//��ʼ����ջ,��ʼ��������Ѿ�����
int initstack(SqStack& L) {
	
	

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
int stackpush(SqStack& L, selemtype value) {
	if (stackfull(L) == 0) {
		*L.top = value;
		L.top++;
		return 1;//�ɹ�
	}
	else
		return 0;//ʧ��

}

//��ջ����ֵ����value������1������ɹ�������0��ջ��ʧ��
int stackpop(SqStack& L, selemtype& value) {
	if (stackepmty(L) == 0) {
		L.top--;
		value = *L.top;
		return 1;//�ɹ�
	}
	else {
		return 0;//ʧ��
	}
}

//���ջ��Ԫ��ֵ
selemtype gettop(SqStack& L) {
	return *(L.top - 1);
}

//�����ַ������ж��Ƿ���ʵ�ָ�˳��
int carproblem(char* outcar,char* car) {
	SqStack in_car,station,out_car;//��վǰ��˳��ջ����վջ����վ��ʵ�ʵ�˳��ջ
	initstack(station);
	initstack(in_car);
	initstack(out_car);
	int length = strlen(car);

	for (int i = length - 1; i >= 0; i--) 
		stackpush(in_car, car[i]);
	
	char c;
	
	for (int i = 0; i < length; i++) {
		c = outcar[i];
		char temp;
		int k = 0;

		while (1) {
			if (stackepmty(in_car)) {
				for (k; k > 0; k--) {
					stackpop(station, temp);
					stackpush(in_car, temp);
				}
				if (gettop(station) != outcar[i])
					return 0; 
				else {
					stackpop(station, temp);
					break;
				}
			}
			else if (gettop(in_car) != c) {
				stackpop(in_car, temp);
				stackpush(station, temp);
				k++;
			}			
			else if(gettop(in_car) == c) {
				stackpop(in_car, temp);
				stackpush(out_car, temp);
				break;
			}
		}
	}
	return 1;
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

int main()
{
	char car[maxsize];//���50
	cin >> car;

	char detemine[maxsize];
	int k = 0;
	while (cin >> detemine) {
		k = carproblem(detemine, car);
		if (k == 0)
			cout << "no" << endl;
		else if (k == 1)
			cout << "yes" << endl;
	}

	return 0;
}