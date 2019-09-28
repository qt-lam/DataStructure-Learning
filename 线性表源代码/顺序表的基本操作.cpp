
//顺序表的基本操作


//写完代码的感受：
//之前那么多次80分卡住的原因就是在于插入元素时所输入的 序号 学号 姓名 成绩
//我先获取序号，序号错误即输出错误，结束这个过程，所以没有后续读入所要插入的信息（因为序号就错了
//发现可知道oj判题中第二个点其实并不是这样子的，要求全部输入后再判断
//所以浪费了我几个小时的时间，我很气愤，强烈抨击这个oj
//建议输入输出信息给详细点

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define list_max_size 10005  //顺序表初始的最多包含元素个数

typedef struct {

	char no[8];   //8 位学号

	char name[20]; // 姓名

	double score;     // 成绩

}Student;

typedef Student ElemType;

//以顺序表实现的线性表
typedef  struct {

	ElemType  *elem;     // 指向数据元素的基地址

	int  length;       // 线性表的当前长度       

	int  listsize;      //线性表的最大容量                                                 

}SqList;

//线性表的初始构造
int initlist(SqList& s) {
	s.elem = (ElemType*)malloc(sizeof(ElemType)*list_max_size);//申请内存
	if (s.elem == NULL)
		return 0;//分配失败

	s.length = 0;
	s.listsize = list_max_size;
	return 1;//构造成功
}

//插入一个元素功能，在顺序表s的第position位置前插入一个元素，使之成为第position个元素
int insertlist(SqList& s, int position,ElemType e) {
	if (position<1 || position > s.length + 1) 
		return 0;//位置不合法
		
	
	if (s.length >= s.listsize) {
		ElemType* newbase = (ElemType*)realloc(s.elem, (s.listsize + 1) * sizeof(ElemType));//暂时就需要一个分配一个空间
		if (newbase == NULL)
			return 0;//分配失败

		s.elem = newbase;//新基址
		s.listsize++;//最大容量+1
	}

	ElemType* q = &(s.elem[position - 1]);
	for (ElemType* p = &(s.elem[s.length - 1]); p >= q; p--) {
		*(p + 1) = *p;
	}
	
	*q = e;

	s.length++;
	return 1;

}

//删除一个元素，删除顺序表s的第position个元素
int deletelist(SqList& s, int position) {
	if (position<1 || position>s.length) {
		return 0;//位置不合法
	}

	ElemType* p = &(s.elem[position - 1]);
	ElemType* q = s.elem + s.length - 1;
	for (p++; p <= q; p++) {
		strcpy((p - 1)->name, p->name);
		strcpy((p - 1)->no, p->no);
		(p - 1)->score = p->score;
	}
	s.length--;
	return 1;
}

//从输入中获取list的元素信息
int scanflist(SqList& s) {

	int number = 0;//即将输入的元素个数

	cin >> number;

	for (int i = s.length; i < number+s.length; i++) 
		cin >> s.elem[i].no >> s.elem[i].name >> s.elem[i].score;


	s.length += number;

	return 1;
	
}

//在顺序表中通过名字信息来找寻元素
int findbyname(SqList& s) {
	char name[20];
	cin >> name;

	for (int i = 0; i < s.length; i++) {
		if (strcmp(s.elem[i].name, name) == 0) {
			cout << s.elem[i].no << ' ' << s.elem[i].score << endl;
			return 1;
		}
	}
	return 0;

}

//释放内存
void listfree(SqList &s) {
	free(s.elem);
	s.length = 0;
}

int main()
{
	SqList s;
	
	initlist(s);
	scanflist(s);
	
	int position = 0;
	int k = 0;
	ElemType e;
	cin >> position >> e.no >> e.name >> e.score;
	k=insertlist(s, position,e);
	if (k == 1)
		cout << 0 << endl;
	else if (k == 0)
		cout << -1 << endl;

	cin >> position;
	k = deletelist(s, position);
	if (k == 1)
		cout << 0 << endl;
	else if (k == 0)
		cout << -1 << endl;

	k=findbyname(s);
	if (k == 0)
		cout << -1 << endl;

	cout << s.length << endl;

	listfree(s);
	return 0;
}
