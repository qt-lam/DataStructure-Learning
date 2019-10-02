//学生信息管理系统
//
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


//函数 initlist 
//功能：根据顺序表的初始最多元素来申请内存实现线性表的初始构造
int initlist(SqList& s) {
	s.elem = (ElemType*)malloc(sizeof(ElemType)*list_max_size);//申请内存
	if (s.elem == NULL) {
		cout << "内存申请失败" << endl;
		return 0;//分配失败
	}

	s.length = 0;
	s.listsize = list_max_size;
	return 1;//构造成功
}


//函数 scanflist /功能1
//功能：从输入中获取list的元素信息
//注意：不同之前的自动判题设定，现在本函数已经添加 [输入输出提示语句]
int scanflist(SqList& s) {
	cout << "功能1：根据指定学生个数，逐个输入学生信息（学号 姓名 成绩）" << endl;
	int number = 0;//即将输入的元素个数


	cout << "请输入即将输入的学生个数" << endl;
	cin >> number;

	//输入后将超过现有容量
	if (number + s.length > s.listsize) {
		ElemType* newbase = (ElemType*)realloc(s.elem, (s.listsize + number) * sizeof(ElemType));//多分配一些空间
		if (newbase == NULL) {
			cout << "内存申请失败" << endl;
			return 0;//分配失败
		}

		s.elem = newbase;//新基址
		s.listsize+=number;//最大容量+1
	}

	cout << "请逐行逐个输入学生信息" << endl;
	for (int i = s.length; i < number + s.length; i++)
		cin >> s.elem[i].no >> s.elem[i].name >> s.elem[i].score;


	s.length += number;

	return 1;
}

//函数 showall /功能2
//功能：逐个显示学生表中所有学生的相关信息
//注意：不同之前的自动判题设定，现在本函数已经添加 [输入输出提示语句]
void showall(SqList& s) {
	cout << "功能2：逐个显示学生表中所有学生的相关信息" << endl;
	cout << "以下为全部学生的信息" << endl;
	for (int i = 0; i < s.length; i++)
		cout << s.elem[i].no << ' ' << s.elem[i].name << ' ' << s.elem[i].score << ' ' << endl;
	cout << endl;
}


//函数 findbyname /功能3
//功能：在顺序表中通过名字信息来找寻元素，并且输出其他相关信息
//注意：不同之前的自动判题设定，现在本函数已经添加 [输入输出提示语句]
int findbyname(SqList& s) {
	cout << "功能3：在顺序表中通过名字信息来找寻元素，并且输入其相关信息" << endl;
	cout << "请输入要查找的学生姓名" << endl;
	char name[20];
	cin >> name;

	for (int i = 0; i < s.length; i++) {
		if (strcmp(s.elem[i].name, name) == 0) {
			cout << "查找结果如下:" << endl;
			cout << s.elem[i].no << ' ' << s.elem[i].score << endl;
			return 1;
		}
	}

	cout << "查无记录" << endl;
	return 0;
}


//函数 findbyid /功能4
//功能：根据指定的位置返回相关学生的信息
//注意：不同之前的自动判题设定，现在本函数已经添加 [输入输出提示语句]
int findbyid(SqList &s) {
	cout << "功能4：功能：根据指定的位置返回相关学生的信息" << endl;
	cout << "请输入想要查询的位置" << endl;
	int position = 0;

	cin >> position;
	if (position<1 || position > s.length ) {
		cout << "输入了不合法的位置" << endl;
		return 0;//位置不合法
	}

	cout << "查询结果如下:" << endl;
	cout << s.elem[position - 1].no << ' ' << s.elem[position - 1].name << ' ' << s.elem[position - 1].score << endl;
	return 1;
}



