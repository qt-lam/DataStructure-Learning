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
//�ݹ鷽������������
void prethreading(BiThTree& T){
	if (T) {
		if (!T->lchild) {
			T->Ltag = Thread;//����Ϊ�գ�ָ��ǰ��
			T->lchild = pre;
		}
		if (!T->rchild)
			T->Rtag = Thread;//�ҽ��Ϊ�գ���ʹ��ʶΪ����

		if (pre&&pre->Rtag == Thread)//ǰ���������ҽ��Ϊ�գ��Һ���ָ����
			pre->rchild = T;

		pre = T;


		if (T->Ltag == Link)
			prethreading(T->lchild);
		if (T->Rtag == Link)
			prethreading(T->rchild);

	}
}

//��ʾ��������������������ͼ
void printree(BiThTree& T, int n) {
	int i;
	char c = ' ';
	if (T) {
		if(T->Rtag==Link)
			printree(T->rchild, n + 1);
		for (i = 1; i <= n; i++) {
			printf("%5c", c);//���5��
			
		}		
		cout << T->data;
		printf("%d%d\n", T->Ltag, T->Rtag);
		if(T->Ltag==Link)
			printree(T->lchild, n + 1);
	}
}

//�����������������
void preorder_Th(BiThTree& T) {
	BiThNode* p = T;
	cout << p->data;
	while (p->rchild) {//�����жϱ��ж�RTAG��һЩ
		if (p->Ltag == Link)
			p = p->lchild;
		else
			p = p->rchild;
		cout << p->data;
	}
}

int main()
{
	BiThTree T;
	creatbitree(T);
	prethreading(T);
	printree(T,0);
	preorder_Th(T);

	return 0;
}