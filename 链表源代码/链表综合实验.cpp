//链表的基本操作
#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct Node {
	ElemType  data;
	Node  *next ;
}Node, *LinkList;//结点，头指针


//尾插法，每次均当前结点后插入新元素 for function9
//改变版本：不输入元素个数，而是以0代表结束
int creatlist9(LinkList& L) {
	Node* s;

	int value = 0;
	int length = 0;//长度
	L = (LinkList)malloc(sizeof(Node));//创建头结点
	L->next = NULL;
	L->data = 0;//头结点数据域存储链表长度

	//cin >> length;//获取创建时链表的长度
	//L->data = length;

	Node* p = L;
	while (1) {
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

//头插法，每次均在头结点后插入新元素
int creatlist(LinkList& L) {
	Node* s;
	int length = 0;//长度
	L = (LinkList)malloc(sizeof(Node));//创建头结点
	L->next = NULL;
	L->data = 0;//头结点数据域存储链表长度

	cout << "功能1" << endl;
	cout << "请输入要创建的链表长度" << endl;
	cin >> length;//获取创建时链表的长度
	L->data = length;

	cout << "请依次输入数据元素" << endl;
	for (int i = 0; i < length; i++) {
		s = (Node *)(malloc)(sizeof(Node));  
		if (s == NULL) {
			cout << "创建失败" << endl;
			return 0;
		}
		//return 0 waiting
		cin >> s->data;
		s->next = L->next;
		L->next = s;
	}
	return 1;
}

//输出链表的所有元素
void printlist(LinkList& L) {

	Node* p;

	cout << "功能2" << '\n' << "所有信息如下" << endl;

	for (p = L->next; p != NULL; p = p->next) {
		cout << p->data << ' ';
	}
	cout << endl;
}

//插入一个元素,函数内获取元素值
int insertlist(LinkList& L) {
	int value;//待插入的值
	int position;//插入的位置

	cout << "功能3" << '\n' << "请输入要插入的位置和数据值" << endl;
	
	cin >> position >> value;

	if (position<1 || position>L->data + 1) {
		cout << "位置不合法" << endl;
		return 0;//插入位置不合法
	}

	//插入操作一定要获得i-1个结点，循环过程的中间量只是过客，只有改变指针域才是出路
	Node* p = L;//指向头结点

	//循环结束时p指向第position-1个结点
	for (int i = 0; i < position - 1; i++)
		p = p->next;

	Node* s = (Node*)malloc(sizeof(Node));
	s->next = p->next;
	p->next = s;
	s->data = value;

	L->data++; //链表长度增加
	return 1;
}

//删除一个元素，函数内获取要删除的位置
int deletelist(LinkList &L) {
	int position;//待删除的位置
	
	cout << "功能4"<<'\n'<<"请输入要删除的位置" << endl;

	cin >> position;
	if (position<1 || position>L->data) {
		cout << "位置不合法" << endl;
		return 0;//位置不合法
	}

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

//查找一个元素，并返回他的位置
int findlist(LinkList& L) {
	int value;//待查询的值

	cout << "功能5\n请输入要查找的元素值" << endl;
	cin >> value;

	Node* p = L->next;//指向第一个结点
	int i = 1;
	for (p; p != NULL; p = p->next) {
		if (p->data == value) {
			cout << "位置是 " ;
			cout << i << endl;
			return 1;//成功找寻
		}
		i++;
	}
	cout << "查无记录" << endl;
	return 0;//没查找到
}

//当前单链表的长度
void lengthoflist(LinkList &L) {
	cout << "功能6\n当前长度为 " << endl;
	cout << L->data << endl;
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

	cout << "功能7\n链表已成功逆置" << endl;
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
	cout << "当前链表成功去重" << endl;
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


//将两个有序表合并成一个
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
	cout << "成功合并" << endl;
}

//释放内存
void freelist(LinkList &L) {
	Node* q = L;
	Node* p = NULL;
	while (q != NULL) {
		p = q->next;
		free(q);
		q = p;
	}
}

void menu() {
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "链表实验（所有链表的建立为头插法）" << endl;
	cout << "功能1：建立单链表，获取初始元素" << endl;
	cout << "功能2：输出链表中的所有元素信息" << endl;
	cout << "功能3：在选定位置中插入一个新元素" << endl;
	cout << "功能4：删除一个指定位置的元素" << endl;
	cout << "功能5：输入元素值，查找该元素是否存在" << endl;
	cout << "功能6：输出当前链表的长度" << endl;
	cout << "功能7：逆置当前链表" << endl;
	cout << "功能8：对当前链表进行去重操作" << endl;
	cout << "功能9：对两个任意链表进行非递减的重新排序和合并操作" << endl;
	cout << "功能0：退出当前程序" << endl;
	cout << "-------------------------------------------------------------------------" << endl;
}

int main()
{
	LinkList L;
	int k = 0;

	do {
		system("cls");
		menu();
		cin >> k;
		system("cls");
		if (k == 0)
			break;
		else if (k == 1)
			creatlist(L);
		else if (k == 2)
			printlist(L);
		else if (k == 3)
			insertlist(L);
		else if (k == 4)
			deletelist(L);
		else if (k == 5)
			findlist(L);
		else if (k == 6)
			lengthoflist(L);
		else if (k == 7)
			reverselist(L);
		else if (k == 8)
			quchong(L);
		else if (k == 9) {
			LinkList a, b, c;
			cout << "功能9" << endl;
			cout << "请输入两行数字，每一行都代表一个链表的初始所有数据，每一行的最后输入0代表结束输入" << endl;
			creatlist9(a);
			creatlist9(b);
			sortlist(a);
			sortlist(b);
			mergelist(a, b, c);
			cout << "已经成功合并，顺序为非递减" << endl;
			printlist(c);
			
			freelist(c);
		}

		cout << endl;
		cout << "请按任意键返回主界面" << endl;
		system("pause");
	} while (1);

	freelist(L);

	return 0;
}