//����Ļ�������
#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct Node {
	ElemType  data;
	Node  *next ;
}Node, *LinkList;//��㣬ͷָ��


//β�巨��ÿ�ξ���ǰ���������Ԫ�� for function9
//�ı�汾��������Ԫ�ظ�����������0�������
int creatlist9(LinkList& L) {
	Node* s;

	int value = 0;
	int length = 0;//����
	L = (LinkList)malloc(sizeof(Node));//����ͷ���
	L->next = NULL;
	L->data = 0;//ͷ���������洢������

	//cin >> length;//��ȡ����ʱ����ĳ���
	//L->data = length;

	Node* p = L;
	while (1) {
		cin >> value;
		if (value == 0)
			break;
		s = (Node *)(malloc)(sizeof(Node));  //return 0 waiting

		s->data = value;
		s->next = NULL;
		length++;

		p->next = s;
		p = s;
	}

	L->data = length;
	return 1;
}

//ͷ�巨��ÿ�ξ���ͷ���������Ԫ��
int creatlist(LinkList& L) {
	Node* s;
	int length = 0;//����
	L = (LinkList)malloc(sizeof(Node));//����ͷ���
	L->next = NULL;
	L->data = 0;//ͷ���������洢������

	cout << "����1" << endl;
	cout << "������Ҫ������������" << endl;
	cin >> length;//��ȡ����ʱ����ĳ���
	L->data = length;

	cout << "��������������Ԫ��" << endl;
	for (int i = 0; i < length; i++) {
		s = (Node *)(malloc)(sizeof(Node));  
		if (s == NULL) {
			cout << "����ʧ��" << endl;
			return 0;
		}
		//return 0 waiting
		cin >> s->data;
		s->next = L->next;
		L->next = s;
	}
	return 1;
}

//������������Ԫ��
void printlist(LinkList& L) {

	Node* p;

	cout << "����2" << '\n' << "������Ϣ����" << endl;

	for (p = L->next; p != NULL; p = p->next) {
		cout << p->data << ' ';
	}
	cout << endl;
}

//����һ��Ԫ��,�����ڻ�ȡԪ��ֵ
int insertlist(LinkList& L) {
	int value;//�������ֵ
	int position;//�����λ��

	cout << "����3" << '\n' << "������Ҫ�����λ�ú�����ֵ" << endl;
	
	cin >> position >> value;

	if (position<1 || position>L->data + 1) {
		cout << "λ�ò��Ϸ�" << endl;
		return 0;//����λ�ò��Ϸ�
	}

	//�������һ��Ҫ���i-1����㣬ѭ�����̵��м���ֻ�ǹ��ͣ�ֻ�иı�ָ������ǳ�·
	Node* p = L;//ָ��ͷ���

	//ѭ������ʱpָ���position-1�����
	for (int i = 0; i < position - 1; i++)
		p = p->next;

	Node* s = (Node*)malloc(sizeof(Node));
	s->next = p->next;
	p->next = s;
	s->data = value;

	L->data++; //����������
	return 1;
}

