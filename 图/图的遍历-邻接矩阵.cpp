//图的遍历（邻接矩阵）
#include <iostream>
#include <stdbool.h>
#include <queue>
using namespace std;

#define MAX_NUM 30

typedef int VRType;//关系类型
typedef char VType;//顶点类型

//邻接矩阵结构
typedef struct ArcCell {
	VRType adj;//顶点关系类型，图为0或1，网为权值
	//InfoType *info;//弧相关信息指针
}ArcCell, AdjMatrix[MAX_NUM][MAX_NUM];

typedef struct {
	VType vexs[MAX_NUM];//顶点向量数组
	AdjMatrix arcs;//邻接矩阵
	int vexnum;//当前顶点数
	int	arcnum;//当前弧数
	int kind;//图的种类标识,1为有向图，2为有向网，3为无向图，4为无向网
}MGraph;

//邻接矩阵表示法构造无向图
void CreatUDG(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//输入顶点数和弧数


	//本题无顶点信息，无需管顶点向量数组

	//初始化邻接矩阵，默认为0
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//构造邻接矩阵
	//输入边的两个顶点的编号，而非顶点
	for (int k = 0; k < G.arcnum; k++) {
		int v1, v2;//顶点

		cin >> v1 >> v2;

		//存在关系置1,置对称弧
		G.arcs[v1][v2].adj = 1;
		G.arcs[v2][v1] = G.arcs[v1][v2];
	}
}

bool visited[MAX_NUM];//访问标识数组
int bbb = 1;

//从顶点i开始深度遍历
void DFS(MGraph& G, int i) {
	visited[i] = true;

	if (bbb == 1) {
		cout << i;
		bbb = 0;
	}
	else
		cout << ' ' << i;

	int j = 0;
	for (j = 0; j < G.vexnum; j++)
		if (G.arcs[i][j].adj != 0 && visited[j] == false)
			DFS(G, j);

}

//无向图的DFS遍历，递归实现,从编号最小开始
void DFSTraverse(MGraph& G) {
	//标识数组初始化
	for (int i = 0; i < G.vexnum; i++)
		visited[i] = false;

	for (int i = 0; i < G.vexnum; i++) {
		
		if (!visited[i]) {
			cout << '{';
			DFS(G, i);
			cout << '}';
		}
		bbb = 1;
	}		
	cout << endl;

	bbb = 1;
}


//无向图的BFS遍历，从编号最小开始,利用队列，非递归实现
void BFSTraverse(MGraph& G) {
	//标识数组初始化
	for (int i = 0; i < G.vexnum; i++)
		visited[i] = false;

	queue <int> Q;

	for (int i = 0; i < G.vexnum; i++) {
		if (!visited[i]) {
			cout << '{';

			cout << i;

			visited[i] = true;
			Q.push(i);

			while (!Q.empty()) {
				int k = Q.front();
				Q.pop();

				for (int j = 0; j < G.vexnum; j++) {
					if (G.arcs[k][j].adj != 0 && visited[j] == false) {
						cout << ' ' << j;
						visited[j] = true;
						Q.push(j);
					}
				}
			}
			cout <<  '}';
		}
	}

	cout << endl;
}

int main() {
	MGraph G;
	CreatUDG(G);
	DFSTraverse(G);
	BFSTraverse(G);
	return 0;
}