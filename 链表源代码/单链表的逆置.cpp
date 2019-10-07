//����Ļ�������
#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct Node {
	ElemType  data;
	Node  *next;
}Node, *LinkList;//��㣬ͷָ��


//ͷ�巨��ÿ�ξ���ͷ���������Ԫ��
int creatlist(LinkList& L) {
	Node* s;
	int length = 0;//����
	L = (LinkList)malloc(sizeof(Node));//����ͷ���
	L->next = NULL;
	L->data = 0;//ͷ���������洢������

	cin >> length;//��ȡ����ʱ����ĳ���
	L->data = length;

	for (int i = 0; i < length; i++) {
		s = (Node *)(malloc)(sizeof(Node));  //return 0 waiting
		cin >> s->data;
		s->next = L->next;
		L->next = s;
	}
	return 1;
}

//������������Ԫ��
void printlist(LinkList& L) {
	Node* p;
	for (p = L->next; p != NULL; p = p->next) {
		cout << p->data << ' ';
	}
	cout << endl;
}

//�����������
void reverselist(LinkList& L) {
	Node* ppre = L;
	Node* pcur = L->next;
	Node* pnext = NULL;
	int length = 0;

	while (pcur != NULL) {
		pnext = pcur->next;
		pcur->next = ppre;
		if (ppre == L) {
			pcur->next = NULL;
			length = L->data;//������������
			free(L);
		}
		ppre = pcur;
		pcur = pnext;
	}

	Node* s = (Node*)malloc(sizeof(Node));
	s->next = ppre;
	s->data = length;
	L = s;
}

void freelist(LinkList &L) {
	Node* q = L;
	Node* p = NULL;
	while (q != NULL) {
		p = q->next;
		free(q);
		q = p;
	}
}

void print3(LinkList &L) {
	Node* p = L->next;
	for (p; p != NULL; p = p->next) {
		if (p->data % 3 == 0)
			cout << p->data << ' ';
	}
	cout << endl;
}

int main()
{
	LinkList L;
	creatlist(L);
	printlist(L);
	reverselist(L);
	print3(L);

	freelist(L);
	return 0;
}