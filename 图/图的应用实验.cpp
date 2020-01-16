#include <iostream>
#include <queue>
using namespace std;

#define MAX_NUM 30 //���max_num-1
typedef int VRType;//��ϵ����
typedef int VType;//��������

//�ڽӾ���ṹ
typedef struct ArcCell {
	VRType adj;//�����ϵ���ͣ�ͼΪ0��1����ΪȨֵ
	//InfoType *info;//�������Ϣָ��
}ArcCell, AdjMatrix[MAX_NUM][MAX_NUM];

typedef struct {
	AdjMatrix arcs;//�ڽӾ���
	int vexnum;//��ǰ������
	int	arcnum;//��ǰ����
	int kind;//ͼ�������ʶ,1Ϊ����ͼ��2Ϊ��������3Ϊ����ͼ��4Ϊ������
	int degree[MAX_NUM];//ͼ�ж���Ķ�
}MGraph;


//�������� CreatMG
//�������� ʹ���ڽӾ����ʾ����������ͼ
//����ʵ�� ʹ���ڽӾ����ʾ�������л�ȡ�������ͻ��������Ҽ�¼ÿһ���ߵĹ�����ͳ�ƶ���Ķ�
//ע������ ��Ա��⣬��0�ſռ�ʼ�� ��ʹ��
void CreatMG(MGraph& G) {
	cout << "���붥�����ͻ���" << endl;
	cin >> G.vexnum >> G.arcnum;//���붥�����ͻ���

	//��ʼ���ڽӾ���Ĭ��Ϊ0
	for (int i = 0; i <= G.vexnum; i++)
		for (int j = 0; j <= G.vexnum; j++)
			G.arcs[i][j] = { 0 };

	//��ʼ��������
	for (int i = 0; i <= G.vexnum; i++)
		G.degree[i] = 0;
	

	//�����ڽӾ���
	//����ߵ���������ı�ţ����Ƕ���
	for (int k = 1; k <= G.arcnum; k++) {
		int v1, v2;//����

		cout << "����ߵ���������" << endl;
		cin >> v1 >> v2;

		//���ڹ�ϵ��1,�öԳƻ�
		G.arcs[v1][v2].adj = 1;
		G.arcs[v2][v1] = G.arcs[v1][v2];

		//������
		G.degree[v1]++;
		G.degree[v2]++;
	}

	G.kind = 3;
}


//ȫ�ֱ�������¼�ݹ�����е��������
int way[MAX_NUM];//��¼���߹�·������
int number = 0;//��¼Ŀǰ�߹�·��������

//�������� DFS_draw
//�������� MGraph���͵�����ͼ����ǰ���㣻�����������������е���ʱ��Ϊ0
//�������� ����������������Լ��ݹ麯����ʵ�ֻ�ȡ����һ�ʻ����
//����ʵ�� ���ڵ������㣬������һ������·����������ߣ�����ǰ�ݹ���ڽӾ���ͼ������ʾ���߹����������¼��
//�����ж��Ƿ�ȫ�����꣬û��ȫ�����������һ��ݹ飬ȫ�����������·������ԭ״̬������һ��һ�ʻ�·���Ĳ��ң�
//��������ߣ�����ѭ��������һ������·��
void DFS_draw(MGraph G, int point, int count) {
	for (int i = 1; i <= G.vexnum; i++) {
		//�����·��������,�ܽ���˵��������·
		if (G.arcs[point][i].adj == 1 && (G.degree[i] >= 2 || count == G.arcnum - 1)) {

			//��·���߹���Ĵ���
			G.arcs[point][i].adj = G.arcs[i][point].adj = 0;
			G.degree[point]--;
			G.degree[i]--;

			//��¼��·����
			count++;
			way[count] = i;

			//������·���������������
			if (count == G.arcnum) {
				//���·��
				for (int j = 0; j <= G.arcnum; j++)
					cout << way[j] << ' ';
				cout << endl;		
				number++;
			}
			else 
				DFS_draw(G, i, count);//��δ���꣬����������
			
			//����һ������·���󣬸�ԭ״̬������һ�����߶���
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


	cout << "\nһ�ʻ���� : " << endl;
	//��Ա���ʹ��ŷ���Ĳ�������
	for (int i = 1; i <= G.vexnum; i++) {
		if (G.degree[i] % 2 == 1) {//��Ϊ�����ĵ�ſ�Ϊ���
			way[0] = i;//���
			DFS_draw(G, i, 0);
		}
	}
	cout << "��" << number << "��" << endl;

	return 0;
}