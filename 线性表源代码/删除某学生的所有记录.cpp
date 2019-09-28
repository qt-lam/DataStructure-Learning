
//删除某值的所有记录


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
		s.listsize=s.length+number;//最大容量+
	}

	for (int i = s.length; i < number + s.length; i++) {
		cin >> s.elem[i];
	}

	s.length += number;

	return 1;

}

int deletelist(SqList& s, int position) {
	if (position<1 || position>s.length) {
		return 0;//位置不合法
	}
	ElemType* p = &(s.elem[position - 1]);
	ElemType* q = s.elem + s.length - 1;
	for (p++; p <= q; p++) {		
		*(p - 1) = *p;
	}
	s.length--;
	return 1;
}

//原算法时间复杂度O（N^2）
//现在时间复杂度O（N）
int removethesame(SqList& s, int e) {
	int flag = 1;

	//找出第一个为e的下标
	int i = 0;
	for (i = 0; i < s.length&&s.elem[i] != e; i++)
		;

	//判断是否含有该元素
	if (i == s.length)
		flag = 0;

	for (int j = i + 1; j < s.length; j++) {
		if (s.elem[j] != e) {
			s.elem[i++] = s.elem[j];
		}
	}
	s.length = i;

	if (flag == 0)
		return 0;
	else 
		return 1;
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

	int e;
	cin >> e;
	int k=removethesame(s, e);
	if (k == 0)
		cout << -1 << endl;
	else
		showall(s);
	listfree(s);
	return 0;
}
