
//˳���Ļ�������


//д�����ĸ��ܣ�
//֮ǰ��ô���80�ֿ�ס��ԭ��������ڲ���Ԫ��ʱ������� ��� ѧ�� ���� �ɼ�
//���Ȼ�ȡ��ţ���Ŵ���������󣬽���������̣�����û�к���������Ҫ�������Ϣ����Ϊ��žʹ���
//���ֿ�֪��oj�����еڶ�������ʵ�����������ӵģ�Ҫ��ȫ����������ж�
//�����˷����Ҽ���Сʱ��ʱ�䣬�Һ����ߣ�ǿ��������oj
//�������������Ϣ����ϸ��

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define list_max_size 10005  //˳����ʼ��������Ԫ�ظ���

typedef struct {

	char no[8];   //8 λѧ��

	char name[20]; // ����

	double score;     // �ɼ�

}Student;

typedef Student ElemType;

//��˳���ʵ�ֵ����Ա�
typedef  struct {

	ElemType  *elem;     // ָ������Ԫ�صĻ���ַ

	int  length;       // ���Ա�ĵ�ǰ����       

	int  listsize;      //���Ա���������                                                 

}SqList;

//���Ա�ĳ�ʼ����
int initlist(SqList& s) {
	s.elem = (ElemType*)malloc(sizeof(ElemType)*list_max_size);//�����ڴ�
	if (s.elem == NULL)
		return 0;//����ʧ��

	s.length = 0;
	s.listsize = list_max_size;
	return 1;//����ɹ�
}

//����һ��Ԫ�ع��ܣ���˳���s�ĵ�positionλ��ǰ����һ��Ԫ�أ�ʹ֮��Ϊ��position��Ԫ��
int insertlist(SqList& s, int position,ElemType e) {
	if (position<1 || position > s.length + 1) 
		return 0;//λ�ò��Ϸ�
		
	
	if (s.length >= s.listsize) {
		ElemType* newbase = (ElemType*)realloc(s.elem, (s.listsize + 1) * sizeof(ElemType));//��ʱ����Ҫһ������һ���ռ�
		if (newbase == NULL)
			return 0;//����ʧ��

		s.elem = newbase;//�»�ַ
		s.listsize++;//�������+1
	}

	ElemType* q = &(s.elem[position - 1]);
	for (ElemType* p = &(s.elem[s.length - 1]); p >= q; p--) {
		*(p + 1) = *p;
	}
	
	*q = e;

	s.length++;
	return 1;

}

//ɾ��һ��Ԫ�أ�ɾ��˳���s�ĵ�position��Ԫ��
int deletelist(SqList& s, int position) {
	if (position<1 || position>s.length) {
		return 0;//λ�ò��Ϸ�
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

//�������л�ȡlist��Ԫ����Ϣ
int scanflist(SqList& s) {

	int number = 0;//���������Ԫ�ظ���

	cin >> number;

	for (int i = s.length; i < number+s.length; i++) 
		cin >> s.elem[i].no >> s.elem[i].name >> s.elem[i].score;


	s.length += number;

	return 1;
	
}

//��˳�����ͨ��������Ϣ����ѰԪ��
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

//�ͷ��ڴ�
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
