#include <iostream>
using namespace std;

//静态链表：待补充

//循环链表： circular linked list
//特点是表中最后一个结点的指针域指向头结点而不是NULL，与单链表差别在于：有时候的判断条件变为是否等于头指针

//双向链表	doublie linked lsit

typedef  int ElemType;

typedef struct DulNode {
	ElemType data;
	DulNode * prior;
	DulNode * next;
}DulNode, *DuLinkList;


int main()
{


	return 0;
}