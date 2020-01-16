#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct {
	ElemType* elem;
	int length;
}SSTable;

//����˳���
void CreatTable(SSTable& s) {
	cin >> s.length;

	s.elem = (ElemType*)malloc(sizeof(int)*(s.length));//������һ���ռ� ��0������

	for (int i = 0; i < s.length; i++) 
		cin >> s.elem[i];
	
}

//�۰���ҵó��Ĳ��ҽ��
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

//����۰���ҵĽ��������һ��������ģ��ҳ���С�±�
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