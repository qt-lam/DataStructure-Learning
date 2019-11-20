//表达式求值
//栈主要有顺序栈和链表栈，本题使用顺序栈实现栈的基本caoz

//主要方法有算符优先法和中缀转为后缀表达式法

#include <iostream>
#include <string.h>
using namespace std;

const int maxsize = 30;
const int addsize = 10;

typedef int selemtype;

//堆栈
typedef struct {
	selemtype* base;
	selemtype* top;
	int stacksize;
}SqStack;

//初始化堆栈,初始最大容量由输入中获取
int initstack(SqStack& L) {
	/*int maxsize = 0;
	cin >> maxsize;*/

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
//针对表达式求值一题没有设定最大数量级，到达栈顶后将继续申请内存
int stackfull(SqStack& L) {
	if (L.base + L.stacksize == L.top) {//栈顶指向的下一个位置超过的堆栈的内存范围
		L.base = (selemtype*)realloc((void*)L.base,sizeof(selemtype)*(L.stacksize + addsize));//重新申请，扩大范围
		return 0;
		//从return1 修改成 return0
	}
	else
		return 0;
}

//将值value压栈，返回1则操作成功，返回0则栈满失败
//修改后一定可以操作成功，只是返回的值无意义，不再用来区分操作是否成功
int stackpush(SqStack& L, selemtype value) {
	if (stackfull(L) == 0) {
		*L.top = value;
		L.top++;
		return 1;//成功
	}
	else
		return 0;//失败

}

//出栈，将值赋给value，返回1则操作成功，返回0则栈空失败
int stackpop(SqStack& L, selemtype& value) {
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

//释放内存，销毁栈
void freestack(SqStack& L) {
	free(L.base);
}


int getxy(int c) {
	int xy = 0;
	switch (c)
	{
		case '+':
			xy = 0;
			break;
		case '-':
			xy = 1;
			break;
		case '*':
			xy = 2;
			break;
		case '/':
			xy = 3;
			break;
		case '(':
			xy = 4;
			break;
		case ')':
			xy = 5;
			break;
		case '=':
			xy = 6;
			break;
	}
	return xy;
}

//比较优先级，拿获取到的运算符字符和栈顶的运算符比较优先级
char precede(selemtype top,char c) {

	//+ - * / ( ) =

	char compare[7][7] = {
		'>','>','<','<','<','>','>',
		'>','>','<','<','<','>','>',
		'>','>','>','>','<','>','>',
		'>','>','>','>','<','>','>',
		'<','<','<','<','<','=','?',
		'>','>','>','>','?','>','>',
		'<','<','<','<','<','?','='
	};
	int x = getxy(top);
	int y = getxy(c);
	return compare[x][y];
}


int getvalue(int a, int b, int c) {
	int value = 0;
	switch (c) {
		case '+':
			value = a + b;
			break;
		case '-':
			value = a - b;
			break;
		case '*':
			value = a * b;
			break;
		case '/':
			value = a / b;
			break;
	}	
	return value;
}

int errorinput(int c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '='||c=='('||c==')')
		return 1;
	else if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}



int value_expression() {
	SqStack OPTR, OPND;//符号和操作数栈
	initstack(OPTR);
	initstack(OPND);
	int c = '=';
	stackpush(OPTR, c);

	int k = 0;//判断是否是十位数以及以上
	//int i = 1;//判断是否连续输入两次符号（即3+-4） 负数的表示
	//int fushu = 0;
	int tem = 0;

	c = getchar();
	while (c != '=' || *(OPTR.top - 1) != '=') {

		if (!errorinput(c)) {
			cout << "ERROR" << endl;
			return 0;
		}			

		if (c >= '0'&&c <= '9') {
			c -= '0';
			if (k == 1) {
				stackpop(OPND, tem);
				c = tem * 10 + c;
			}
			/*if (fushu == 1) {
				c = 0 - c;
				fushu = 0;
			}*/
			stackpush(OPND, c);
			k = 1;
			//i = 0;
			c = getchar();
		}
		else {
			k = 0;

			////其他情况属于错误情况，应该不会出现
			//if (i == 1 && c == '-') {
			//	fushu = 1;
			//	i = 0;
			//	c = getchar();
			//	continue;
			//}

			//i = 1;
			switch (precede(*(OPTR.top - 1), c))
			{
				case '<':
					stackpush(OPTR, c);
					c = getchar();
					break;
				case '=':
					stackpop(OPTR, c);
					c = getchar();
					break;
				case '>':
					if (*(OPTR.top - 1) == '/'&&*(OPND.top - 1) == 0) {
						cout << "ERROR" << endl;
						return 0;
					}

					int a, b, operato;
					stackpop(OPND, b);
					stackpop(OPND, a);
					stackpop(OPTR, operato);
					stackpush(OPND, getvalue(a, b, operato));
					break;
			}
		}
	}
	cout << *(OPND.top - 1) << endl;
	return 1;
}



int main() {
	value_expression();

	return 0;
}