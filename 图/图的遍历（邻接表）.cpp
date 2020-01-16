//ͼ�Ĵ洢�ṹ
#include <iostream>
#include <limits.h>
#include <queue>
using namespace std;


#define INF INT_MAX
#define MAX_NUM 30

typedef int VRType;//��ϵ����
typedef int VType;//��������


//�ڽӱ�ṹ
typedef struct ArcNode {
	int adjvex;//�û���ָ��Ķ���λ��
	ArcNode* nextarc;
	VRType adj;//�û��洢����Ϣ��Ȩֵ����������ָ��ָ����Ϣ�飩
}ArcNode;

typedef struct VNode {
	VType data;//������Ϣ
	ArcNode* firstarc;//ָ���һ�������ö���Ļ���ָ��
}VNnode, AdjList[MAX_NUM];

typedef struct {
	AdjList vertices;//�ڽӱ�ͷ����
	int vexnum;//������
	int arcnum;//����
	int kind;//ͼ�������ʶ��1Ϊ����ͼ��2Ϊ��������3Ϊ����ͼ��4Ϊ������
}ALGraph;


//��������ͼ
void CreatUDG(ALGraph& A) {
	A.kind = 3;//����ͼ
	cin >> A.vexnum >> A.arcnum;//���붥�����ͱ���

	//��ʼ����ͷ������飬���ⶥ��Ϊ0~n-1
	for (int i = 0; i < A.vexnum; i++) {
		A.vertices[i].data = i;
		A.vertices[i].firstarc = NULL;
	}

	VType v1, v2;//����ͼֻ����ض��㣬��Ȩֵ
	for (int i = 0; i < A.arcnum; i++) {
		cin >> v1 >> v2;
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = v2;
		p->adj = 0;//����ͼ��Ȩֵ����ֵ0����������

		//ͷ�巨
		p->nextarc = A.vertices[v1].firstarc;
		A.vertices[v1].firstarc = p;

		//��˫��
		p = (ArcNode*)malloc(sizeof(ArcNode));//�ٴ�����ռ�
		p->adjvex = v1;
		p->adj = 0;

		p->nextarc = A.vertices[v2].firstarc;
		A.vertices[v2].firstarc = p;
	}
	
}


bool visited[MAX_NUM];////���ʱ�ʶ����

int bbb = 1;

//�Ӷ���i��ʼ��ȱ���
void DFS(ALGraph& A, int i) {
	visited[i] = true;

	if (bbb == 1) {
		cout << i;
		bbb = 0;
	}
	else
		cout << ' ' << i;

	int j = 0;
	ArcNode* p = A.vertices[i].firstarc;
	while (p != NULL) {
		j = p->adjvex;
		if (visited[j] == false)
			DFS(A, j);
		p = p->nextarc;
	}

}

//����ͼ��DFS�������ݹ�ʵ��,�ӱ����С��ʼ
void DFSTraverse(ALGraph& A) {
	//��ʶ�����ʼ��
	for (int i = 0; i < A.vexnum; i++)
		visited[i] = false;

	for (int i = 0; i < A.vexnum; i++) {

		if (!visited[i]) {
			cout << '{';
			DFS(A, i);
			cout << '}';
		}
		bbb = 1;
	}
	cout << endl;

	bbb = 1;
}

//����ͼ��BFS����,���ö��У��ǵݹ�ʵ��
void BFSTraverse(ALGraph& A) {
	//��ʶ�����ʼ��
	for (int i = 0; i < A.vexnum; i++)
		visited[i] = false;

	queue <int> Q;

	for (int i = 0; i < A.vexnum; i++) {
		if (!visited[i]) {
			cout << '{';

			cout << i;

			visited[i] = true;
			Q.push(i);

			while (!Q.empty()) {
				int k = Q.front();
				Q.pop();

				int j = 0;
				for (ArcNode* p = A.vertices[k].firstarc; p != NULL; p = p->nextarc) {
					j = p->adjvex;
					if (visited[j] == false) {
						cout << ' ' << j;
						visited[j] = true;
						Q.push(j);
					}
				}
			}
			cout << '}';
		}
	}

	cout << endl;
}

int main() {
	ALGraph A;
	CreatUDG(A);
	DFSTraverse(A);
	BFSTraverse(A);
	return 0;
}