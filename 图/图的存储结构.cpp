//图的存储结构
#include <iostream>
#include <limits.h>
using namespace std;


#define INF INT_MAX
#define MAX_NUM 30

typedef int VRType;//关系类型
typedef char VType;//顶点类型


//邻接表结构
typedef struct ArcNode {
	int adjvex;//该弧所指向的顶点位置
	ArcNode* nextarc;
	int adj;//该弧相关的信息：权值
}ArcNode;

typedef struct VNode {
	VType data;//顶点信息
	ArcNode* firstarc;//指向第一条依附该顶点的弧的指针
}VNnode,AdjList[MAX_NUM];

typedef struct {
	AdjList vertices;//邻接表头数组
	int vexnum;//顶点数
	int arcnum;//弧数
	int kind;//图的种类标识：1为有向图，2为有向网，3为无向图，4为无向网
}ALGraph;

//邻接矩阵结构
typedef struct ArcCell {
	VRType adj;//顶点关系类型，图为0或1，网为权值
	//InfoType *info;//弧相关信息指针
}ArcCell,AdjMatrix[MAX_NUM][MAX_NUM];

typedef struct {
	VType vexs[MAX_NUM];//顶点向量数组
	AdjMatrix arcs;//邻接矩阵
	int vexnum;//当前顶点数
	int	arcnum;//当前弧数
	int kind;//图的种类标识,1为有向图，2为有向网，3为无向图，4为无向网
}MGraph;

//返回顶点在邻接矩阵中的下标
int localvex(MGraph G, VType v) {
	for (int i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i])
			return i;
	}
	return -1;
}

//邻接矩阵表示法构造有向图
void CreatDG(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//输入顶点数和弧数
	for (int i = 0; i < G.vexnum; i++)//获取顶点向量
		cin >> G.vexs[i];
	//初始化邻接矩阵，默认为0
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//构造邻接矩阵
	for (int k=0; k < G.arcnum; k++) {
		VType v1, v2;//顶点

		cin >> v1 >> v2;

		//获取顶点对应下标
		int i = localvex(G, v1);
		int j = localvex(G, v2);
		//存在关系置1
		G.arcs[i][j].adj = 1;
	}
}

//邻接矩阵表示法构造无向图
void CreatUDG(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//输入顶点数和弧数
	for (int i = 0; i < G.vexnum; i++)//获取顶点向量
		cin >> G.vexs[i];
	//初始化邻接矩阵，默认为0
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//构造邻接矩阵
	for (int k=0; k < G.arcnum; k++) {
		VType v1, v2;//顶点

		cin >> v1 >> v2;

		//获取顶点对应下标
		int i = localvex(G, v1);
		int j = localvex(G, v2);
		//存在关系置1,置对称弧
		G.arcs[i][j].adj = 1;
		G.arcs[j][i] = G.arcs[i][j];
	}
}

//邻接矩阵表示法构造有向网
void CreatDN(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//输入顶点数和弧数
	for (int i = 0; i < G.vexnum; i++)//获取顶点向量
		cin >> G.vexs[i];
	//初始化邻接矩阵,默认0（根据oj是0，树上为无穷大）
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//构造邻接矩阵
	for (int k=0; k < G.arcnum; k++) {
		VType v1, v2;//顶点
		VRType w;//权值

		cin >> v1 >> v2 >> w;

		//获取顶点对应下标
		int i = localvex(G, v1);
		int j = localvex(G, v2);
		//输入权值
		G.arcs[i][j].adj = w;
	}
}

//邻接矩阵表示法构造无向网
void CreatUDN(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//输入顶点数和弧数
	for (int i = 0; i < G.vexnum; i++)//获取顶点向量
		cin >> G.vexs[i];
	//初始化邻接矩阵,默认0（根据oj是0，树上为无穷大）
	for (int i = 0; i < G.vexnum; i++) 
		for (int j = 0; j < G.vexnum; j++) 
			G.arcs[i][j] = { 0 };
	
	//构造邻接矩阵
	for (int k=0; k < G.arcnum; k++) {
		VType v1, v2;//顶点
		VRType w;//权值

		cin >> v1 >> v2 >> w;

		//获取顶点对应下标
		int i = localvex(G, v1);
		int j = localvex(G, v2);
		//输入权值，置对称弧
		G.arcs[i][j].adj = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
}

//输出邻接矩阵
void printarcs(MGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			cout << "    " << G.arcs[i][j].adj;
		}
		cout << endl;
	}
}

//采用邻接矩阵表示法构造图G
void CreatGraph(MGraph& G) {
	cin >> G.kind;
	switch (G.kind)
	{
		case 1:CreatDG(G); break;
		case 2:CreatDN(G); break;
		case 3:CreatUDG(G); break;
		case 4:CreatUDN(G); break;
	}
}

//将邻接矩阵以邻接表的形式输出
void printlist(MGraph& G) {

	if (G.kind == 1 || G.kind == 3) {
		//图
		for (int i = 0; i < G.vexnum; i++) {
			cout << G.vexs[i] << "-->";
			for (int j = G.vexnum - 1; j >= 0; j--)
				if (G.arcs[i][j].adj == 1)
					cout << j << ' ';

			cout << endl;
		}
	}
	else if (G.kind == 2 || G.kind == 4) {
		//网
		for (int i = 0; i < G.vexnum; i++) {
			cout << G.vexs[i] << "-->";
			for (int j = G.vexnum - 1; j >= 0; j--) {
				if (G.arcs[i][j].adj != 0) {
					cout << j << ',' << G.arcs[i][j].adj << ' ';
				}
					
			}
			cout << endl;
		}
	}
	
}




int main()
{
	MGraph G;
	CreatGraph(G);
	for (int i = 0; i < G.vexnum; i++)
		cout << G.vexs[i] << ' ';
	cout << endl;
	printarcs(G);
	printlist(G);
	return 0;
}