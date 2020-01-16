
//�ؼ�·��
#include <iostream>
#include <stdbool.h>
#include <stack>
#include <queue>
using namespace std;


#define MAX_NUM 101//1-100

typedef int VRType;//��ϵ����
typedef int VType;//��������

//�ڽӾ���ṹ
typedef struct ArcCell {
	VRType adj;//�����ϵ���ͣ�ͼΪ0��1����ΪȨֵ
}ArcCell, AdjMatrix[MAX_NUM][MAX_NUM];

typedef struct {
	VType vexs[MAX_NUM];//������������,�������ڶ���ȷ�����Ͳ�������
	AdjMatrix arcs;//�ڽӾ���
	int vexnum;//��ǰ������
	int	arcnum;//��ǰ����
	int kind;//ͼ�������ʶ,1Ϊ����ͼ��2Ϊ��������3Ϊ����ͼ��4Ϊ������
	int indegree[MAX_NUM];//�������������
	int ve[MAX_NUM];//�������¼������緢��ʱ������ ʹ��1-n
	int vl[MAX_NUM];//�������¼�����ٷ���ʱ������ ʹ��1-n
}MGraph;

//�ڽӾ����ʾ������������
void CreatUDG(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//���붥�����ͻ���
	G.kind = 2;

	//��ʼ���ڽӾ���Ĭ��Ϊ0
	//0 0 ��ʹ��
	for (int i = 0; i <= G.vexnum; i++)
		for (int j = 0; j <= G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//�����ڽӾ���
	//����ߵ���������ı�ţ����Ƕ���
	for (int k = 0; k < G.arcnum; k++) {
		int v1, v2;//����
		int w1;

		cin >> v1 >> v2 >> w1;

		//���ڹ�ϵ
		G.arcs[v1][v2].adj = w1;
	}
}

//�Ը��������Ȼ�ȡ
void FindInDegree(MGraph& G) {

	//��������ʼ��
	for (int i = 0; i <= G.vexnum; i++)
		G.indegree[i] = 0;

	//��ȡ���
	for (int i = 1; i <= G.vexnum; i++)
		for (int j = 1; j <= G.vexnum; j++)
			if (G.arcs[i][j].adj != 0)
				G.indegree[j]++;

}

queue<int> f4;
//�������򣬻�ȡ�¼����緢��ʱ�䣬���ҵõ�һ��������������
int TopologicalSort(stack<int>&topo, MGraph& G) {
	FindInDegree(G);
	stack <int>s;//initial stack

	//��ʼ���¼����緢��ʱ������
	for (int i = 0; i <= G.vexnum; i++)
		G.ve[i] = 0;

	//��¼���Ϊ0�Ķ���/�¼�
	for (int i = 1; i <= G.vexnum; i++)
		if (G.indegree[i] == 0)
			s.push(i);

	int count = 0;

	while (!s.empty()) {
		int k = s.top();
		s.pop();//ɾ����

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

	//�л�·��ʧ��
	if (count < G.vexnum)
		return 0;

	//�޻�·���ɹ�
	return 1;
}


//��ؼ�·����ؼ�����������к�ͼ���ڽӾ���
int CriticalPath(MGraph& G) {
	stack<int>topo;
	int length = 0;

	if (!TopologicalSort(topo, G)) {
		cout << 0 << endl;//�л�·
		return 0;
	}

	//��ʼ��vl
	int max = 0;
	for (int i = 1; i <= G.vexnum; i++) 
		if (G.ve[i] > max)
			max = G.ve[i];
	

	for (int i = 1; i <= G.vexnum; i++) {
		G.vl[i] = max;
	}

	//���¼���ٷ���ʱ��
	while (!topo.empty()) {
		//��ջ
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