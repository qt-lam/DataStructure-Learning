//һԪ����ʽ�����
//Ӧ��ͬ����ǵ���˳��

#include <iostream>
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

//����һԪ����ʽab ��˵�c��c��δ�����ʼ��������,����˳��,ab�����ܵ�Ӱ�죬û���ͷ�
//Ч�ʽϲ�
void mulitlist(HeadNodeP& a, HeadNodeP& b, HeadNodeP& c) {
	Node* pa = a->next;
	Node* pb = b->next;
	Node* pc = c = (Node*)malloc(sizeof(Node));
	pc->next = NULL;

	Node* s = NULL;
	Node* ppa;
	Node* ppc;

	//�ȶ��ڸ�����ˣ���δ���������
	for (pa = a->next; pa != NULL; pa = pa->next) {
		for (pb = b->next; pb != NULL; pb = pb->next) {
			s = (Node*)malloc(sizeof(Node));
			s->ei = pa->ei + pb->ei;
			s->pi = pa->pi*pb->pi;
			pc->next = s;
			s->next = NULL;
			pc = pc->next;
		}
	}
	
	//��һ���ض���ָ����С�ģ������ظ�
	ppc = c->next;
	pc = (c->next)->next;
	while (pc) {
		ppa = pc;
		pa = pc->next;
		while (pa) {
			if (pa->ei < pc->ei) {
				int k = 0;
				k = pc->ei;
				pc->ei = pa->ei;
				pa->ei = k;

				k = pc->pi;
				pc->pi = pa->pi;
				pa->pi = k;
			}
			else if (pa->ei == pc->ei) {
				pc->pi += pa->pi;
				//���û����ȵģ�
				/*if (pc->pi == 0) {
					ppc->next = pc->next;
					pb = pc;
					pc = pc->next;
					free(pb);

					ppa->next = pa->next;
					pb = pa;
					pa = pa->next;
					free(pb);
				}*/
				ppa->next = pa->next;
				pb = pa;
				pa = pa->next;
				free(pb);
				continue;
			}
			ppa = ppa->next;
			pa = pa->next;
		}
		ppc = ppc->next;
		pc = pc->next;
	}



}

//�������Ԫ��
void printlist(HeadNodeP& L) {
	Node* p = L->next;
	for (p; p != NULL; p = p->next) {
		cout << p->pi << ' ' << p->ei << endl;
	}
}

int main() {
	HeadNodeP a;
	HeadNodeP b;
	HeadNodeP c;
	creatlist(a);
	creatlist(b);

	/*cout << endl;
	printlist(a);
	printlist(b);*/

	mulitlist(a, b, c);
	/*cout << endl;*/
	printlist(c);
	return 0;
}