#include <iostream>
#include <queue>
using namespace std;

#define MAX_NUM 30 //最多max_num-1
typedef int VRType;//关系类型
typedef int VType;//顶点类型

//邻接矩阵结构
typedef struct ArcCell {
	VRType adj;//顶点关系类型，图为0或1，网为权值
	//InfoType *info;//弧相关信息指针
}ArcCell, AdjMatrix[MAX_NUM][MAX_NUM];

typedef struct {
	AdjMatrix arcs;//邻接矩阵
	int vexnum;//当前顶点数
	int	arcnum;//当前弧数
	int kind;//图的种类标识,1为有向图，2为有向网，3为无向图，4为无向网
	int degree[MAX_NUM];//图中顶点的度
}MGraph;


//函数名称 CreatMG
//函数功能 使用邻接矩阵表示法构造无向图
//函数实现 使用邻接矩阵表示，过程中获取顶点数和弧数，并且记录每一条边的过程中统计顶点的度
//注意事项 针对本题，第0号空间始终 不使用
void CreatMG(MGraph& G) {
	cout << "输入顶点数和弧数" << endl;
	cin >> G.vexnum >> G.arcnum;//输入顶点数和弧数

	//初始化邻接矩阵，默认为0
	for (int i = 0; i <= G.vexnum; i++)
		for (int j = 0; j <= G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//初始化度数组
	for (int i = 0; i <= G.vexnum; i++)
		G.degree[i] = 0;
	

	//构造邻接矩阵
	//输入边的两个顶点的编号，而非顶点
	for (int k = 1; k <= G.arcnum; k++) {
		int v1, v2;//顶点

		cout << "输入边的两个顶点" << endl;
		cin >> v1 >> v2;

		//存在关系置1,置对称弧
		G.arcs[v1][v2].adj = 1;
		G.arcs[v2][v1] = G.arcs[v1][v2];

		//度增加
		G.degree[v1]++;
		G.degree[v2]++;
	}

	G.kind = 3;
}


//全局变量，记录递归过程中的相关数据
int way[MAX_NUM];//记录所走过路径顶点
int number = 0;//记录目前走过路径的数量

//函数名称 DFS_draw
//函数参数 MGraph类型的无向图；当前顶点；计数参数，主函数中调用时需为0
//函数功能 利用深度优先搜索以及递归函数来实现获取所有一笔画情况
//函数实现 对于单个顶点，搜索下一条可走路径：如果可走，处理当前递归的邻接矩阵（图），表示已走过，并将其记录，
//并且判断是否全部走完，没有全部走完进入下一层递归，全部走完后就输出路径，复原状态进行下一条一笔画路径的查找；
//如果不可走，利用循环查找下一条可走路径
void DFS_draw(MGraph G, int point, int count) {
	for (int i = 1; i <= G.vexnum; i++) {
		//进入该路径的条件,能进入说明不会死路
		if (G.arcs[point][i].adj == 1 && (G.degree[i] >= 2 || count == G.arcnum - 1)) {

			//该路径走过后的处理
			G.arcs[point][i].adj = G.arcs[i][point].adj = 0;
			G.degree[point]--;
			G.degree[i]--;

			//记录该路径点
			count++;
			way[count] = i;

			//当所有路径都被遍历后，输出
			if (count == G.arcnum) {
				//输出路径
				for (int j = 0; j <= G.arcnum; j++)
					cout << way[j] << ' ';
				cout << endl;		
				number++;
			}
			else 
				DFS_draw(G, i, count);//尚未走完，继续往下走
			
			//走完一个完整路径后，复原状态，走下一个可走顶点
			G.arcs[point][i].adj = G.arcs[i][point].adj = 1;
			G.degree[point]++;
			G.degree[i]++;

			count--;
		}
	}
}


int main()
{
	MGraph G;
	CreatMG(G);


	cout << "\n一笔画结果 : " << endl;
	//针对本题使用欧拉的部分理论
	for (int i = 1; i <= G.vexnum; i++) {
		if (G.degree[i] % 2 == 1) {//度为奇数的点才可为起点
			way[0] = i;//起点
			DFS_draw(G, i, 0);
		}
	}
	cout << "共" << number << "种" << endl;

	return 0;
}