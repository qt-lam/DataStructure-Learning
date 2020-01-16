//拓扑排序判断图是否有环
#include <iostream>
#include <stack>
using namespace std;


#define MAX_NUM 30

typedef int VRType;//关系类型
typedef int VType;//顶点类型

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
	int indegree[MAX_NUM];//各顶点入度数组
}MGraph;


//邻接矩阵表示法构造有向网,本题是有向网，存在与边相关的权值信息
void CreatDN(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//输入顶点数和弧数
	for (int i = 0; i < G.vexnum; i++)//获取顶点向量
		G.vexs[i] = i + 1;//题目默认了顶点为1-n整数
	//初始化邻接矩阵,默认0（根据oj是0，树上为无穷大）
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//构造邻接矩阵
	for (int k = 0; k < G.arcnum; k++) {
		VType v1, v2;//顶点
		VRType w;//权值

		cin >> v1 >> v2 >> w;

		//输入权值
		G.arcs[v1-1][v2-1].adj = w;
	}
	G.kind = 2;
}


//对各顶点的入度获取
void FindInDegree(MGraph& G) {

	//入度数组初始化
	for (int i = 0; i < G.vexnum; i++)
		G.indegree[i] = 0;

	//获取入度
	for (int i = 0; i < G.vexnum; i++) 
		for (int j = 0; j < G.vexnum; j++) 
			if (G.arcs[i][j].adj != 0) 
				G.indegree[j]++;
						
}


//利用删边法来判断图是否有环,邻接矩阵
int TopologicalSort(MGraph& G) {
	FindInDegree(G);
	stack <int>s;//initial stack
	for (int i = 0; i < G.vexnum; i++) 
		if (G.indegree[i] == 0)
			s.push(i);
	
	int count = 0;

	while (!s.empty()) {
		int k = s.top();
		s.pop();//删除边
		count++;
		for (int i = 0; i < G.vexnum; i++) {
			if (G.arcs[k][i].adj != 0) {
				G.indegree[i]--;

				if (G.indegree[i] == 0)
					s.push(i);
			}			
		}
	}

	if (count < G.vexnum)
		return 0;

	return 1;
}

int main()
{
	MGraph G;
	CreatDN(G);
	cout << TopologicalSort(G) << endl;

	return 0;
}