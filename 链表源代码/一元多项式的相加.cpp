//һԪ����ʽ�����
//����˳��洢�ṹʱ�������˷�ʱ�䣨����ÿһ��ֱ��ָ��������
//��������洢�洢ÿһ�������������Ϣ������һЩ�������������ոպ�ָ����1-n���򷴶��˷ѿռ䣩������������ǽ�ʡ�ռ䣬����Ч�ʻ��

//����������һ�ζ���ʽ����ӣ�����ǰ���Ƕ���ʽ��û��ָ���ظ�����Ҵ�С����˳������

#include <iostream>
using namespace std;

typedef int elemtype;

typedef struct linklist {
	elemtype pi;
	elemtype ei;
	linklist* next;
}Node, *HeadNodeP;

//β�巨������˳��Ϊ������Ҫ��ָ������
int creatlist(HeadNodeP& L) {
	L = (HeadNodeP)malloc(sizeof(Node));
	//ͷ����ʼ��
	L->ei = -1;
	L->pi = -1;
	L->next = NULL;

	//��ȡ��ʼ��������Ŀ
	int length = 0;
	cin >> length;

	Node* s;
	Node* p = L;
	for (int i = 0; i < length; i++) {
		s = (Node*)malloc(sizeof(Node));
		cin >> s->pi >> s->ei;
		s->next = p->next;
		p->next = s;
		p = s;
	}

	return 1;
}

//��������ʽ��ӣ������������c�У�������c��δ��ʼ����������abָ������;ab�����ڲ���仯����������֮ǰ�Ľṹ
void addlist(HeadNodeP& a, HeadNodeP &b, HeadNodeP& c) {
	Node* pa = a->next;//ָ���һ������
	Node* pb = b->next;
	Node* ppre = c = a;//��a��ͷ����c
	Node* tobefree = NULL;

	while (pa&&pb) {
		if (pa->ei < pb->ei) {
			ppre = pa;
			pa = pa->next;
		}
		else if (pa->ei == pb->ei) {
			pa->pi += pb->pi;
			if (pa->pi == 0) {
				tobefree = pa;
				pa = pa->next;
				free(tobefree);

				tobefree = pb;
				pb = pb->next;
				free(tobefree);
			}
			else {
				ppre = pa;
				pa = pa->next;
				pb = pb->next;
			}
		}
		else if(pa->ei>pb->ei){
			ppre->next = pb;
			pb = pb->next;
			(ppre->next)->next = pa;
			ppre = ppre->next;		
		}
	}
	ppre->next = pa ? pa : pb;
	free(b);
}

void printlist(HeadNodeP& L) {
	Node* p = L->next;
	for (p; p != NULL; p = p->next) {
		cout << p->pi << ' ' << p->ei << endl;
	}
}

int main()
{
	HeadNodeP a;
	HeadNodeP b;
	creatlist(a);
	creatlist(b);
	//printlist(a);
	//printlist(b);
	HeadNodeP(c);
	addlist(a, b, c);
	cout << endl;
	printlist(c);
	return 0;
}