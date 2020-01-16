//���������ж�ͼ�Ƿ��л�
#include <iostream>
#include <stack>
using namespace std;


#define MAX_NUM 30

typedef int VRType;//��ϵ����
typedef int VType;//��������

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
	int indegree[MAX_NUM];//�������������
}MGraph;


//�ڽӾ����ʾ������������,�����������������������ص�Ȩֵ��Ϣ
void CreatDN(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//���붥�����ͻ���
	for (int i = 0; i < G.vexnum; i++)//��ȡ��������
		G.vexs[i] = i + 1;//��ĿĬ���˶���Ϊ1-n����
	//��ʼ���ڽӾ���,Ĭ��0������oj��0������Ϊ�����
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//�����ڽӾ���
	for (int k = 0; k < G.arcnum; k++) {
		VType v1, v2;//����
		VRType w;//Ȩֵ

		cin >> v1 >> v2 >> w;

		//����Ȩֵ
		G.arcs[v1-1][v2-1].adj = w;
	}
	G.kind = 2;
}


//�Ը��������Ȼ�ȡ
void FindInDegree(MGraph& G) {

	//��������ʼ��
	for (int i = 0; i < G.vexnum; i++)
		G.indegree[i] = 0;

	//��ȡ���
	for (int i = 0; i < G.vexnum; i++) 
		for (int j = 0; j < G.vexnum; j++) 
			if (G.arcs[i][j].adj != 0) 
				G.indegree[j]++;
						
}


//����ɾ�߷����ж�ͼ�Ƿ��л�,�ڽӾ���
int TopologicalSort(MGraph& G) {
	FindInDegree(G);
	stack <int>s;//initial stack
	for (int i = 0; i < G.vexnum; i++) 
		if (G.indegree[i] == 0)
			s.push(i);
	
	int count = 0;

	while (!s.empty()) {
		int k = s.top();
		s.pop();//ɾ����
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