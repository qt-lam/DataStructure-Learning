//��������Ӧ��-�շ�������
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <iomanip>
using namespace std;

//�շ�����
//��˳������ʽ���洢�շ���������Ϣ������Ȩֵ������㣬���Һ��ӽ��
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;

//ָ��շ��������ָ������
typedef char** HuffmancCode;

//�������� select2min
//�������� ��1-max��������Ѱ�Һշ������и��ڵ�Ϊ0����Ȩֵ��С���������s1 s2��max���Ϊȫ�������-1��
//����˵�� �շ��������ָ��HT��Ѱ�������������ֵmax��Ѱ�ҵ���Ž��ͨ�����ü�¼��s1 s2��
//����ʵ�� �ڸ����������ҳ�����Ҫ���Ȩֵ��С��㣬��¼��ţ����ҳ��ڶ�СȨֵ�Ľ�㣬��¼��ţ����Ƚ����˳��
//	   �����С���Ȩֵ��űȽϴ��򽻻����ߵ���Ų��Ҹ���s1 s2����Ϊԭ�շ�������Ҫ���ҳ���������СȨֵ��㰴˳������
void select2min(HuffmanTree HT, int max, int& s1, int& s2) {
	int min1 = 0, min2 = 0;//��¼������С�������
	unsigned int minweight = 0;//�м������¼�ݶ�����СȨֵ
	int minnumber = 0;//�м������¼��СȨ��ֵ�����
	//�м����
	HTNode* p = NULL;
	int i = 0;
	int k = 1;//������ǵ�һ�γ������������Ľ��Ϊ��ʼȨֵ��С��

	for (i = 1, p = HT; i <= max; i++) {
		//��һ�����ڵ�Ϊ0���ȶ�Ϊ��СȨ��ֵ
		if (k == 1 && p[i].parent == 0) {
			minweight = p[i].weight;
			minnumber = i;
			k = 0;
		}

		if (p[i].weight < minweight&&p[i].parent == 0) {
			minweight = p[i].weight;
			minnumber = i;
		}
	}

	min1 = minnumber;
	s1 = minnumber;//��һ�� ��СȨֵ��ŵ�

	k = 1;
	for (i = 1, p = HT; i <= max; i++) {

		//�ų���С�ĸ��ţ��ҵڶ�С
		if (i == min1)
			continue;

		//��һ�����ڵ�Ϊ0���ȶ�Ϊ��СȨֵ
		if (k == 1 && p[i].parent == 0) {
			minweight = p[i].weight;
			minnumber = i;
			k = 0;
		}

		if (p[i].weight < minweight&&p[i].parent == 0) {
			minweight = p[i].weight;
			minnumber = i;
		}
	}

	min2 = minnumber;
	s2 = minnumber;//�ڶ��� �ڶ�СȨֵ��ŵ�

	//��Ϊ���������㷨����СȨֵ��һ������ǰ�棬������Ҫ����ʵ������������������׼�շ�����
	if (s1 > s2) {
		minnumber = s1;
		s1 = s2;
		s2 = minnumber;
	}
}

//�������� HuffmanCoding
//�������� ���ݶ�ӦȨֵ���������ַ��ĺշ�������Ϣ�ͺշ�������
//����˵�� �շ��������ָ��HT���ã�ָ��շ�������ָ�������ָ�����ã�Ȩֵ����w��Ԫ�ظ���n
void HuffmanCoding(HuffmanTree& HT, HuffmancCode& HC, int* w, int n) {
	int m = 2 * n - 1;//�շ������������
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//0��λ�ò�ʹ��

	//�м����
	HTNode* p = NULL;
	int i = 0;

	//1-n������Ȩ�أ���ʼ����ĸ�ͺ��ӽ��
	for (p = HT + 1, i = 1; i <= n; i++, p++) {
		p->weight = w[i];
		p->lchild = p->rchild = p->parent = 0;
	}

	//����ʣ��λ��ȫ���������
	for (p; i <= m; i++, p++, w++)
		p->lchild = p->rchild = p->parent = p->weight = 0;

	//�����շ�����������Ϣ�����������
	for (i = n + 1; i <= m; i++) {
		int s1 = 0, s2 = 0;
		select2min(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//��Ҷ�ӽ�㵽�����������ÿ���ַ��ĺշ�������
	HC = (HuffmancCode)malloc((n + 1) * sizeof(char*));//n���ַ������ͷָ������,��0���ռ䲻��
	char* cd = (char*)malloc(n * sizeof(char));//�������ռ�
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++) {
		int start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char*)malloc((n - start) * sizeof(char));//�����i���ַ��ı���ռ�
		strcpy(HC[i], &cd[start]);
	}
	free(cd);//�ͷ�
}

