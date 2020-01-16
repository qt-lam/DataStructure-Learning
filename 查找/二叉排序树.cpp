#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

typedef int Elemtype;

//二叉排序树
typedef struct BitNode{
	Elemtype data;
	struct BitNode* lchild, *rchild;
}BitNode,*BitTree;

//将指针S指向的结点插入到二叉排序树T中
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

//输入一组数据元素的序列，构造二叉排序树
void CreatBST(BitTree& T) {
	BitTree s = NULL;
	T = NULL;//先定为空树
	int length = 0;//初始序列的长度，由本题题干

	cin >> length;//关键字长度

	for (int i = 0; i < length; i++) {
		s = (BitNode*)malloc(sizeof(BitNode));
		cin >> s->data;
		s->lchild = s->rchild = NULL;

		InserBST(T, s);
	}
}

void delNode(BitTree& T, BitTree p, BitTree f);
//寻找被删除的结点
int DeleteBST(BitTree& T, Elemtype key) {
	BitTree p, f;//当前结点 前驱结点

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

//删除结点
void delNode(BitTree& T, BitTree p, BitTree f) {
	BitTree s = NULL, q = NULL;//要去替换被删除的结点 前驱结点
	int tag = 0;

	if (!p->lchild)//左孩子不存在
		s = p->rchild;
	else if (!p->rchild) //右孩子不存在
		s = p->lchild;
	else {//左右孩子都存在
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

	//左孩子或者右孩子不存在的处理
	if (!tag) {
		if (!f)//删除头结点
			T = s;
		else if (f->lchild == p)
			f->lchild = s;
		else
			f->rchild = s;

		free(p);
	}
}


//查找结点,动态查找，找到返回1，没有插入后返回0
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

//先序遍历输出,无换行
void prioder_print(BitTree& T) {
	if (T) {
		cout << T->data << ' ';
		prioder_print(T->lchild);
		prioder_print(T->rchild);
	}
}


//计算平均查找长度
double cal_ave(BitTree& T) {
	BitTree s = NULL;
	queue<BitTree> Q;
	int lay = 0;//层次
	int number = 0;//当前层次的结点数目
	int total_number = 0;//总结点数目
	int length = 0;//平均查找长度;
	int last_laynumber = 0;//上一层的结点数，方便判断该层结点队列是否结束

	if (T) {
		Q.push(T);
		lay++;
		number++;
		last_laynumber = number;//下一层的上层结点
		total_number++;
		length += (lay * number);
		number = 0;//为下一层计数做准备		
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

//显示树形
void printree(BitTree& T, int n) {
	int i;
	char c = ' ';
	if (T) {
		printree(T->rchild, n + 1);
		for (i = 1; i <= n; i++)
			printf("%5c", c);//间隔5个
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
	cin >> key;//输入关键字

	//删除结果
	cout << DeleteBST(T, key) << endl;

	//查找结果
	cout << SearchBST(T, key) << endl;

	//先序遍历
	prioder_print(T);
	cout << endl;

	//计算平均查找长度
	cout << setiosflags(ios::fixed) << setprecision(2) << cal_ave(T) << endl;
	//是查找前还是查找后的结果还是初始序列

	/*cout << endl;
	printree(T, 0);*/

	return 0;
}