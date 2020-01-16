
//关键路径
#include <iostream>
#include <stdbool.h>
#include <stack>
#include <queue>
using namespace std;


#define MAX_NUM 101//1-100

typedef int VRType;//关系类型
typedef int VType;//顶点类型

//邻接矩阵结构
typedef struct ArcCell {
	VRType adj;//顶点关系类型，图为0或1，网为权值
}ArcCell, AdjMatrix[MAX_NUM][MAX_NUM];

typedef struct {
	VType vexs[MAX_NUM];//顶点向量数组,本题由于顶点确定，就不操作了
	AdjMatrix arcs;//邻接矩阵
	int vexnum;//当前顶点数
	int	arcnum;//当前弧数
	int kind;//图的种类标识,1为有向图，2为有向网，3为无向图，4为无向网
	int indegree[MAX_NUM];//各顶点入度数组
	int ve[MAX_NUM];//各顶点事件的最早发生时间数组 使用1-n
	int vl[MAX_NUM];//各顶点事件的最迟发生时间数组 使用1-n
}MGraph;

//邻接矩阵表示法构造有向网
void CreatUDG(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//输入顶点数和弧数
	G.kind = 2;

	//初始化邻接矩阵，默认为0
	//0 0 不使用
	for (int i = 0; i <= G.vexnum; i++)
		for (int j = 0; j <= G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//构造邻接矩阵
	//输入边的两个顶点的编号，而非顶点
	for (int k = 0; k < G.arcnum; k++) {
		int v1, v2;//顶点
		int w1;

		cin >> v1 >> v2 >> w1;

		//存在关系
		G.arcs[v1][v2].adj = w1;
	}
}

//对各顶点的入度获取
void FindInDegree(MGraph& G) {

	//入度数组初始化
	for (int i = 0; i <= G.vexnum; i++)
		G.indegree[i] = 0;

	//获取入度
	for (int i = 1; i <= G.vexnum; i++)
		for (int j = 1; j <= G.vexnum; j++)
			if (G.arcs[i][j].adj != 0)
				G.indegree[j]++;

}

queue<int> f4;
//拓扑排序，获取事件最早发生时间，并且得到一组拓扑排序序列
int TopologicalSort(stack<int>&topo, MGraph& G) {
	FindInDegree(G);
	stack <int>s;//initial stack

	//初始化事件最早发生时间数组
	for (int i = 0; i <= G.vexnum; i++)
		G.ve[i] = 0;

	//记录入度为0的顶点/事件
	for (int i = 1; i <= G.vexnum; i++)
		if (G.indegree[i] == 0)
			s.push(i);

	int count = 0;

	while (!s.empty()) {
		int k = s.top();
		s.pop();//删除边

		topo.push(k);
		f4.push(k);

		count++;
		for (int i = 1; i <= G.vexnum; i++) {
			if (G.arcs[k][i].adj != 0) {
				G.indegree[i]--;

				if (G.indegree[i] == 0)
					s.push(i);

				if (G.ve[k] + G.arcs[k][i].adj > G.ve[i])
					G.ve[i] = G.ve[k] + G.arcs[k][i].adj;

			}
		}
	}

	//有回路，失败
	if (count < G.vexnum)
		return 0;

	//无回路，成功
	return 1;
}


//求关键路径与关键活动，拓扑序列和图的邻接矩阵
int CriticalPath(MGraph& G) {
	stack<int>topo;
	int length = 0;

	if (!TopologicalSort(topo, G)) {
		cout << 0 << endl;//有回路
		return 0;
	}

	//初始化vl
	int max = 0;
	for (int i = 1; i <= G.vexnum; i++) 
		if (G.ve[i] > max)
			max = G.ve[i];
	

	for (int i = 1; i <= G.vexnum; i++) {
		G.vl[i] = max;
	}

	//求事件最迟发生时间
	while (!topo.empty()) {
		//出栈
		int j = topo.top();
		topo.pop();

		for (int k = 1; k <= G.vexnum; k++) {
			if (G.arcs[j][k].adj != 0) {
				int dut = G.arcs[j][k].adj;

				if (G.vl[k] - dut < G.vl[j])
					G.vl[j] = G.vl[k] - dut;
			}
		}
	}

	queue<int>key;
	while (!f4.empty()) {
		int j = f4.front();
		f4.pop();
		for (int k = 1; k <= G.vexnum; k++) {
			if (G.arcs[j][k].adj != 0) {
				int dut = G.arcs[j][k].adj;

				int ee = G.ve[j];
				int el = G.vl[k] - dut;

				if (ee == el) {
					length += dut;
					key.push(j);
					key.push(k);
				}
			}
		}
	}

	cout << length << endl;
	while (!key.empty()) {
		int j = key.front();
		key.pop();
		int k = key.front();
		key.pop();
		cout << j << "->" << k << endl;
	}
	return 1;
}

int main()
{
	MGraph G;
	CreatUDG(G);
	CriticalPath(G);

	return 0;
}