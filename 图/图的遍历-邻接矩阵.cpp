//ͼ�ı������ڽӾ���
#include <iostream>
#include <stdbool.h>
#include <queue>
using namespace std;

#define MAX_NUM 30

typedef int VRType;//��ϵ����
typedef char VType;//��������

//�ڽӾ���ṹ
typedef struct ArcCell {
	VRType adj;//�����ϵ���ͣ�ͼΪ0��1����ΪȨֵ
	//InfoType *info;//�������Ϣָ��
}ArcCell, AdjMatrix[MAX_NUM][MAX_NUM];

typedef struct {
	VType vexs[MAX_NUM];//������������
	AdjMatrix arcs;//�ڽӾ���
	int vexnum;//��ǰ������
	int	arcnum;//��ǰ����
	int kind;//ͼ�������ʶ,1Ϊ����ͼ��2Ϊ��������3Ϊ����ͼ��4Ϊ������
}MGraph;

//�ڽӾ����ʾ����������ͼ
void CreatUDG(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//���붥�����ͻ���


	//�����޶�����Ϣ������ܶ�����������

	//��ʼ���ڽӾ���Ĭ��Ϊ0
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//�����ڽӾ���
	//����ߵ���������ı�ţ����Ƕ���
	for (int k = 0; k < G.arcnum; k++) {
		int v1, v2;//����

		cin >> v1 >> v2;

		//���ڹ�ϵ��1,�öԳƻ�
		G.arcs[v1][v2].adj = 1;
		G.arcs[v2][v1] = G.arcs[v1][v2];
	}
}

bool visited[MAX_NUM];//���ʱ�ʶ����
int bbb = 1;

//�Ӷ���i��ʼ��ȱ���
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

//����ͼ��DFS�������ݹ�ʵ��,�ӱ����С��ʼ
void DFSTraverse(MGraph& G) {
	//��ʶ�����ʼ��
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


//����ͼ��BFS�������ӱ����С��ʼ,���ö��У��ǵݹ�ʵ��
void BFSTraverse(MGraph& G) {
	//��ʶ�����ʼ��
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