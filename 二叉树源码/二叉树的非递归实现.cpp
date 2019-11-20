//�������ķǵݹ�ʵ��
#include <iostream>
using namespace std;

typedef char datatype;

//��ʽ������
typedef struct BitNode {
	datatype data;
	BitNode* lchild, *rchild;
}BitNode, *BitTree;


typedef BitNode* selemtype;

//��ջ
typedef struct {
	selemtype* base;
	selemtype* top;
	int stacksize;
}SqStack;

//��ʼ����ջ,[��ʼ��������������л�ȡ]
int initstack(SqStack& L) {
	int maxsize = 50;
	//cin >> maxsize;

	L.stacksize = maxsize;//�������
	L.base = L.top = (selemtype*)malloc(sizeof(selemtype)*L.stacksize);//һ��ʼջ������ջ��
	if (L.base == NULL)
		return 0;//����ʧ��
	return 1;
}


//�ж�ջ�Ƿ�Ϊ�գ��Ƿ���1�����Ƿ���0
int stackepmty(SqStack& L) {
	if (L.top == L.base)
		return 1;//ջ������ջ��
	else
		return 0;//�ǿ�
}

//�ж�ջ�Ƿ�Ϊ�����Ƿ���1�����Ƿ���0
int stackfull(SqStack& L) {
	if (L.base + L.stacksize == L.top)//ջ��ָ�����һ��λ�ó����Ķ�ջ���ڴ淶Χ
		return 1;
	else
		return 0;
}

//��ֵvalueѹջ������1������ɹ�������0��ջ��ʧ��
int stackpush(SqStack& L, selemtype value) {
	if (stackfull(L) == 0) {
		*L.top = value;
		L.top++;
		return 1;//�ɹ�
	}
	else
		return 0;//ʧ��

}

//��ջ����ֵ����value������1������ɹ�������0��ջ��ʧ��
int stackpop(SqStack& L, selemtype& value) {
	if (stackepmty(L) == 0) {
		L.top--;
		value = *L.top;
		return 1;//�ɹ�
	}
	else {
		return 0;//ʧ��
	}
}

//��������������������
int creatbitree(BitTree& T) {
	char c;
	cin >> c;
	if (c == '#')
		T = NULL;
	else {
		T = (BitNode*)malloc(sizeof(BitNode));
		if (T == NULL)
			return 0;//����ʧ��,����ʧ��

		T->data = c;
		creatbitree(T->lchild);
		creatbitree(T->rchild);
	}
	return 1;
}

//�������뽨����������ʹ�÷ǵݹ�
//int CreatTree(BitTree& T) {
//	SqStack S;
//	initstack(S);
//
//	char c;
//	while (1) {
//		cin >> c;
//		if (c == '#')
//			T = NULL;
//		else {
//			T = (BitNode*)malloc(sizeof(BitNode));
//			T->data = c;
//			stackpush(S, T);
//		}
//
//		if (T == NULL && stackepmty(S))
//			return 0;
//
//		T = T->lchild;
//	}
//}

//�ǵݹ��������
void inorder_print(BitTree& T) {
	SqStack S;
	initstack(S);
	BitTree TP = T;
	while (TP || !stackepmty(S)) {
		if (TP) {
			stackpush(S, TP);
			cout << "push " << TP->data << endl;
			TP = TP->lchild;
		}
		else {
			stackpop(S, TP);
			cout << "pop" << endl;
			cout << TP->data << endl;
			TP = TP->rchild;
		}
	}
}

int main()
{
	BitTree T;
	creatbitree(T);
	inorder_print(T);
	return 0;
}