//�������� compress
//�������� ���ݺշ������룬��ASCII�ļ�ѹ���ɶ�Ӧ�ַ��շ��������γɵ�ѹ���ļ�
//����˵�� char*���ʹ�ѹ���ļ���filename
//����ʵ�� 1.���ȶ�ȡ�ļ����ݻ�ȡ�ַ�Ƶ��Ȩֵ��Ϣ�����ݴ���Ϣ���ɶ�Ӧ�ĺշ������Լ��շ������룻
//		   2.�Ƚ�ԭ�ļ��������Ϣ�������ַ�Ȩֵ���뵽ѹ���ļ��У����ڽ�ѹʱ����Ϣ��ԭ
//		   3.�ٴζԴ�ѹ���ļ�����һ���ַ�һ���ַ��Ķ�ȡ������Ӧ�ĺշ���������Ϣ��ʱ�洢������洢�ı���λ�����ڵ���8λ����ʱ��
//		   ͨ��λ�������뵽һ��unsigned char�����У��ٽ��ñ������뵽ѹ���ļ��У�ʵ����Ϣѹ��
//		   4.����˳��ͳ�������ļ��Ĵ�С����������ʵ�ֺ�������ע��������
int compress(char* filename) {
	FILE* file;//���ļ�
	int w[128];//�洢�ļ��е��ַ�Ȩ�� ��¼�ַ�1-127

	int byte1 = 0;//Դ�ļ��ֽ���
	int byte2 = 0;//ѹ���ļ��ֽ���

	//Ȩֵ�����ʼ��
	for (int i = 0; i < 128; i++) {
		w[i] = 0;
	}

	file = fopen(filename, "rb");//��Դ�ļ�
	if (file == 0) {
		cout << "open failed" << endl;
		return 0;//����
	}

	//�����ı���ͳ�ƴ�Ƶ����¼Ȩ��
	unsigned char c;
	while (1) {
		
		c = fgetc(file);
		if (feof(file))
			break;

		
		w[c]++;
		byte1++;
	}

	//����շ������ͱ���
	HuffmanTree HT;//�շ�����
	HuffmancCode HC;//�շ�������
	HuffmanCoding(HT, HC, w, 127);//���ɺշ�������

	//����ѹ���ļ���
	char p[50];
	strcpy(p, filename);
	strcat(p, ".qjy");

	//�ٴα�����ͨ���շ���������ѹ�������ļ�
	FILE* compressfile = fopen(p, "wb");//��Դ���򴦴���ѹ���ļ�

	//ʡ�Դ�ʧ��

	fwrite(&byte1, sizeof(byte1), 1, compressfile);//��ԭ�ļ����ֽ�������С���洢
	byte2 += sizeof(int);
	fwrite(w, sizeof(w), 1, compressfile);//���ַ�Ȩֵѹ�������ļ�����Ȼ��0���ռ䲻�ã�����Ҳд�룩
	byte2 += (128 * sizeof(int));//ѹ���ļ�ͽ��512�ֽڣ����Դ��ļ�ѹ��������

	rewind(file);//�ٴα���Դ�ļ�����Ҫ��ָ��ر굽��ͷ
	unsigned char temp = '\0';//������8λ�շ�������תΪ1�ֽ����ݿ�
	string unit;//��ʱ�洢������ת���ĺշ�������
	while (1) {

		c = fgetc(file);//��ȡһ���ַ�

		if (feof(file))
			break;

		//cout << "ѹ���ַ�intֵ" << (int)c << endl;
		unit += HC[c];//�����ַ��ĺշ���������뵽�ַ����ͱ������������

		//��unit�д洢�ĺշ���������ڵ���8ʱ�����Ͻ�ǰ8λ�ó������в�����1byte
		while ((unit.length()) >= 8) {
			temp = '\0';//��ʼ�����
			for (int i = 0; i < 8; i++) {
				temp = temp << 1;//�߼�����1λ
				if (unit[i] == '1')
					temp = temp | 1;
			}
			auto p = unit.begin();//ָ���һ��λ��
			unit.erase(p, p + 8);//��ǰ8λ���


			fwrite(&temp, sizeof(temp), 1, compressfile);//�����ֽ����ݿ�д��ѹ���ļ���

			byte2++;
		}
	}

	//�����Ȼʣ�಻��8λ���ȵĺշ������룬��û�иպñ�8������Ŀ��bit��
	if (unit.length() > 0) {
		temp = '\0';
		for (int i = 0; i < (int)unit.length(); i++) {
			temp = temp << 1;
			if (unit[i] == '1')
				temp = temp | 1;
		}

		for (int i = 0; i < (int)(8 - unit.length()); i++)
			temp = (temp << 1);//������ת�Ƶ���λ

		fwrite(&temp, sizeof(temp), 1, compressfile);//�����ֽ����ݿ�д��ѹ���ļ���
		byte2++;
	}

	cout << "--------------------------------------ѹ�����--------------------------------------------" << endl;
	cout << "ѹ��ǰ�ļ����� : " << filename << ' ' << "��С : " << byte1 << "�ֽ�" << endl;
	cout << "ѹ�����ļ����� : " << p << ' ' << "��С : " << byte2 << "�ֽ�" << endl;
	cout << "ѹ���� : " << setiosflags(ios::fixed) << setprecision(2) << (double)byte2 / byte1 * 100 << "%" << endl;

	//�ر��ļ�
	fclose(compressfile);
	fclose(file);

	//ѹ���������ͷ��ڴ�
	free(HT);

	//���ֱ��ͷ�
	for (int i = 1; i <= 127; i++)
		free(HC[i]);
	free(HC);

	return 1;
}


