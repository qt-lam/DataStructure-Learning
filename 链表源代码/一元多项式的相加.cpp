//一元多项式的相加
//利用顺序存储结构时，容易浪费时间（尤其每一项直接指数差别过大）
//利用链表存储存储每一项的两个数据信息，除了一些极端情况（比如刚刚好指数从1-n，则反而浪费空间），其余情况都是节省空间，但是效率会低

//本方法用于一次多项式的相加，但是前提是多项式内没有指数重复的项，且从小到大按顺序排列

#include <iostream>
using namespace std;

typedef int elemtype;

typedef struct linklist {
	elemtype pi;
	elemtype ei;
	linklist* next;
}Node, *HeadNodeP;

//尾插法建立，顺序为正序，且要求指数递增
int creatlist(HeadNodeP& L) {
	L = (HeadNodeP)malloc(sizeof(Node));
	//头结点初始化
	L->ei = -1;
	L->pi = -1;
	L->next = NULL;

	//获取初始数据组数目
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

//两个多项式相加，结果存至链表c中，且链表c尚未初始化建立过，ab指数递增;ab链表内部会变化，即不保存之前的结构
void addlist(HeadNodeP& a, HeadNodeP &b, HeadNodeP& c) {
	Node* pa = a->next;//指向第一组数据
	Node* pb = b->next;
	Node* ppre = c = a;//将a的头结点给c
	Node* tobefree = NULL;

	while (pa&&pb) {
		if (pa->ei < pb->ei) {
			ppre = pa;
			pa = pa->next;
		}
		else if (pa->ei == pb->ei) {
			pa->pi += pb->pi;
			if (pa->pi == 0) {
				tobefree = pa;
				pa = pa->next;
				free(tobefree);

				tobefree = pb;
				pb = pb->next;
				free(tobefree);
			}
			else {
				ppre = pa;
				pa = pa->next;
				pb = pb->next;
			}
		}
		else if(pa->ei>pb->ei){
			ppre->next = pb;
			pb = pb->next;
			(ppre->next)->next = pa;
			ppre = ppre->next;		
		}
	}
	ppre->next = pa ? pa : pb;
	free(b);
}

void printlist(HeadNodeP& L) {
	Node* p = L->next;
	for (p; p != NULL; p = p->next) {
		cout << p->pi << ' ' << p->ei << endl;
	}
}

int main()
{
	HeadNodeP a;
	HeadNodeP b;
	creatlist(a);
	creatlist(b);
	//printlist(a);
	//printlist(b);
	HeadNodeP(c);
	addlist(a, b, c);
	cout << endl;
	printlist(c);
	return 0;
}