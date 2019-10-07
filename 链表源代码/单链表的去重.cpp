//单链表的去重
#include <iostream>
using namespace std;


typedef int ElemType;

typedef struct Node {
	ElemType  data;
	Node  *next;
}Node, *LinkList;//结点，头指针


//尾插法，每次均当前结点后插入新元素
int creatlist(LinkList& L) {
	Node* s;
	

	int length = 0;//长度
	L = (LinkList)malloc(sizeof(Node));//创建头结点
	L->next = NULL;
	L->data = 0;//头结点数据域存储链表长度

	cin >> length;//获取创建时链表的长度
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

//输出链表的所有元素
void printlist(LinkList& L) {
	Node* p;
	for (p = L->next; p != NULL; p = p->next) {
		cout << p->data << ' ';
	}
	cout << endl;
}

//去重单链表
void quchong(LinkList& L) {
	Node* ppre = NULL;//前结点
	Node* pcur = NULL;//当前结点
	Node* pnext = NULL;//后结点
	Node *pflag = NULL;//所要比较的结点

	//从第一个开始比较
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



int main() {
	LinkList L;
	creatlist(L);
	quchong(L);
	printlist(L);
	freelist(L);
	return 0;
}