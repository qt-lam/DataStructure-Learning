#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct {
	ElemType* elem;
	int length;
}SSTable;

//创建顺序表
void CreatTable(SSTable& s) {
	cin >> s.length;

	s.elem = (ElemType*)malloc(sizeof(int)*(s.length));//多申请一个空间 第0个不用

	for (int i = 0; i < s.length; i++) 
		cin >> s.elem[i];
	
}

//折半查找得出的查找结果
int SearchTable(SSTable& s, ElemType key) {
	
	int low = 0;
	int high = s.length-1;

	while (low <= high) {
		int mid = (low + high) / 2;

		if (key == s.elem[mid])
			return mid;
		else if (key < s.elem[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}

	return -1;
}

//针对折半查找的结果，由于一定是有序的，找出最小下标
int Search_plus(SSTable& s, int mid,int key) {
	int k = mid;

	while (k >= 0) {
		
		if (s.elem[k] != key)
			break;
		
		k--;
	}

	k++;
	return k;
}

int main()
{
	SSTable s;
	CreatTable(s);
	
	int number = 0;
	cin >> number;
	for (int i = 0; i < number; i++) {
		int key = 0;
		cin >> key;
		int mid = SearchTable(s, key);
		if (mid == -1) {
			cout << -1 << endl;
			continue;
		}
		else {
			int finalp = Search_plus(s, mid, key);
			cout << finalp << endl;
		}
	}

	return 0;
}