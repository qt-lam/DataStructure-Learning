//���ʽ��ֵ
//ջ��Ҫ��˳��ջ������ջ������ʹ��˳��ջʵ��ջ�Ļ���caoz

//��Ҫ������������ȷ�����׺תΪ��׺���ʽ��

#include <iostream>
#include <string.h>
using namespace std;

const int maxsize = 30;
const int addsize = 10;

typedef int selemtype;

//��ջ
typedef struct {
	selemtype* base;
	selemtype* top;
	int stacksize;
}SqStack;

//��ʼ����ջ,��ʼ��������������л�ȡ
int initstack(SqStack& L) {
	/*int maxsize = 0;
	cin >> maxsize;*/

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
//��Ա��ʽ��ֵһ��û���趨���������������ջ���󽫼��������ڴ�
int stackfull(SqStack& L) {
	if (L.base + L.stacksize == L.top) {//ջ��ָ�����һ��λ�ó����Ķ�ջ���ڴ淶Χ
		L.base = (selemtype*)realloc((void*)L.base,sizeof(selemtype)*(L.stacksize + addsize));//�������룬����Χ
		return 0;
		//��return1 �޸ĳ� return0
	}
	else
		return 0;
}

//��ֵvalueѹջ������1������ɹ�������0��ջ��ʧ��
//�޸ĺ�һ�����Բ����ɹ���ֻ�Ƿ��ص�ֵ�����壬�����������ֲ����Ƿ�ɹ�
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

//���ջ������Ԫ��
void printstack(SqStack& L) {
	selemtype* p = L.top;

	while (p != L.base) {
		p--;
		cout << *p << ' ';
	}
	cout << endl;
}

//�ͷ��ڴ棬����ջ
void freestack(SqStack& L) {
	free(L.base);
}


int getxy(int c) {
	int xy = 0;
	switch (c)
	{
		case '+':
			xy = 0;
			break;
		case '-':
			xy = 1;
			break;
		case '*':
			xy = 2;
			break;
		case '/':
			xy = 3;
			break;
		case '(':
			xy = 4;
			break;
		case ')':
			xy = 5;
			break;
		case '=':
			xy = 6;
			break;
	}
	return xy;
}

//�Ƚ����ȼ����û�ȡ����������ַ���ջ����������Ƚ����ȼ�
char precede(selemtype top,char c) {

	//+ - * / ( ) =

	char compare[7][7] = {
		'>','>','<','<','<','>','>',
		'>','>','<','<','<','>','>',
		'>','>','>','>','<','>','>',
		'>','>','>','>','<','>','>',
		'<','<','<','<','<','=','?',
		'>','>','>','>','?','>','>',
		'<','<','<','<','<','?','='
	};
	int x = getxy(top);
	int y = getxy(c);
	return compare[x][y];
}


int getvalue(int a, int b, int c) {
	int value = 0;
	switch (c) {
		case '+':
			value = a + b;
			break;
		case '-':
			value = a - b;
			break;
		case '*':
			value = a * b;
			break;
		case '/':
			value = a / b;
			break;
	}	
	return value;
}

int errorinput(int c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '='||c=='('||c==')')
		return 1;
	else if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}



int value_expression() {
	SqStack OPTR, OPND;//���źͲ�����ջ
	initstack(OPTR);
	initstack(OPND);
	int c = '=';
	stackpush(OPTR, c);

	int k = 0;//�ж��Ƿ���ʮλ���Լ�����
	//int i = 1;//�ж��Ƿ������������η��ţ���3+-4�� �����ı�ʾ
	//int fushu = 0;
	int tem = 0;

	c = getchar();
	while (c != '=' || *(OPTR.top - 1) != '=') {

		if (!errorinput(c)) {
			cout << "ERROR" << endl;
			return 0;
		}			

		if (c >= '0'&&c <= '9') {
			c -= '0';
			if (k == 1) {
				stackpop(OPND, tem);
				c = tem * 10 + c;
			}
			/*if (fushu == 1) {
				c = 0 - c;
				fushu = 0;
			}*/
			stackpush(OPND, c);
			k = 1;
			//i = 0;
			c = getchar();
		}
		else {
			k = 0;

			////����������ڴ��������Ӧ�ò������
			//if (i == 1 && c == '-') {
			//	fushu = 1;
			//	i = 0;
			//	c = getchar();
			//	continue;
			//}

			//i = 1;
			switch (precede(*(OPTR.top - 1), c))
			{
				case '<':
					stackpush(OPTR, c);
					c = getchar();
					break;
				case '=':
					stackpop(OPTR, c);
					c = getchar();
					break;
				case '>':
					if (*(OPTR.top - 1) == '/'&&*(OPND.top - 1) == 0) {
						cout << "ERROR" << endl;
						return 0;
					}

					int a, b, operato;
					stackpop(OPND, b);
					stackpop(OPND, a);
					stackpop(OPTR, operato);
					stackpush(OPND, getvalue(a, b, operato));
					break;
			}
		}
	}
	cout << *(OPND.top - 1) << endl;
	return 1;
}



int main() {
	value_expression();

	return 0;
}