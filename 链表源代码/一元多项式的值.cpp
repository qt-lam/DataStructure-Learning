//һԪ����ʽ��ֵ
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

typedef int elemtype;

typedef struct linklist {
	elemtype pi;
	elemtype ei;
	linklist* next;
}Node, *HeadNodeP;

//β�巨������˳��Ϊ������Ҫ��ָ������
int creatlist(HeadNodeP& L) {
	L = (HeadNodeP)malloc(sizeof(Node));
	//ͷ����ʼ��
	L->ei = -1;
	L->pi = -1;
	L->next = NULL;

	//��ȡ��ʼ��������Ŀ
	int length = 0;
	cin >> length;

	Node* s;
	Node* p = L;
	for (int i = 0; i < length; i++) {
		s = (Node*)malloc(sizeof(Node));
		cin >> s->pi >> s->ei;
		s->next = p->next;
		p->next = s;
		p = s;
	}

	return 1;
}

//�������Ԫ��
void printlist(HeadNodeP& L) {
	Node* p = L->next;
	for (p; p != NULL; p = p->next) {
		cout << p->pi << ' ' << p->ei << endl;
	}
}


//������ֵ��ֵ�ں����ڻ�ȡ
double clalist(HeadNodeP& a) {
	double x = 0;
	double value = 0;
	cin >> x;
	Node* s = a->next;
	while (s != NULL) {
		value = value + pow(x, s->ei)*s->pi;
		s = s->next;
	}

	return value;
}

int main() {
	double value = 0;
	HeadNodeP a;
	creatlist(a);
	value=clalist(a);

	cout << setiosflags(ios::fixed) << setprecision(1) << value << endl;
	return 0;
}