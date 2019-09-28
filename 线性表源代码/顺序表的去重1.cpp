
//顺序表的去重1

#include <iostream>
#include <stdlib.h>
using namespace std;


#define list_max_size 100  //顺序表初始的最多包含元素个数


typedef int ElemType;

typedef  struct {

	ElemType *elem;     // 指向数据元素的基地址

	int  length;       // 线性表的当前长度       

	int  listsize;      //线性表的最大容量                                                 

}SqList;

int initlist(SqList& s) {
	s.elem = (ElemType*)malloc(sizeof(ElemType)*list_max_size);//申请内存
	if (s.elem == NULL)
		return 0;//分配失败

	s.length = 0;
	s.listsize = list_max_size;
	return 1;//构造成功
}

void listfree(SqList &s) {
	free(s.elem);
	s.length = 0;
}


int scanflist(SqList& s) {

	int number = 0;//即将输入的元素个数

	cin >> number;

	if (number > s.length) {
		ElemType* newbase = (ElemType*)realloc(s.elem, (s.length + number) * sizeof(ElemType));//
		if (newbase == NULL)
			return 0;//分配失败

		s.elem = newbase;//新基址
		s.listsize = s.length + number;//最大容量+
	}

	for (int i = s.length; i < number + s.length; i++) {
		cin >> s.elem[i];
	}

	s.length += number;

	return 1;

}

void quchong(SqList &s) {
	int e = 0;
	int position = 0;
	for (int i = 0; i < s.length; i++) {
		e = s.elem[i];

		//找到第二次出现
		for (position = i+1; position < s.length&&s.elem[position] != e; position++)
			;

		for (int j = position + 1; j < s.length; j++) {
			if (s.elem[j] != e) {
				s.elem[position++] = s.elem[j];
			}
		}
		s.length = position;
		
	}

}

void showall(SqList& s) {
	for (int i = 0; i < s.length; i++)
		cout << s.elem[i] << ' ';
	cout << endl;
}

int main() {
	SqList s;
	initlist(s);
	scanflist(s);
	quchong(s);
	showall(s);
	listfree(s);
	return 0;
}
