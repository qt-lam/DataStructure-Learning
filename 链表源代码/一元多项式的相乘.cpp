//一元多项式的相乘
//应该同相加是递增顺序

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

//两个一元多项式ab 相乘得c，c尚未链表初始化建立过,递增顺序,ab不会受到影响，没有释放
//效率较差
void mulitlist(HeadNodeP& a, HeadNodeP& b, HeadNodeP& c) {
	Node* pa = a->next;
	Node* pb = b->next;
	Node* pc = c = (Node*)malloc(sizeof(Node));
	pc->next = NULL;

	Node* s = NULL;
	Node* ppa;
	Node* ppc;

	//先对于各自相乘，尚未排序和排重
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
	
	//第一个必定是指数最小的，且无重复
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
				//相乘没有相等的？
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

//输出所有元素
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