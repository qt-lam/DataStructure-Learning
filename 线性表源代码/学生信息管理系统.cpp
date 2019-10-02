//ѧ����Ϣ����ϵͳ
//
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


//���� initlist 
//���ܣ�����˳���ĳ�ʼ���Ԫ���������ڴ�ʵ�����Ա�ĳ�ʼ����
int initlist(SqList& s) {
	s.elem = (ElemType*)malloc(sizeof(ElemType)*list_max_size);//�����ڴ�
	if (s.elem == NULL) {
		cout << "�ڴ�����ʧ��" << endl;
		return 0;//����ʧ��
	}

	s.length = 0;
	s.listsize = list_max_size;
	return 1;//����ɹ�
}


//���� scanflist /����1
//���ܣ��������л�ȡlist��Ԫ����Ϣ
//ע�⣺��֮ͬǰ���Զ������趨�����ڱ������Ѿ���� [���������ʾ���]
int scanflist(SqList& s) {
	cout << "����1������ָ��ѧ���������������ѧ����Ϣ��ѧ�� ���� �ɼ���" << endl;
	int number = 0;//���������Ԫ�ظ���


	cout << "�����뼴�������ѧ������" << endl;
	cin >> number;

	//����󽫳�����������
	if (number + s.length > s.listsize) {
		ElemType* newbase = (ElemType*)realloc(s.elem, (s.listsize + number) * sizeof(ElemType));//�����һЩ�ռ�
		if (newbase == NULL) {
			cout << "�ڴ�����ʧ��" << endl;
			return 0;//����ʧ��
		}

		s.elem = newbase;//�»�ַ
		s.listsize+=number;//�������+1
	}

	cout << "�������������ѧ����Ϣ" << endl;
	for (int i = s.length; i < number + s.length; i++)
		cin >> s.elem[i].no >> s.elem[i].name >> s.elem[i].score;


	s.length += number;

	return 1;
}

//���� showall /����2
//���ܣ������ʾѧ����������ѧ���������Ϣ
//ע�⣺��֮ͬǰ���Զ������趨�����ڱ������Ѿ���� [���������ʾ���]
void showall(SqList& s) {
	cout << "����2�������ʾѧ����������ѧ���������Ϣ" << endl;
	cout << "����Ϊȫ��ѧ������Ϣ" << endl;
	for (int i = 0; i < s.length; i++)
		cout << s.elem[i].no << ' ' << s.elem[i].name << ' ' << s.elem[i].score << ' ' << endl;
	cout << endl;
}


//���� findbyname /����3
//���ܣ���˳�����ͨ��������Ϣ����ѰԪ�أ�����������������Ϣ
//ע�⣺��֮ͬǰ���Զ������趨�����ڱ������Ѿ���� [���������ʾ���]
int findbyname(SqList& s) {
	cout << "����3����˳�����ͨ��������Ϣ����ѰԪ�أ����������������Ϣ" << endl;
	cout << "������Ҫ���ҵ�ѧ������" << endl;
	char name[20];
	cin >> name;

	for (int i = 0; i < s.length; i++) {
		if (strcmp(s.elem[i].name, name) == 0) {
			cout << "���ҽ������:" << endl;
			cout << s.elem[i].no << ' ' << s.elem[i].score << endl;
			return 1;
		}
	}

	cout << "���޼�¼" << endl;
	return 0;
}


//���� findbyid /����4
//���ܣ�����ָ����λ�÷������ѧ������Ϣ
//ע�⣺��֮ͬǰ���Զ������趨�����ڱ������Ѿ���� [���������ʾ���]
int findbyid(SqList &s) {
	cout << "����4�����ܣ�����ָ����λ�÷������ѧ������Ϣ" << endl;
	cout << "��������Ҫ��ѯ��λ��" << endl;
	int position = 0;

	cin >> position;
	if (position<1 || position > s.length ) {
		cout << "�����˲��Ϸ���λ��" << endl;
		return 0;//λ�ò��Ϸ�
	}

	cout << "��ѯ�������:" << endl;
	cout << s.elem[position - 1].no << ' ' << s.elem[position - 1].name << ' ' << s.elem[position - 1].score << endl;
	return 1;
}



