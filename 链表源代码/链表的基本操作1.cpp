//����Ļ�������
#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct Node {
	ElemType  data;     
	Node  *next;        
}Node, *LinkList;//��㣬ͷָ��


//ͷ�巨��ÿ�ξ���ͷ���������Ԫ��
int creatlist(LinkList& L) {
	Node* s;
	int length = 0;//����
	L = (LinkList)malloc(sizeof(Node));//����ͷ���
	L->next = NULL;
	L->data = 0;//ͷ���������洢������

	cin >> length;//��ȡ����ʱ����ĳ���
	L->data = length;

	for (int i = 0; i < length; i++) {
		s = (Node *)(malloc)(sizeof(Node));  //return 0 waiting
		cin >> s->data;
		s->next = L->next;
		L->next = s;
	}
	return 1;
}

//������������Ԫ��
void printlist(LinkList& L) {
	Node* p;
	for (p = L->next;p!=NULL ;p=p->next ) {
		cout << p->data << ' ';
	}
	cout << endl;
}

//����һ��Ԫ��
int insertlist(LinkList& L) {
	int value;//�������ֵ
	int position;//�����λ��
	cin >> position >> value;

	if (position<1 || position>L->data + 1)
		return 0;//����λ�ò��Ϸ�

	//�������һ��Ҫ���i-1����㣬ѭ�����̵��м���ֻ�ǹ��ͣ�ֻ�иı�ָ������ǳ�·
	Node* p = L;//ָ��ͷ���

	//ѭ������ʱpָ���position-1�����
	for (int i = 0; i < position-1; i++) 
		p = p->next;
	
	Node* s = (Node*)malloc(sizeof(Node));
	s->next = p->next;
	p->next = s;
	s->data = value;

	L->data++; //����������
	return 1;
}


int deletelist(LinkList &L) {
	int position;//��ɾ����λ��
	cin >> position;
	if (position<1 || position>L->data)
		return 0;//λ�ò��Ϸ�

	Node* p = L;//ָ��ͷ���

	//ѭ������ʱpָ���position-1�����
	for (int i = 0; i < position - 1; i++)
		p = p->next;

	Node* q = p->next;
	p->next = (p->next)->next;
	free(q);//�ͷ��ڴ�
	L->data--;//���ȼ���
	return 1;

}

int findlist(LinkList& L) {
	int value;//����ѯ��ֵ
	cin >> value;

	Node* p = L->next;//ָ���һ�����
	int i = 1;
	for (p; p != NULL; p = p->next) {
		if (p->data == value) {
			cout << i << endl;//�������λ��
			return 1;//�ɹ���Ѱ
		}
		i++;
	}
	return 0;//û���ҵ�
}

void lengthoflist(LinkList &L) {
	cout << L->data << endl;
}

void freelist(LinkList &L) {
	Node* q = L;
	Node* p = NULL;
	while (q != NULL) {
		p = q->next;
		free(q);
		q = p;
	}
}

int main()
{
	LinkList L;
	creatlist(L);
	printlist(L);

	int k = insertlist(L);
	if (k == 1)
		printlist(L);
	else if (k == 0)
		cout << -1 << endl;

	k = deletelist(L);
	if (k == 1)
		printlist(L);
	else if (k == 0)
		cout << -1 << endl;

	k = findlist(L);
	if (k == 0)
		cout << -1 << endl;

	lengthoflist(L);

	freelist(L);

	return 0;
}