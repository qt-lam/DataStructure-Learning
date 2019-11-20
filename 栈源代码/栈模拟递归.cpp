//栈模拟递归过程
#include <iostream>
#include <string.h>
using namespace std;

const int maxsize = 50;//堆栈的最大容量暂定50

//模拟递归中的被记录在局部变量存储区的信息，堆栈的基本元素结构
typedef struct {
	int n; //函数的输入参数
	//构造器及getter、setter
}Data;


//堆栈的基本结构
typedef struct {
	Data* base;
	Data* top;
	int stacksize;
}SqStack;

//初始化堆栈,初始最大容量由输入中获取
int initstack(SqStack& L) {

	L.stacksize = maxsize;//最大容量
	L.base = L.top = (Data*)malloc(sizeof(Data)*L.stacksize);//一开始栈顶等于栈底
	if (L.base == NULL)
		return 0;//申请失败
	return 1;
}

//判断栈是否为空，是返回1，不是返回0
int stackempty(SqStack& L) {
	if (L.top == L.base)
		return 1;//栈顶等于栈底
	else
		return 0;//非空
}

//函数 stackfull
//功能 判断栈是否为满，是返回1，不是返回0
int stackfull(SqStack& L) {
	if (L.base + L.stacksize == L.top)//栈顶指向的下一个位置超过的堆栈的内存范围
		return 1;
	else
		return 0;
}


//函数 stackpush
//功能 将元素value压栈，返回1则操作成功，返回0则栈满失败
int stackpush(SqStack& L, Data value) {
	if (stackfull(L) == 0) {
		*L.top = value;
		L.top++;
		return 1;//成功
	}
	else
		return 0;//失败

}

//函数 stackpop
//功能 将栈顶元素出栈给参数value，返回1则操作成功，返回0则栈空失败
int stackpop(SqStack& L, Data& value) {
	if (stackempty(L) == 0) {
		L.top--;
		value = *L.top;
		return 1;//成功
	}
	else {
		return 0;//失败
	}
}

//函数 simulation
//功能 使用栈来模拟n阶乘的递归过程
int simulation(int n) {
	//相当于main函数内，尚未开始调用“递归”
	SqStack L;
	initstack(L);

	Data element;

	element.n = n;//初始参数

	while (element.n > 1) {
		//正式进入递归函数
		stackpush(L, element);//将参数和返回的地址压入栈
		element.n--;//n-1		
	}
	int sum = 1;
	//递归函数开始回溯
	while (!stackempty(L)) {
		stackpop(L, element);
		sum = sum * element.n;		
	}

	cout << sum << endl;
	return 1;
}

int main() {

	simulation(1000000000);

	return 0;
}