//ɾ��һ��Ԫ�أ������ڻ�ȡҪɾ����λ��
int deletelist(LinkList &L) {
	int position;//��ɾ����λ��
	
	cout << "����4"<<'\n'<<"������Ҫɾ����λ��" << endl;

	cin >> position;
	if (position<1 || position>L->data) {
		cout << "λ�ò��Ϸ�" << endl;
		return 0;//λ�ò��Ϸ�
	}

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

//����һ��Ԫ�أ�����������λ��
int findlist(LinkList& L) {
	int value;//����ѯ��ֵ

	cout << "����5\n������Ҫ���ҵ�Ԫ��ֵ" << endl;
	cin >> value;

	Node* p = L->next;//ָ���һ�����
	int i = 1;
	for (p; p != NULL; p = p->next) {
		if (p->data == value) {
			cout << "λ���� " ;
			cout << i << endl;
			return 1;//�ɹ���Ѱ
		}
		i++;
	}
	cout << "���޼�¼" << endl;
	return 0;//û���ҵ�
}

//��ǰ������ĳ���
void lengthoflist(LinkList &L) {
	cout << "����6\n��ǰ����Ϊ " << endl;
	cout << L->data << endl;
}

//�����������
void reverselist(LinkList& L) {
	Node* ppre = L;
	Node* pcur = L->next;
	Node* pnext = NULL;
	int length = 0;

	while (pcur != NULL) {
		pnext = pcur->next;
		pcur->next = ppre;
		if (ppre == L) {
			pcur->next = NULL;
			length = L->data;//������������
			free(L);
		}
		ppre = pcur;
		pcur = pnext;
	}

	Node* s = (Node*)malloc(sizeof(Node));
	s->next = ppre;
	s->data = length;
	L = s;

	cout << "����7\n�����ѳɹ�����" << endl;
}

//ȥ�ص�����
void quchong(LinkList& L) {
	Node* ppre = NULL;//ǰ���
	Node* pcur = NULL;//��ǰ���
	Node* pnext = NULL;//����
	Node *pflag = NULL;//��Ҫ�ȽϵĽ��

	//�ӵ�һ����ʼ�Ƚ�
	for (pflag = L->next; pflag != NULL; pflag = pflag->next) {

		pcur = pflag->next;
		ppre = pflag;

		while (pcur != NULL) {
			pnext = pcur->next;
			if (pcur->data == pflag->data) {
				ppre->next = pnext;
				free(pcur);
				pcur = pnext;
			}
			else {
				ppre = ppre->next;
				pcur = pcur->next;
			}
		}
	}
	cout << "��ǰ����ɹ�ȥ��" << endl;
}

//���շǵݼ�������������
void sortlist(LinkList&L) {
	Node* p = NULL;
	Node* q = NULL;

	int min = 0;

	for (p = L->next; p != NULL; p = p->next) {
		min = p->data;
		for (q = p->next; q != NULL; q = q->next) {
			if (q->data < min) {
				min = q->data;
				q->data = p->data;
				p->data = min;
			}
		}
	}
}


//�����������ϲ���һ��
void mergelist(LinkList& a, LinkList& b, LinkList& c) {
	Node* pa = a->next;
	Node* pb = b->next;
	Node * pc = c = a;//ͷ���
	c->data = a->data + b->data;//�������;
	
	while (pa&&pb) {
		if (pa->data <= pb->data) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(b);
	cout << "�ɹ��ϲ�" << endl;
}

//�ͷ��ڴ�
void freelist(LinkList &L) {
	Node* q = L;
	Node* p = NULL;
	while (q != NULL) {
		p = q->next;
		free(q);
		q = p;
	}
}

void menu() {
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "����ʵ�飨��������Ľ���Ϊͷ�巨��" << endl;
	cout << "����1��������������ȡ��ʼԪ��" << endl;
	cout << "����2����������е�����Ԫ����Ϣ" << endl;
	cout << "����3����ѡ��λ���в���һ����Ԫ��" << endl;
	cout << "����4��ɾ��һ��ָ��λ�õ�Ԫ��" << endl;
	cout << "����5������Ԫ��ֵ�����Ҹ�Ԫ���Ƿ����" << endl;
	cout << "����6�������ǰ����ĳ���" << endl;
	cout << "����7�����õ�ǰ����" << endl;
	cout << "����8���Ե�ǰ�������ȥ�ز���" << endl;
	cout << "����9������������������зǵݼ�����������ͺϲ�����" << endl;
	cout << "����0���˳���ǰ����" << endl;
	cout << "-------------------------------------------------------------------------" << endl;
}

int main()
{
	LinkList L;
	int k = 0;

	do {
		system("cls");
		menu();
		cin >> k;
		system("cls");
		if (k == 0)
			break;
		else if (k == 1)
			creatlist(L);
		else if (k == 2)
			printlist(L);
		else if (k == 3)
			insertlist(L);
		else if (k == 4)
			deletelist(L);
		else if (k == 5)
			findlist(L);
		else if (k == 6)
			lengthoflist(L);
		else if (k == 7)
			reverselist(L);
		else if (k == 8)
			quchong(L);
		else if (k == 9) {
			LinkList a, b, c;
			cout << "����9" << endl;
			cout << "�������������֣�ÿһ�ж�����һ������ĳ�ʼ�������ݣ�ÿһ�е��������0�����������" << endl;
			creatlist9(a);
			creatlist9(b);
			sortlist(a);
			sortlist(b);
			mergelist(a, b, c);
			cout << "�Ѿ��ɹ��ϲ���˳��Ϊ�ǵݼ�" << endl;
			printlist(c);
			
			freelist(c);
		}

		cout << endl;
		cout << "�밴���������������" << endl;
		system("pause");
	} while (1);

	freelist(L);

	return 0;
}