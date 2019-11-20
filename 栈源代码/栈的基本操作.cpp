//栈的基本操作
//栈主要有顺序栈和链表栈，本题使用顺序栈实现栈的基本caoz

#include <iostream>
#include <string.h>
using namespace std;


typedef int selemtype;

//堆栈
typedef struct {
	selemtype* base;
	selemtype* top;
	int stacksize;
}SqStack;

//初始化堆栈,初始最大容量由输入中获取
int initstack(SqStack& L) {
	int maxsize = 0;
	cin >> maxsize;

	L.stacksize = maxsize;//最大容量
	L.base = L.top = (selemtype*)malloc(sizeof(selemtype)*L.stacksize);//一开始栈顶等于栈底
	if (L.base == NULL)
		return 0;//申请失败
	return 1;
}


//判断栈是否为空，是返回1，不是返回0
int stackepmty(SqStack& L) {
	if (L.top == L.base)
		return 1;//栈顶等于栈底
	else
		return 0;//非空
}

//判断栈是否为满，是返回1，不是返回0
int stackfull(SqStack& L) {
	if (L.base + L.stacksize == L.top)//栈顶指向的下一个位置超过的堆栈的内存范围
		return 1;
	else
		return 0;
}

//将值value压栈，返回1则操作成功，返回0则栈满失败
int stackpush(SqStack& L,int& value) {
	if (stackfull(L) == 0) {
		*L.top = value;
		L.top++;
		return 1;//成功
	}
	else
		return 0;//失败
	
}

//出栈，将值赋给value，返回1则操作成功，返回0则栈空失败
int stackpop(SqStack& L, int& value) {
	if (stackepmty(L) == 0) {
		L.top--;
		value = *L.top;
		return 1;//成功
	}
	else {
		return 0;//失败
	}
}

//输出栈中所有元素
void printstack(SqStack& L) {
	selemtype* p = L.top;

	while (p != L.base) {
		p--;
		cout << *p << ' ';
	}
	cout << endl;
}

//获取字符串命令，入栈返回1，出栈返回2，输出返回3，都不是返回0
int chooseact() {
	char order[10];
	cin >> order;//获取入栈，出栈，输出的命令

	if (strcmp(order, "push") == 0)
		return 1;
	else if (strcmp(order, "pop") == 0)
		return 2;
	else if (strcmp(order, "quit") == 0)
		return 3;
	
	return 0;
}

void freestack(SqStack& L) {
	free(L.base);
}

int main() {
	SqStack L;
	initstack(L);

	int value = 0;
	int act = 0;
	int k = 0;
	while (1) {
		act = chooseact();
		if (act == 1) {
			cin >> value;
			k = stackpush(L, value);
			if (k == 0)
				cout << "Stack is Full" << endl;
		}
		else if (act == 2) {
			k = stackpop(L, value);
			if (k == 0)
				cout << "Stack is Empty" << endl;
			else
				cout << value << endl;			
		}
		else if (act == 3) {
			printstack(L);
			break;
		}
	}

	freestack(L);
	return 0;
}