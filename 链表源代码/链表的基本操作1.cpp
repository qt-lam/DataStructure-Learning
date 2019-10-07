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
	for (p = L->next;p!=NULL ;p=p->next ) {
		cout << p->data << ' ';
	}
	cout << endl;
}

//插入一个元素
int insertlist(LinkList& L) {
	int value;//待插入的值
	int position;//插入的位置
	cin >> position >> value;

	if (position<1 || position>L->data + 1)
		return 0;//插入位置不合法

	//插入操作一定要获得i-1个结点，循环过程的中间量只是过客，只有改变指针域才是出路
	Node* p = L;//指向头结点

	//循环结束时p指向第position-1个结点
	for (int i = 0; i < position-1; i++) 
		p = p->next;
	
	Node* s = (Node*)malloc(sizeof(Node));
	s->next = p->next;
	p->next = s;
	s->data = value;

	L->data++; //链表长度增加
	return 1;
}


int deletelist(LinkList &L) {
	int position;//待删除的位置
	cin >> position;
	if (position<1 || position>L->data)
		return 0;//位置不合法

	Node* p = L;//指向头结点

	//循环结束时p指向第position-1个结点
	for (int i = 0; i < position - 1; i++)
		p = p->next;

	Node* q = p->next;
	p->next = (p->next)->next;
	free(q);//释放内存
	L->data--;//长度减少
	return 1;

}

int findlist(LinkList& L) {
	int value;//待查询的值
	cin >> value;

	Node* p = L->next;//指向第一个结点
	int i = 1;
	for (p; p != NULL; p = p->next) {
		if (p->data == value) {
			cout << i << endl;//相减即是位置
			return 1;//成功找寻
		}
		i++;
	}
	return 0;//没查找到
}

void lengthoflist(LinkList &L) {
	cout << L->data << endl;
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

int main()
{
	LinkList L;
	creatlist(L);
	printlist(L);

	int k = insertlist(L);
	if (k == 1)
		printlist(L);
	else if (k == 0)
		cout << -1 << endl;

	k = deletelist(L);
	if (k == 1)
		printlist(L);
	else if (k == 0)
		cout << -1 << endl;

	k = findlist(L);
	if (k == 0)
		cout << -1 << endl;

	lengthoflist(L);

	freelist(L);

	return 0;
}