//---------------------����insertlist ����5�ĸ�������----------------------//
//---------------------����һ��ʹ�ã������������ڻ�ȡposition��e----------//
void insertlist_fun(int &position,ElemType& e) {
	cout << "����5������һ��ѧ������Ϣ" << endl;
	cout << "�����뼴�������λ��" << endl;
	cin >> position;
	cout << "������ѧ����Ϣ" << endl;
	cin >> e.no >> e.name >> e.score;
}
//����insertlist /����5
//���ܣ�����һ��Ԫ�ع��ܣ���˳���s�ĵ�positionλ��ǰ����һ��Ԫ�أ�ʹ֮��Ϊ��position��Ԫ��
//ע�⣺��֮ͬǰ���Զ������趨�����ڱ������Ѿ���� [���������ʾ���]
int insertlist(SqList& s, int position, ElemType e) {


	if (position<1 || position > s.length + 1) {
		cout << "λ�ò��Ϸ�" << endl;
		return 0;//λ�ò��Ϸ�
	}


	if (s.length >= s.listsize) {
		ElemType* newbase = (ElemType*)realloc(s.elem, (s.listsize + 1) * sizeof(ElemType));//��ʱ����Ҫһ������һ���ռ�
		if (newbase == NULL) {
			cout << "�ڴ�����ʧ��" << endl;
			return 0;//����ʧ��
		}

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



//---------------------����deletelist ����6�ĸ�������----------------------//
//---------------------����һ��ʹ�ã������������ڻ�ȡposition----------//
void deletelist_fun(int &position) {
	cout << "����6��ɾ��һ��ѧ������Ϣ" << endl;
	cout << "�����뼴��ɾ����λ��" << endl;
	cin >> position;
}

//���� deletelist /����6
//���ܣ�ɾ��һ��Ԫ�أ�ɾ��˳���s�ĵ�position��Ԫ��
//ע�⣺��֮ͬǰ���Զ������趨�����ڱ������Ѿ���� [���������ʾ���]
int deletelist(SqList& s, int position) {
	if (position<1 || position>s.length) {
		cout << "λ�ò��Ϸ�" << endl;
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

//���� numberofsutd /����7
//���� ͳ�Ʊ���ѧ����Ϣ����
//ע�⣺��֮ͬǰ���Զ������趨�����ڱ������Ѿ���� [���������ʾ���]
void numberofstud(SqList&s) {
	cout << "����7��ͳ��ѧ����Ϣ����" << endl;
	cout << "ѧ����Ϣ����Ϊ : " << s.length << endl;
}

//���� removethesame /����8
//���ܣ�ɾ��ĳѧ�������м�¼����Ŀû�о�����ȷ������ѧ��Ϊ�жϣ�ѧ����ͬ��ͬһ��ѧ����
//ע�⣺��֮ͬǰ���Զ������趨�����ڱ������Ѿ���� [���������ʾ���]
void removethesame(SqList& s) {
	cout << "����8������ѧ����ѧ�ţ�ɾ����ѧ�������м�¼" << endl;
	cout << "������ѧ��(8λ����)" << endl;
	char no[8];
	cin >> no;

	int flag = 1;//�Ƿ���ڸ�ѧ����¼�ı�ʶ

	//�ҳ���ѧ����¼��һ�γ��ֵ��±�
	int i = 0;
	for (i = 0; i < s.length&&strcmp(no,s.elem[i].no)!=0; i++)
		;

	//�ж��Ƿ��и�Ԫ��
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
		cout << "��ȫ��ɾ��" << endl;
	else if (flag == 0)
		cout << "���޸�ѧ�ż�¼" << endl;
}

 
//ע�⣺��֮ͬǰ���Զ������趨�����ڱ������Ѿ���� [���������ʾ���]
void quchong(SqList&s) {
	cout << "����9��ȥ�������ظ���¼" << endl;
	char no[8];
	int position = 0;

	for (int i = 0; i < s.length; i++) {
		strcpy(no, s.elem[i].no);

		//�ҵ��ڶ��γ���
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


//�ͷ��ڴ�
void listfree(SqList &s) {
	free(s.elem);
	s.length = 0;
}


void menu() {
	cout << "---------------------------------------ѧ����Ϣ����ϵͳ-----------------------------------------" << endl;
	cout << "����1������ָ��ѧ���������������ѧ����Ϣ��ѧ�� ���� �ɼ���" << endl;
	cout << "����2�������ʾѧ����������ѧ���������Ϣ" << endl;
	cout << "����3����˳�����ͨ��������Ϣ����ѰԪ�أ����������������Ϣ" << endl;
	cout << "����4�����ܣ�����ָ����λ�÷������ѧ������Ϣ" << endl;
	cout << "����5������һ��ѧ������Ϣ" << endl;
	cout << "����6��ɾ��һ��ѧ������Ϣ" << endl;
	cout << "����7��ͳ��ѧ����Ϣ����" << endl;
	cout << "����8������ѧ����ѧ�ţ�ɾ����ѧ�������м�¼" << endl;
	cout << "����9��ȥ�������ظ���¼" << endl;
	cout << "����0���˳�����" << endl;
	cout << "����������0-9ѡ����" << endl;
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
			cout << "�������" << endl;
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
		cout << "---------------------�밴����������������----------------------" << endl;
		system("pause");
		system("cls");
	}
	return 0;
}