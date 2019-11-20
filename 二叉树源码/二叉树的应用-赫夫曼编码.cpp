//二叉树的应用-赫夫曼编码
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <iomanip>
using namespace std;

//赫夫曼树
//以顺序表的形式来存储赫夫曼树的信息，包括权值，父结点，左右孩子结点
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;

//指向赫夫曼编码的指针数组
typedef char** HuffmancCode;

//函数名称 select2min
//函数功能 在1-max的区间内寻找赫夫曼树中父节点为0，且权值最小的两个结点s1 s2（max最大为全部结点数-1）
//参数说明 赫夫曼树结点指针HT，寻找区间的序号最大值max，寻找的序号结果通过引用记录到s1 s2中
//函数实现 在该区间内先找出满足要求的权值最小结点，记录序号；再找出第二小权值的结点，记录序号，最后比较序号顺序，
//	   如果最小结点权值序号比较大，则交换二者的序号并且赋给s1 s2（因为原赫夫曼编码要求找出的两个最小权值结点按顺序排序）
void select2min(HuffmanTree HT, int max, int& s1, int& s2) {
	int min1 = 0, min2 = 0;//记录两个最小结点的序号
	unsigned int minweight = 0;//中间参数记录暂定的最小权值
	int minnumber = 0;//中间参数记录最小权重值的序号
	//中间参数
	HTNode* p = NULL;
	int i = 0;
	int k = 1;//用来标记第一次出现满足条件的结点为初始权值最小点

	for (i = 1, p = HT; i <= max; i++) {
		//第一个父节点为0的先定为最小权重值
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
	s1 = minnumber;//第一个 最小权值序号点

	k = 1;
	for (i = 1, p = HT; i <= max; i++) {

		//排除最小的干扰，找第二小
		if (i == min1)
			continue;

		//第一个父节点为0的先定为最小权值
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
	s2 = minnumber;//第二个 第二小权值序号点

	//因为按照上述算法，最小权值点一定会在前面，所以需要根据实际情况来调整以满足标准赫夫曼树
	if (s1 > s2) {
		minnumber = s1;
		s1 = s2;
		s2 = minnumber;
	}
}

//函数名称 HuffmanCoding
//函数功能 根据对应权值数组生成字符的赫夫曼树信息和赫夫曼编码
//参数说明 赫夫曼树结点指针HT引用，指向赫夫曼编码指针数组的指针引用，权值数组w，元素个数n
void HuffmanCoding(HuffmanTree& HT, HuffmancCode& HC, int* w, int n) {
	int m = 2 * n - 1;//赫夫曼树结点总数
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//0号位置不使用

	//中间参数
	HTNode* p = NULL;
	int i = 0;

	//1-n先输入权重，初始化父母和孩子结点
	for (p = HT + 1, i = 1; i <= n; i++, p++) {
		p->weight = w[i];
		p->lchild = p->rchild = p->parent = 0;
	}

	//表中剩余位置全部清空置零
	for (p; i <= m; i++, p++, w++)
		p->lchild = p->rchild = p->parent = p->weight = 0;

	//建立赫夫曼树，将信息存至数组表中
	for (i = n + 1; i <= m; i++) {
		int s1 = 0, s2 = 0;
		select2min(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//从叶子结点到根结点逆向求每个字符的赫夫曼编码
	HC = (HuffmancCode)malloc((n + 1) * sizeof(char*));//n个字符编码的头指针数组,第0个空间不用
	char* cd = (char*)malloc(n * sizeof(char));//分配编码空间
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++) {
		int start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char*)malloc((n - start) * sizeof(char));//分配第i个字符的编码空间
		strcpy(HC[i], &cd[start]);
	}
	free(cd);//释放
}

//函数名称 compress
//函数功能 根据赫夫曼编码，将ASCII文件压缩成对应字符赫夫曼编码形成的压缩文件
//参数说明 char*类型待压缩文件名filename
//函数实现 1.首先读取文件内容获取字符频数权值信息，根据此信息生成对应的赫夫曼树以及赫夫曼编码；
//		   2.先将原文件的相关信息，比如字符权值输入到压缩文件中，便于解压时的信息还原
//		   3.再次对待压缩文件进行一个字符一个字符的读取，将对应的赫夫曼编码信息暂时存储，如果存储的编码位数大于等于8位比特时，
//		   通过位操作输入到一个unsigned char变量中，再将该变量输入到压缩文件中，实现信息压缩
//		   4.其中顺便统计两个文件的大小（其他具体实现函数内有注释描述）
int compress(char* filename) {
	FILE* file;//打开文件
	int w[128];//存储文件中的字符权重 记录字符1-127

	int byte1 = 0;//源文件字节数
	int byte2 = 0;//压缩文件字节数

	//权值数组初始化
	for (int i = 0; i < 128; i++) {
		w[i] = 0;
	}

	file = fopen(filename, "rb");//打开源文件
	if (file == 0) {
		cout << "open failed" << endl;
		return 0;//结束
	}

	//遍历文本，统计词频，记录权重
	unsigned char c;
	while (1) {
		
		c = fgetc(file);
		if (feof(file))
			break;

		
		w[c]++;
		byte1++;
	}

	//求出赫夫曼树和编码
	HuffmanTree HT;//赫夫曼数
	HuffmancCode HC;//赫夫曼编码
	HuffmanCoding(HT, HC, w, 127);//生成赫夫曼编码

	//生成压缩文件名
	char p[50];
	strcpy(p, filename);
	strcat(p, ".qjy");

	//再次遍历，通过赫夫曼编码来压缩出新文件
	FILE* compressfile = fopen(p, "wb");//在源程序处创建压缩文件

	//省略打开失败

	fwrite(&byte1, sizeof(byte1), 1, compressfile);//将原文件的字节数（大小）存储
	byte2 += sizeof(int);
	fwrite(w, sizeof(w), 1, compressfile);//将字符权值压缩进入文件（虽然第0个空间不用，但是也写入）
	byte2 += (128 * sizeof(int));//压缩文件徒增512字节，所以大文件压缩才有用

	rewind(file);//再次遍历源文件，需要将指针回标到开头
	unsigned char temp = '\0';//用来将8位赫夫曼编码转为1字节数据块
	string unit;//暂时存储即将待转换的赫夫曼编码
	while (1) {

		c = fgetc(file);//读取一个字符

		if (feof(file))
			break;

		//cout << "压缩字符int值" << (int)c << endl;
		unit += HC[c];//将该字符的赫夫曼编码加入到字符串型变量，方便操作

		//当unit中存储的赫夫曼编码大于等于8时，不断将前8位拿出来进行操作成1byte
		while ((unit.length()) >= 8) {
			temp = '\0';//初始化清空
			for (int i = 0; i < 8; i++) {
				temp = temp << 1;//逻辑左移1位
				if (unit[i] == '1')
					temp = temp | 1;
			}
			auto p = unit.begin();//指向第一个位置
			unit.erase(p, p + 8);//将前8位清空


			fwrite(&temp, sizeof(temp), 1, compressfile);//将该字节数据块写入压缩文件中

			byte2++;
		}
	}

	//最后仍然剩余不足8位长度的赫夫曼编码，即没有刚好被8整除数目的bit数
	if (unit.length() > 0) {
		temp = '\0';
		for (int i = 0; i < (int)unit.length(); i++) {
			temp = temp << 1;
			if (unit[i] == '1')
				temp = temp | 1;
		}

		for (int i = 0; i < (int)(8 - unit.length()); i++)
			temp = (temp << 1);//将编码转移到高位

		fwrite(&temp, sizeof(temp), 1, compressfile);//将该字节数据块写入压缩文件中
		byte2++;
	}

	cout << "--------------------------------------压缩完成--------------------------------------------" << endl;
	cout << "压缩前文件名称 : " << filename << ' ' << "大小 : " << byte1 << "字节" << endl;
	cout << "压缩后文件名称 : " << p << ' ' << "大小 : " << byte2 << "字节" << endl;
	cout << "压缩率 : " << setiosflags(ios::fixed) << setprecision(2) << (double)byte2 / byte1 * 100 << "%" << endl;

	//关闭文件
	fclose(compressfile);
	fclose(file);

	//压缩结束，释放内存
	free(HT);

	//多层分别释放
	for (int i = 1; i <= 127; i++)
		free(HC[i]);
	free(HC);

	return 1;
}


//函数名称 decompress
//函数功能 对相应压缩文件进行解压，还原文件，实现无损压缩解压
//参数说明 char*类型待解压文件名filename
//函数说明 1.首先获取待解压文件名称，判断其是否为可解压文件
//		   2.首先读取压缩文件开头记录的相关字符权值信息以及原文件大小信息
//		   3.获取以上信息后生成赫夫曼树和赫夫曼编码，根据压缩文件中的编码利用位操作将每一字节的信息一比特一比特去读取，
//		   通过赫夫曼树来找到叶子结点对应的字符，输出到解压文件中
//		   4.顺便统计大小信息
int decompress(char* filename) {
	FILE* file;//打开文件
	int w[128];//存储文件中的字符权重 记录字符1-127

	int byte1 = 0;//压缩文件中记录的原来文件字节数（大小）,理论值
	int byte2 = 0;//解压后的文件字节数，实际值
	int byte3 = 0;//压缩文件的大小

	//权值数组初始化
	for (int i = 0; i < 128; i++) {
		w[i] = 0;
	}

	file = fopen(filename, "rb");//打开源文件
	if (file == NULL) {
		cout << "open failed" << endl;
		return 0;//结束
	}

	fread(&byte1, sizeof(int), 1, file);//读入压缩文件中存储的关于原文件的大小信息
	byte3 += 4;

	for (int i = 0; i < 128; i++) {
		fread(&w[i], sizeof(int), 1, file);
	}

	byte3 += (128 * 4);

	//准备还原赫夫曼数和赫夫曼编码，为解压做准备
	HuffmanTree HT;
	HuffmancCode HC;
	HuffmanCoding(HT, HC, w, 127);

	//判断该文件是否可解压，并且解析出原文件名称
	char p[50];
	char pfinal[50] = "qjy-";
	int str_length = strlen(filename);
	if (strcmp(".qjy", &filename[str_length - 4]) == 0) {
		strncpy(p, filename, str_length - 4);//获取待解压文件名称
		p[str_length - 4] = '\0';
		strcat(pfinal, p);
	}
	else {
		//后缀非.qjy的文件无法解压
		cout << "输入的文件不符合该程序解压格式" << endl;
		return 0;
	}

	FILE* decompressfile = fopen(pfinal, "wb");//创建解压文件
	//省略打开失败
	unsigned char temp = '\0';//读取赫夫曼编码
	int top = 2 * 127 - 1;//赫夫曼树（表）中的根结点
	int length = byte1;//记录原大小

	while (length) {
		temp = fgetc(file);//获取8bit
		byte3++;//压缩文件的大小

		for (int i = 0; i < 8; i++) {
			if ((temp & 128) == 0)
				top = HT[top].lchild;//左孩子
			else
				top = HT[top].rchild;//右孩子

			//到达叶子结点
			if (top <= 127) {

				//cout << "还原字符int值" << (int)top << endl;
				fputc((char)top, decompressfile);//输出叶子结点代表的字符

				length--;
				byte2++;//现文件大小加1

				if (length == 0)
					break;//结束

				top = 127 * 2 - 1;//复位到根结点
			}

			temp = temp << 1;//如果没有到达叶子结点，继续沿着树走下去
		}
	}

	cout << "--------------------------------------解压完成--------------------------------------------" << endl;
	cout << "压缩前文件名称 : " << filename << ' ' << "大小 : " << byte3 << "字节"<< endl;
	cout << "压缩后文件名称 : " << pfinal << ' ' << "大小 : " << byte2 << "字节" << endl;

	//关闭文件
	fclose(file);
	fclose(decompressfile);


	//压缩结束，释放内存
	free(HT);

	//多层分别释放
	for (int i = 1; i <= 127; i++)
		free(HC[i]);
	free(HC);

	return 1;
}

int main()
{
	char s[40];//读取输入的文件名
	int choice = 0;

	while (1) {
		//system("cls");//清屏
		cout << "请输入序号选择功能" << endl;
		cout << "1.压缩文件" << endl;
		cout << "2.解压文件" << endl;
		cout << "3.退出程序" << endl;

		cin >> choice;
		if (choice == 3)//退出程序
			break;
		else if (choice == 1) {
			cout << "请输入待压缩文件名" << endl;
			cin >> s;
			compress(s);
		}
		else if (choice == 2) {
			cout << "请输入待解压文件名" << endl;
			cin >> s;
			decompress(s);
		}
		else 
			cout << "输入错误" << endl;

		cout << endl;
	}
	return 0;
}

//输出信息交互部分省略，可在程序截图中体现