//---------------------函数insertlist 功能5的辅助函数----------------------//
//---------------------二者一起使用，辅助函数用于获取position和e----------//
void insertlist_fun(int &position,ElemType& e) {
	cout << "功能5：插入一名学生的信息" << endl;
	cout << "请输入即将插入的位置" << endl;
	cin >> position;
	cout << "请输入学生信息" << endl;
	cin >> e.no >> e.name >> e.score;
}
//函数insertlist /功能5
//功能：插入一个元素功能，在顺序表s的第position位置前插入一个元素，使之成为第position个元素
//注意：不同之前的自动判题设定，现在本函数已经添加 [输入输出提示语句]
int insertlist(SqList& s, int position, ElemType e) {


	if (position<1 || position > s.length + 1) {
		cout << "位置不合法" << endl;
		return 0;//位置不合法
	}


	if (s.length >= s.listsize) {
		ElemType* newbase = (ElemType*)realloc(s.elem, (s.listsize + 1) * sizeof(ElemType));//暂时就需要一个分配一个空间
		if (newbase == NULL) {
			cout << "内存申请失败" << endl;
			return 0;//分配失败
		}

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



//---------------------函数deletelist 功能6的辅助函数----------------------//
//---------------------二者一起使用，辅助函数用于获取position----------//
void deletelist_fun(int &position) {
	cout << "功能6：删除一名学生的信息" << endl;
	cout << "请输入即将删除的位置" << endl;
	cin >> position;
}

//函数 deletelist /功能6
//功能：删除一个元素，删除顺序表s的第position个元素
//注意：不同之前的自动判题设定，现在本函数已经添加 [输入输出提示语句]
int deletelist(SqList& s, int position) {
	if (position<1 || position>s.length) {
		cout << "位置不合法" << endl;
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

//函数 numberofsutd /功能7
//功能 统计表中学生信息个数
//注意：不同之前的自动判题设定，现在本函数已经添加 [输入输出提示语句]
void numberofstud(SqList&s) {
	cout << "功能7：统计学生信息个数" << endl;
	cout << "学生信息个数为 : " << s.length << endl;
}

//函数 removethesame /功能8
//功能：删除某学生的所有记录（题目没有具体明确，故以学号为判断，学号相同即同一名学生）
//注意：不同之前的自动判题设定，现在本函数已经添加 [输入输出提示语句]
void removethesame(SqList& s) {
	cout << "功能8：输入学生的学号，删除该学生的所有记录" << endl;
	cout << "请输入学号(8位以内)" << endl;
	char no[8];
	cin >> no;

	int flag = 1;//是否存在该学生记录的标识

	//找出该学生记录第一次出现的下标
	int i = 0;
	for (i = 0; i < s.length&&strcmp(no,s.elem[i].no)!=0; i++)
		;

	//判断是否含有该元素
	if (i == s.length)
		flag = 0;
	 
	for (int j = i + 1; j < s.length; j++) {
		if (strcmp(no,s.elem[j].no)!=0) {
			s.elem[i].score = s.elem[j].score;
			strcpy(s.elem[i].no, s.elem[j].no);
			strcpy(s.elem[i].name, s.elem[j].name);
			i++;
		}
	}

	s.length = i;
	if (flag == 1)
		cout << "已全部删除" << endl;
	else if (flag == 0)
		cout << "查无该学号记录" << endl;
}

 
//注意：不同之前的自动判题设定，现在本函数已经添加 [输入输出提示语句]
void quchong(SqList&s) {
	cout << "功能9：去重所有重复记录" << endl;
	char no[8];
	int position = 0;

	for (int i = 0; i < s.length; i++) {
		strcpy(no, s.elem[i].no);

		//找到第二次出现
		for (position = i + 1; position < s.length&&strcmp(no, s.elem[position].no) != 0; position++)
			;

		for (int j = position + 1; j < s.length; j++) {
			if (strcmp(no, s.elem[j].no) != 0) {
				s.elem[position].score = s.elem[j].score;
				strcpy(s.elem[position].no, s.elem[j].no);
				strcpy(s.elem[position].name, s.elem[j].name);
				position++;
			}
		}
		s.length = position;

	}
}


//释放内存
void listfree(SqList &s) {
	free(s.elem);
	s.length = 0;
}


void menu() {
	cout << "---------------------------------------学生信息管理系统-----------------------------------------" << endl;
	cout << "功能1：根据指定学生个数，逐个输入学生信息（学号 姓名 成绩）" << endl;
	cout << "功能2：逐个显示学生表中所有学生的相关信息" << endl;
	cout << "功能3：在顺序表中通过名字信息来找寻元素，并且输入其相关信息" << endl;
	cout << "功能4：功能：根据指定的位置返回相关学生的信息" << endl;
	cout << "功能5：插入一名学生的信息" << endl;
	cout << "功能6：删除一名学生的信息" << endl;
	cout << "功能7：统计学生信息个数" << endl;
	cout << "功能8：输入学生的学号，删除该学生的所有记录" << endl;
	cout << "功能9：去重所有重复记录" << endl;
	cout << "功能0：退出程序" << endl;
	cout << "请输入数字0-9选择功能" << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
}

int main() {
	int choice = 0;
	SqList s;
	initlist(s);

	while (1) {
		
		menu();
		cin >> choice;
		system("cls");

		if (choice == 0) {
			cout << "程序结束" << endl;
			break;
		}
		else if (choice == 1)
			scanflist(s);
		else if (choice == 2)
			showall(s);
		else if (choice == 3)
			findbyname(s);
		else if (choice == 4)
			findbyid(s);
		else if (choice == 5) {
			int position;
			ElemType e;
			insertlist_fun(position, e);
			insertlist(s, position, e);
		}
		else if (choice == 6) {
			int position;
			deletelist_fun(position);
			deletelist(s, position);
		}
		else if (choice == 7)
			numberofstud(s);
		else if (choice == 8)
			removethesame(s);
		else if (choice == 9)
			quchong(s);

		cout << endl;
		cout << "---------------------请按任意键到主程序界面----------------------" << endl;
		system("pause");
		system("cls");
	}
	return 0;
}