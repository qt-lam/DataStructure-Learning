//列车问题 对栈的理解

#include <iostream>
#include <string.h>
using namespace std;

const int maxsize = 50;//暂时设定堆栈的最大容量50

typedef char selemtype;//本题主要对字符处理

//堆栈
typedef struct {
	selemtype* base;
	selemtype* top;
	int stacksize;
}SqStack;

//初始化堆栈,初始最大容量已经给定
int initstack(SqStack& L) {
	
	

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

//获得栈顶元素值
selemtype gettop(SqStack& L) {
	return *(L.top - 1);
}

//输入字符串，判断是否能实现该顺序
int carproblem(char* outcar,char* car) {
	SqStack in_car,station,out_car;//进站前的顺序栈，车站栈，出站后实际的顺序栈
	initstack(station);
	initstack(in_car);
	initstack(out_car);
	int length = strlen(car);

	for (int i = length - 1; i >= 0; i--) 
		stackpush(in_car, car[i]);
	
	char c;
	
	for (int i = 0; i < length; i++) {
		c = outcar[i];
		char temp;
		int k = 0;

		while (1) {
			if (stackepmty(in_car)) {
				for (k; k > 0; k--) {
					stackpop(station, temp);
					stackpush(in_car, temp);
				}
				if (gettop(station) != outcar[i])
					return 0; 
				else {
					stackpop(station, temp);
					break;
				}
			}
			else if (gettop(in_car) != c) {
				stackpop(in_car, temp);
				stackpush(station, temp);
				k++;
			}			
			else if(gettop(in_car) == c) {
				stackpop(in_car, temp);
				stackpush(out_car, temp);
				break;
			}
		}
	}
	return 1;
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

int main()
{
	char car[maxsize];//最多50
	cin >> car;

	char detemine[maxsize];
	int k = 0;
	while (cin >> detemine) {
		k = carproblem(detemine, car);
		if (k == 0)
			cout << "no" << endl;
		else if (k == 1)
			cout << "yes" << endl;
	}

	return 0;
}