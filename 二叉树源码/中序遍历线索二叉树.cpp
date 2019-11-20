//�����������������
#include <iostream>
using namespace std;

typedef char datatype;

enum PointerTag {
	Link, Thread//link==0,ָ�� thread==1,����
};

typedef struct BiThNode {
	datatype data;//����
	BiThNode *lchild, *rchild;//���Һ��ӽ��
	PointerTag Ltag, Rtag;//���ұ�ʶ
}BiThNode, *BiThTree;


typedef BiThNode* selemtype;



//��������������������,��δ������
int creatbitree(BiThTree& T) {
	char c;
	cin >> c;
	if (c == '#')
		T = NULL;
	else {
		T = (BiThNode*)malloc(sizeof(BiThNode));
		if (T == NULL)
			return 0;//����ʧ��,����ʧ��

		T->data = c;
		T->Ltag = T->Rtag = Link;//��ȫ����ΪLINK ��������ʱ�ٷ�
		creatbitree(T->lchild);
		creatbitree(T->rchild);
	}
	return 1;
}


BiThTree pre = NULL;//ȫ��ָ�������ָ��ǰ�����
//������������������ʹ�õݹ鷽��
void inthreading(BiThTree& T) {
	if (T) {
		inthreading(T->lchild);

		if (!T->lchild) {
			T->Ltag = Thread;//����Ϊ�գ�ָ��ǰ��
			T->lchild = pre;
		}

		if (!T->rchild)
			T->Rtag = Thread;//�ҽ��Ϊ�գ���ʹ��ʶΪ����

		if (pre&&pre->Rtag == Thread)//ǰ���������ҽ��Ϊ�գ��Һ���ָ����
			pre->rchild = T;

		pre = T;


		inthreading(T->rchild);
	}
}


//�����������������,�ǵݹ�
void inorder_Th(BiThTree& T) {
	BiThNode* p = T;

	while (1) {
		while (p->Ltag == Link) {
			p = p->lchild;
		}
		cout << p->data;

		if ((p->Rtag == Thread && p->rchild == NULL))
			break;

		while (p->Rtag == Thread) {
			p = p->rchild;
			cout << p->data;
			if ((p->Rtag == Thread && p->rchild == NULL))
				break;
		}

		if ((p->Rtag == Thread && p->rchild == NULL))
			break;
		p = p->rchild;
	}
	cout << endl;
}


void findneibor(BiThTree& T,datatype e) {
	BiThNode* p = T;

	BiThNode** s = (BiThNode**)malloc(sizeof(BiThNode*)*20);
	int i = 0;


	while (1) {
		while (p->Ltag == Link) {
			p = p->lchild;
		}

		s[i] = p;
		i++;

		if ((p->Rtag == Thread && p->rchild == NULL))
			break;

		while (p->Rtag == Thread) {
			p = p->rchild;

			s[i] = p;
			i++;

			if ((p->Rtag == Thread && p->rchild == NULL))
				break;
		}

		if ((p->Rtag == Thread && p->rchild == NULL))
			break;
		p = p->rchild;
	}


	int k = 0;
	for (int j = 0; j < i; j++) {
		if (s[j]->data == e) {
			k = 1;
			if (i == 1) {
				cout << "succ is NULL" << endl;
				cout << "prev is NULL" << endl;
			}
			else if (j == 0) {
				cout << "succ is " << s[j + 1]->data << s[j + 1]->Rtag << endl;
				cout << "prev is NULL" << endl;				
			}
			else if (j == i-1) {
				cout << "succ is NULL" << endl;
				cout << "prev is " << s[j - 1]->data << s[j - 1]->Ltag << endl;
			}
			else {
				cout << "succ is " << s[j + 1]->data << s[j + 1]->Rtag << endl;
				cout << "prev is " << s[j - 1]->data << s[j - 1]->Ltag << endl;
			}
			break;
		}
	}

	if (k == 0)
		cout << "Not found" << endl;
}

int main() {
	BiThTree T;
	creatbitree(T);
	inthreading(T);
	inorder_Th(T);
	datatype e;
	cin >> e;
	findneibor(T, e);
	return 0;
}