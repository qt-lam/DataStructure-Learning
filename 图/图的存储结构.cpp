//ͼ�Ĵ洢�ṹ
#include <iostream>
#include <limits.h>
using namespace std;


#define INF INT_MAX
#define MAX_NUM 30

typedef int VRType;//��ϵ����
typedef char VType;//��������


//�ڽӱ�ṹ
typedef struct ArcNode {
	int adjvex;//�û���ָ��Ķ���λ��
	ArcNode* nextarc;
	int adj;//�û���ص���Ϣ��Ȩֵ
}ArcNode;

typedef struct VNode {
	VType data;//������Ϣ
	ArcNode* firstarc;//ָ���һ�������ö���Ļ���ָ��
}VNnode,AdjList[MAX_NUM];

typedef struct {
	AdjList vertices;//�ڽӱ�ͷ����
	int vexnum;//������
	int arcnum;//����
	int kind;//ͼ�������ʶ��1Ϊ����ͼ��2Ϊ��������3Ϊ����ͼ��4Ϊ������
}ALGraph;

//�ڽӾ���ṹ
typedef struct ArcCell {
	VRType adj;//�����ϵ���ͣ�ͼΪ0��1����ΪȨֵ
	//InfoType *info;//�������Ϣָ��
}ArcCell,AdjMatrix[MAX_NUM][MAX_NUM];

typedef struct {
	VType vexs[MAX_NUM];//������������
	AdjMatrix arcs;//�ڽӾ���
	int vexnum;//��ǰ������
	int	arcnum;//��ǰ����
	int kind;//ͼ�������ʶ,1Ϊ����ͼ��2Ϊ��������3Ϊ����ͼ��4Ϊ������
}MGraph;

//���ض������ڽӾ����е��±�
int localvex(MGraph G, VType v) {
	for (int i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i])
			return i;
	}
	return -1;
}

//�ڽӾ����ʾ����������ͼ
void CreatDG(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//���붥�����ͻ���
	for (int i = 0; i < G.vexnum; i++)//��ȡ��������
		cin >> G.vexs[i];
	//��ʼ���ڽӾ���Ĭ��Ϊ0
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//�����ڽӾ���
	for (int k=0; k < G.arcnum; k++) {
		VType v1, v2;//����

		cin >> v1 >> v2;

		//��ȡ�����Ӧ�±�
		int i = localvex(G, v1);
		int j = localvex(G, v2);
		//���ڹ�ϵ��1
		G.arcs[i][j].adj = 1;
	}
}

//�ڽӾ����ʾ����������ͼ
void CreatUDG(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//���붥�����ͻ���
	for (int i = 0; i < G.vexnum; i++)//��ȡ��������
		cin >> G.vexs[i];
	//��ʼ���ڽӾ���Ĭ��Ϊ0
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//�����ڽӾ���
	for (int k=0; k < G.arcnum; k++) {
		VType v1, v2;//����

		cin >> v1 >> v2;

		//��ȡ�����Ӧ�±�
		int i = localvex(G, v1);
		int j = localvex(G, v2);
		//���ڹ�ϵ��1,�öԳƻ�
		G.arcs[i][j].adj = 1;
		G.arcs[j][i] = G.arcs[i][j];
	}
}

//�ڽӾ����ʾ������������
void CreatDN(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//���붥�����ͻ���
	for (int i = 0; i < G.vexnum; i++)//��ȡ��������
		cin >> G.vexs[i];
	//��ʼ���ڽӾ���,Ĭ��0������oj��0������Ϊ�����
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//�����ڽӾ���
	for (int k=0; k < G.arcnum; k++) {
		VType v1, v2;//����
		VRType w;//Ȩֵ

		cin >> v1 >> v2 >> w;

		//��ȡ�����Ӧ�±�
		int i = localvex(G, v1);
		int j = localvex(G, v2);
		//����Ȩֵ
		G.arcs[i][j].adj = w;
	}
}

//�ڽӾ����ʾ������������
void CreatUDN(MGraph& G) {
	cin >> G.vexnum >> G.arcnum;//���붥�����ͻ���
	for (int i = 0; i < G.vexnum; i++)//��ȡ��������
		cin >> G.vexs[i];
	//��ʼ���ڽӾ���,Ĭ��0������oj��0������Ϊ�����
	for (int i = 0; i < G.vexnum; i++) 
		for (int j = 0; j < G.vexnum; j++) 
			G.arcs[i][j] = { 0 };
	
	//�����ڽӾ���
	for (int k=0; k < G.arcnum; k++) {
		VType v1, v2;//����
		VRType w;//Ȩֵ

		cin >> v1 >> v2 >> w;

		//��ȡ�����Ӧ�±�
		int i = localvex(G, v1);
		int j = localvex(G, v2);
		//����Ȩֵ���öԳƻ�
		G.arcs[i][j].adj = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
}

//����ڽӾ���
void printarcs(MGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			cout << "    " << G.arcs[i][j].adj;
		}
		cout << endl;
	}
}

//�����ڽӾ����ʾ������ͼG
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

//���ڽӾ������ڽӱ����ʽ���
void printlist(MGraph& G) {

	if (G.kind == 1 || G.kind == 3) {
		//ͼ
		for (int i = 0; i < G.vexnum; i++) {
			cout << G.vexs[i] << "-->";
			for (int j = G.vexnum - 1; j >= 0; j--)
				if (G.arcs[i][j].adj == 1)
					cout << j << ' ';

			cout << endl;
		}
	}
	else if (G.kind == 2 || G.kind == 4) {
		//��
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