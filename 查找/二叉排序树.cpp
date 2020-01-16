#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

typedef int Elemtype;

//����������
typedef struct BitNode{
	Elemtype data;
	struct BitNode* lchild, *rchild;
}BitNode,*BitTree;

//��ָ��Sָ��Ľ����뵽����������T��
void InserBST(BitTree& T, BitTree S) {
	BitTree p = NULL, q = NULL;

	if (!T)
		T = S;
	else {
		p = T;
		while (p) {
			q = p;
			if (S->data < p->data)
				p = p->lchild;
			else
				p = p->rchild;
		}

		if (S->data < q->data)
			q->lchild = S;
		else
			q->rchild = S;
	}
}

//����һ������Ԫ�ص����У��������������
void CreatBST(BitTree& T) {
	BitTree s = NULL;
	T = NULL;//�ȶ�Ϊ����
	int length = 0;//��ʼ���еĳ��ȣ��ɱ������

	cin >> length;//�ؼ��ֳ���

	for (int i = 0; i < length; i++) {
		s = (BitNode*)malloc(sizeof(BitNode));
		cin >> s->data;
		s->lchild = s->rchild = NULL;

		InserBST(T, s);
	}
}

void delNode(BitTree& T, BitTree p, BitTree f);
//Ѱ�ұ�ɾ���Ľ��
int DeleteBST(BitTree& T, Elemtype key) {
	BitTree p, f;//��ǰ��� ǰ�����

	p = T;
	f = NULL;

	while (p) {
		if (p->data == key) {
			delNode(T, p, f);
			return 1;
		}
		else if (p->data > key) {
			f = p;
			p = p->lchild;
		}
		else {
			f = p;
			p = p->rchild;
		}
	}
	return 0;
}

//ɾ�����
void delNode(BitTree& T, BitTree p, BitTree f) {
	BitTree s = NULL, q = NULL;//Ҫȥ�滻��ɾ���Ľ�� ǰ�����
	int tag = 0;

	if (!p->lchild)//���Ӳ�����
		s = p->rchild;
	else if (!p->rchild) //�Һ��Ӳ�����
		s = p->lchild;
	else {//���Һ��Ӷ�����
		q = p;
		s = p->lchild;

		while (s->rchild) {
			q = s;
			s = s->rchild;
		}

		p->data = s->data;
		if (p == q)
			q->lchild = s->lchild;
		else
			q->rchild = s->lchild;

		free(s);
		tag = 1;
	}

	//���ӻ����Һ��Ӳ����ڵĴ���
	if (!tag) {
		if (!f)//ɾ��ͷ���
			T = s;
		else if (f->lchild == p)
			f->lchild = s;
		else
			f->rchild = s;

		free(p);
	}
}


//���ҽ��,��̬���ң��ҵ�����1��û�в���󷵻�0
int SearchBST(BitTree& T, Elemtype key) {
	BitTree p = NULL, q = NULL;
	p = T;

	while (p) {
		if (p->data == key)
			return 1;
		else if (p->data > key) {
			q = p;
			p = p->lchild;
		}
		else {
			q = p;
			p = p->rchild;
		}
	}

	BitTree s = (BitNode*)malloc(sizeof(BitNode));
	s->data = key;
	s->lchild = s->rchild = NULL;
	
	if (!T)
		T = s;
	else if (q->data > key)
		q->lchild = s;
	else
		q->rchild = s;

	return 0;
}

//����������,�޻���
void prioder_print(BitTree& T) {
	if (T) {
		cout << T->data << ' ';
		prioder_print(T->lchild);
		prioder_print(T->rchild);
	}
}


//����ƽ�����ҳ���
double cal_ave(BitTree& T) {
	BitTree s = NULL;
	queue<BitTree> Q;
	int lay = 0;//���
	int number = 0;//��ǰ��εĽ����Ŀ
	int total_number = 0;//�ܽ����Ŀ
	int length = 0;//ƽ�����ҳ���;
	int last_laynumber = 0;//��һ��Ľ�����������жϸò�������Ƿ����

	if (T) {
		Q.push(T);
		lay++;
		number++;
		last_laynumber = number;//��һ����ϲ���
		total_number++;
		length += (lay * number);
		number = 0;//Ϊ��һ�������׼��		
	}

	
	while (!Q.empty()) {

		s = Q.front();
		Q.pop();	

		if (s->lchild) {
			Q.push(s->lchild);
			total_number++;
			number++;
		}

		if (s->rchild) {
			Q.push(s->rchild);
			total_number++;
			number++;
		}

		last_laynumber--;

		if (last_laynumber == 0) {
			lay++;
			length = length + (lay*number);
			last_laynumber = number;
			number = 0;			
		}
	}

	return (double)length / total_number;
}

//��ʾ����
void printree(BitTree& T, int n) {
	int i;
	char c = ' ';
	if (T) {
		printree(T->rchild, n + 1);
		for (i = 1; i <= n; i++)
			printf("%5c", c);//���5��
		cout << T->data << endl;
		printree(T->lchild, n + 1);
	}
}


int main()
{
	BitTree T;
	CreatBST(T);

	//cout << endl;
	//printree(T, 0);

	int key = 0;
	cin >> key;//����ؼ���

	//ɾ�����
	cout << DeleteBST(T, key) << endl;

	//���ҽ��
	cout << SearchBST(T, key) << endl;

	//�������
	prioder_print(T);
	cout << endl;

	//����ƽ�����ҳ���
	cout << setiosflags(ios::fixed) << setprecision(2) << cal_ave(T) << endl;
	//�ǲ���ǰ���ǲ��Һ�Ľ�����ǳ�ʼ����

	/*cout << endl;
	printree(T, 0);*/

	return 0;
}