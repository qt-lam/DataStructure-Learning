//有序链表的合并

#include <iostream>
using namespace std;


typedef int ElemType;

typedef struct Node {
	ElemType  data;
	Node  *next;
}Node, *LinkList;//结点，头指针


//尾插法，每次均当前结点后插入新元素
//改变版本：不输入元素个数，而是以0代表结束
int creatlist(LinkList& L) {
	Node* s;

	int value = 0;
	int length = 0;//长度
	L = (LinkList)malloc(sizeof(Node));//创建头结点
	L->next = NULL;
	L->data = 0;//头结点数据域存储链表长度

	//cin >> length;//获取创建时链表的长度
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

//输出链表的所有元素
void printlist(LinkList& L) {
	Node* p;
	for (p = L->next; p != NULL; p = p->next) {
		cout << p->data << ' ';
	}
	cout << endl;
}

//删除整个单链表，释放内存
void freelist(LinkList &L) {
	Node* q = L;
	Node* p = NULL;
	while (q != NULL) {
		p = q->next;
		free(q);
		q = p;
	}
}

//按照非递减重新排序链表
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
	Node * pc = c = a;//头结点
	c->data = a->data + b->data;//长度相加;

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