//�������� decompress
//�������� ����Ӧѹ���ļ����н�ѹ����ԭ�ļ���ʵ������ѹ����ѹ
//����˵�� char*���ʹ���ѹ�ļ���filename
//����˵�� 1.���Ȼ�ȡ����ѹ�ļ����ƣ��ж����Ƿ�Ϊ�ɽ�ѹ�ļ�
//		   2.���ȶ�ȡѹ���ļ���ͷ��¼������ַ�Ȩֵ��Ϣ�Լ�ԭ�ļ���С��Ϣ
//		   3.��ȡ������Ϣ�����ɺշ������ͺշ������룬����ѹ���ļ��еı�������λ������ÿһ�ֽڵ���Ϣһ����һ����ȥ��ȡ��
//		   ͨ���շ��������ҵ�Ҷ�ӽ���Ӧ���ַ����������ѹ�ļ���
//		   4.˳��ͳ�ƴ�С��Ϣ
int decompress(char* filename) {
	FILE* file;//���ļ�
	int w[128];//�洢�ļ��е��ַ�Ȩ�� ��¼�ַ�1-127

	int byte1 = 0;//ѹ���ļ��м�¼��ԭ���ļ��ֽ�������С��,����ֵ
	int byte2 = 0;//��ѹ����ļ��ֽ�����ʵ��ֵ
	int byte3 = 0;//ѹ���ļ��Ĵ�С

	//Ȩֵ�����ʼ��
	for (int i = 0; i < 128; i++) {
		w[i] = 0;
	}

	file = fopen(filename, "rb");//��Դ�ļ�
	if (file == NULL) {
		cout << "open failed" << endl;
		return 0;//����
	}

	fread(&byte1, sizeof(int), 1, file);//����ѹ���ļ��д洢�Ĺ���ԭ�ļ��Ĵ�С��Ϣ
	byte3 += 4;

	for (int i = 0; i < 128; i++) {
		fread(&w[i], sizeof(int), 1, file);
	}

	byte3 += (128 * 4);

	//׼����ԭ�շ������ͺշ������룬Ϊ��ѹ��׼��
	HuffmanTree HT;
	HuffmancCode HC;
	HuffmanCoding(HT, HC, w, 127);

	//�жϸ��ļ��Ƿ�ɽ�ѹ�����ҽ�����ԭ�ļ�����
	char p[50];
	char pfinal[50] = "qjy-";
	int str_length = strlen(filename);
	if (strcmp(".qjy", &filename[str_length - 4]) == 0) {
		strncpy(p, filename, str_length - 4);//��ȡ����ѹ�ļ�����
		p[str_length - 4] = '\0';
		strcat(pfinal, p);
	}
	else {
		//��׺��.qjy���ļ��޷���ѹ
		cout << "������ļ������ϸó����ѹ��ʽ" << endl;
		return 0;
	}

	FILE* decompressfile = fopen(pfinal, "wb");//������ѹ�ļ�
	//ʡ�Դ�ʧ��
	unsigned char temp = '\0';//��ȡ�շ�������
	int top = 2 * 127 - 1;//�շ����������еĸ����
	int length = byte1;//��¼ԭ��С

	while (length) {
		temp = fgetc(file);//��ȡ8bit
		byte3++;//ѹ���ļ��Ĵ�С

		for (int i = 0; i < 8; i++) {
			if ((temp & 128) == 0)
				top = HT[top].lchild;//����
			else
				top = HT[top].rchild;//�Һ���

			//����Ҷ�ӽ��
			if (top <= 127) {

				//cout << "��ԭ�ַ�intֵ" << (int)top << endl;
				fputc((char)top, decompressfile);//���Ҷ�ӽ�������ַ�

				length--;
				byte2++;//���ļ���С��1

				if (length == 0)
					break;//����

				top = 127 * 2 - 1;//��λ�������
			}

			temp = temp << 1;//���û�е���Ҷ�ӽ�㣬��������������ȥ
		}
	}

	cout << "--------------------------------------��ѹ���--------------------------------------------" << endl;
	cout << "ѹ��ǰ�ļ����� : " << filename << ' ' << "��С : " << byte3 << "�ֽ�"<< endl;
	cout << "ѹ�����ļ����� : " << pfinal << ' ' << "��С : " << byte2 << "�ֽ�" << endl;

	//�ر��ļ�
	fclose(file);
	fclose(decompressfile);


	//ѹ���������ͷ��ڴ�
	free(HT);

	//���ֱ��ͷ�
	for (int i = 1; i <= 127; i++)
		free(HC[i]);
	free(HC);

	return 1;
}

int main()
{
	char s[40];//��ȡ������ļ���
	int choice = 0;

	while (1) {
		//system("cls");//����
		cout << "���������ѡ����" << endl;
		cout << "1.ѹ���ļ�" << endl;
		cout << "2.��ѹ�ļ�" << endl;
		cout << "3.�˳�����" << endl;

		cin >> choice;
		if (choice == 3)//�˳�����
			break;
		else if (choice == 1) {
			cout << "�������ѹ���ļ���" << endl;
			cin >> s;
			compress(s);
		}
		else if (choice == 2) {
			cout << "���������ѹ�ļ���" << endl;
			cin >> s;
			decompress(s);
		}
		else 
			cout << "�������" << endl;

		cout << endl;
	}
	return 0;
}

//�����Ϣ��������ʡ�ԣ����ڳ����ͼ������