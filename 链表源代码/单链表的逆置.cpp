//链表的基本操作
#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct Node {
	ElemType  data;
	Node  *next;
}Node, *LinkList;//结点，头指针


//头插法，每次均在头结点后插入新元素
int creatlist(LinkList& L) {
	Node* s;
	int length = 0;//长度
	L = (LinkList)malloc(sizeof(Node));//创建头结点
	L->next = NULL;
	L->data = 0;//头结点数据域存储链表长度

	cin >> length;//获取创建时链表的长度
	L->data = length;

	for (int i = 0; i < length; i++) {
		s = (Node *)(malloc)(sizeof(Node));  //return 0 waiting
		cin >> s->data;
		s->next = L->next;
		L->next = s;
	}
	return 1;
}

//输出链表的所有元素
void printlist(LinkList& L) {
	Node* p;
	for (p = L->next; p != NULL; p = p->next) {
		cout << p->data << ' ';
	}
	cout << endl;
}

//单链表的逆置
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
			length = L->data;//保留长度数据
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