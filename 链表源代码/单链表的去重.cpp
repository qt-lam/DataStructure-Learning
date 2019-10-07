//�������ȥ��
#include <iostream>
using namespace std;


typedef int ElemType;

typedef struct Node {
	ElemType  data;
	Node  *next;
}Node, *LinkList;//��㣬ͷָ��


//β�巨��ÿ�ξ���ǰ���������Ԫ��
int creatlist(LinkList& L) {
	Node* s;
	

	int length = 0;//����
	L = (LinkList)malloc(sizeof(Node));//����ͷ���
	L->next = NULL;
	L->data = 0;//ͷ���������洢������

	cin >> length;//��ȡ����ʱ����ĳ���
	L->data = length;

	Node* p = L;
	for (int i = 0; i < length; i++) {
		s = (Node *)(malloc)(sizeof(Node));  //return 0 waiting
		cin >> s->data;
		s->next = NULL;
		p->next = s;
		p = s;
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

//ȥ�ص�����
void quchong(LinkList& L) {
	Node* ppre = NULL;//ǰ���
	Node* pcur = NULL;//��ǰ���
	Node* pnext = NULL;//����
	Node *pflag = NULL;//��Ҫ�ȽϵĽ��

	//�ӵ�һ����ʼ�Ƚ�
	for (pflag = L->next; pflag != NULL; pflag = pflag->next) {

		pcur = pflag->next;
		ppre = pflag;

		while (pcur != NULL) {
			pnext = pcur->next;
			if (pcur->data == pflag->data) {
				ppre->next = pnext;
				free(pcur);
				pcur = pnext;
			}
			else {
				ppre = ppre->next;
				pcur = pcur->next;
			}		
		}
	}
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



int main() {
	LinkList L;
	creatlist(L);
	quchong(L);
	printlist(L);
	freelist(L);
	return 0;
}