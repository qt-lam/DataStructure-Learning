//��������ĺϲ�

#include <iostream>
using namespace std;


typedef int ElemType;

typedef struct Node {
	ElemType  data;
	Node  *next;
}Node, *LinkList;//��㣬ͷָ��


//β�巨��ÿ�ξ���ǰ���������Ԫ��
//�ı�汾��������Ԫ�ظ�����������0�������
int creatlist(LinkList& L) {
	Node* s;

	int value = 0;
	int length = 0;//����
	L = (LinkList)malloc(sizeof(Node));//����ͷ���
	L->next = NULL;
	L->data = 0;//ͷ���������洢������

	//cin >> length;//��ȡ����ʱ����ĳ���
	//L->data = length;

	Node* p = L;
	while(1) {
		cin >> value;
		if (value == 0)
			break;
		s = (Node *)(malloc)(sizeof(Node));  //return 0 waiting
		
		s->data = value;
		s->next = NULL;
		length++;

		p->next = s;
		p = s;
	}

	L->data = length;
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

//ɾ�������������ͷ��ڴ�
void freelist(LinkList &L) {
	Node* q = L;
	Node* p = NULL;
	while (q != NULL) {
		p = q->next;
		free(q);
		q = p;
	}
}

//���շǵݼ�������������
void sortlist(LinkList&L) {
	Node* p = NULL;
	Node* q = NULL;

	int min = 0;

	for (p = L->next; p != NULL; p = p->next) {
		min = p->data;
		for (q = p->next; q != NULL; q = q->next) {
			if (q->data < min) {
				min = q->data;
				q->data = p->data;
				p->data = min;
			}
		}
	}
}

void mergelist(LinkList& a, LinkList& b, LinkList& c) {
	Node* pa = a->next;
	Node* pb = b->next;
	Node * pc = c = a;//ͷ���
	c->data = a->data + b->data;//�������;

	while (pa&&pb) {
		if (pa->data <= pb->data) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}	
	}
	pc->next = pa ? pa : pb;
	free(b);
}

int main() {
	LinkList a;
	LinkList b;
	LinkList c;

	creatlist(a);
	creatlist(b);

	sortlist(a);
	sortlist(b);

	mergelist(a, b, c);
	printlist(c);

	freelist(c);

	return 0;
}