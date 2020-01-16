//图的存储结构
#include <iostream>
#include <limits.h>
#include <queue>
using namespace std;


#define INF INT_MAX
#define MAX_NUM 30

typedef int VRType;//关系类型
typedef int VType;//顶点类型


//邻接表结构
typedef struct ArcNode {
	int adjvex;//该弧所指向的顶点位置
	ArcNode* nextarc;
	VRType adj;//该弧存储的信息：权值（书中利用指针指向信息块）
}ArcNode;

typedef struct VNode {
	VType data;//顶点信息
	ArcNode* firstarc;//指向第一条依附该顶点的弧的指针
}VNnode, AdjList[MAX_NUM];

typedef struct {
	AdjList vertices;//邻接表头数组
	int vexnum;//顶点数
	int arcnum;//弧数
	int kind;//图的种类标识：1为有向图，2为有向网，3为无向图，4为无向网
}ALGraph;


//创建无向图
void CreatUDG(ALGraph& A) {
	A.kind = 3;//无向图
	cin >> A.vexnum >> A.arcnum;//输入顶点数和边数

	//初始化表头结点数组，该题顶点为0~n-1
	for (int i = 0; i < A.vexnum; i++) {
		A.vertices[i].data = i;
		A.vertices[i].firstarc = NULL;
	}

	VType v1, v2;//无向图只有相关顶点，无权值
	for (int i = 0; i < A.arcnum; i++) {
		cin >> v1 >> v2;
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = v2;
		p->adj = 0;//无向图无权值，赋值0无特殊意义

		//头插法
		p->nextarc = A.vertices[v1].firstarc;
		A.vertices[v1].firstarc = p;

		//置双向
		p = (ArcNode*)malloc(sizeof(ArcNode));//再次申请空间
		p->adjvex = v1;
		p->adj = 0;

		p->nextarc = A.vertices[v2].firstarc;
		A.vertices[v2].firstarc = p;
	}
	
}


bool visited[MAX_NUM];////访问标识数组

int bbb = 1;

//从顶点i开始深度遍历
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

//无向图的DFS遍历，递归实现,从编号最小开始
void DFSTraverse(ALGraph& A) {
	//标识数组初始化
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

//无向图的BFS遍历,利用队列，非递归实现
void BFSTraverse(ALGraph& A) {
	//标识数组初始化
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