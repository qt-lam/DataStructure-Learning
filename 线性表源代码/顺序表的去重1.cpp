
//˳����ȥ��1

#include <iostream>
#include <stdlib.h>
using namespace std;


#define list_max_size 100  //˳����ʼ��������Ԫ�ظ���


typedef int ElemType;

typedef  struct {

	ElemType *elem;     // ָ������Ԫ�صĻ���ַ

	int  length;       // ���Ա�ĵ�ǰ����       

	int  listsize;      //���Ա���������                                                 

}SqList;

int initlist(SqList& s) {
	s.elem = (ElemType*)malloc(sizeof(ElemType)*list_max_size);//�����ڴ�
	if (s.elem == NULL)
		return 0;//����ʧ��

	s.length = 0;
	s.listsize = list_max_size;
	return 1;//����ɹ�
}

void listfree(SqList &s) {
	free(s.elem);
	s.length = 0;
}


int scanflist(SqList& s) {

	int number = 0;//���������Ԫ�ظ���

	cin >> number;

	if (number > s.length) {
		ElemType* newbase = (ElemType*)realloc(s.elem, (s.length + number) * sizeof(ElemType));//
		if (newbase == NULL)
			return 0;//����ʧ��

		s.elem = newbase;//�»�ַ
		s.listsize = s.length + number;//�������+
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

		//�ҵ��ڶ��γ���
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
