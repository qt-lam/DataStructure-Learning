//本题要求大根堆
#include <iostream>
using namespace std;

//线性表结构
struct SqList {
	int* elem;
	int times;
	int length;
};

typedef SqList HeapType;

void HeapAdjust(HeapType& H, int s, int m) {
	int rc = H.elem[s];

	for (int j = 2 * s; j <= m; j *= 2) {
		if (j<m&&H.elem[j]<H.elem[j + 1])
			j++;
		if (rc > H.elem[j])
			break;

		H.elem[s] = H.elem[j];
		s = j;
	}

	H.elem[s] = rc;
}

int HeapSort(HeapType& H) {

	int cal = 0;

	//先建立小根堆
	for (int i = H.length / 2; i > 0; i--)
		HeapAdjust(H, i, H.length);
	
	//输出次序
	for (int i = H.length; i > 1; i--) {
		cout << H.elem[1] << ' ';
		cal++;

		if (cal == H.times)
			return 0;

		H.elem[1] = H.elem[H.length];

		H.length--;
		HeapAdjust(H, 1, i - 1);
		
	}

	cout << H.elem[1] <<' ' <<endl;
	return 1;
}

//建立线性表
void CreatList(SqList& L) {
	cin >> L.length;
	cin >> L.times;

	L.elem = (int*)malloc(sizeof(int)*(L.length+1));

	for (int i = 1; i <= L.length; i++)
		cin >> L.elem[i];

}



int main()
{
	SqList H;
	CreatList(H);
	HeapSort(H);                     
	return 0;
}