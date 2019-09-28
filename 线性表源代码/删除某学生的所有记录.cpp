
//ɾ��ĳֵ�����м�¼


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
		s.listsize=s.length+number;//�������+
	}

	for (int i = s.length; i < number + s.length; i++) {
		cin >> s.elem[i];
	}

	s.length += number;

	return 1;

}

int deletelist(SqList& s, int position) {
	if (position<1 || position>s.length) {
		return 0;//λ�ò��Ϸ�
	}
	ElemType* p = &(s.elem[position - 1]);
	ElemType* q = s.elem + s.length - 1;
	for (p++; p <= q; p++) {		
		*(p - 1) = *p;
	}
	s.length--;
	return 1;
}

//ԭ�㷨ʱ�临�Ӷ�O��N^2��
//����ʱ�临�Ӷ�O��N��
int removethesame(SqList& s, int e) {
	int flag = 1;

	//�ҳ���һ��Ϊe���±�
	int i = 0;
	for (i = 0; i < s.length&&s.elem[i] != e; i++)
		;

	//�ж��Ƿ��и�Ԫ��
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
