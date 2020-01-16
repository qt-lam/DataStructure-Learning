#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

struct memory_like {
	int memory;
	char name[100];
};

memory_like s[100];

void cal(int position[100], int findtime[100],int M,int number) {
	char name[100];
	cin >> name;

	int length = strlen(name);

	int temp = 0;

	for (int i = 0; name[i] != '\0'; i++) {
		
		if (name[i] >= 'a'&&name[i] < 'z') {
			length--;
			temp +=  ((name[i] - 'a' + 1)*(long long int)pow(37, length)) % M;
		}
		else if (name[i] >= 'A'&&name[i] <= 'Z') {
			length--;
			temp += ((name[i] - 'A' + 1)*(long long int)pow(37, length)) % M;
		}

	}

	temp = temp % M;

	while (1) {
		if (s[temp].memory == 0) {
			s[temp].memory = 1;
			position[number] = temp;
			findtime[number]++;
			break;
		}

		temp = (temp + 1) % M;
		findtime[number]++;
	}
	
}

int main() {
	int N, M, P;
	cin >> N >> M >> P;

	//memory_like s[100];
	for (int i = 0; i < 100; i++) {
		s[i].memory = 0;
		strcpy(s[i].name, "");
	}

	int position[100];
	int findtime[100];
	for (int i = 0; i < 100; i++) {
		position[i] = 0;
		findtime[i] = 0;
	}
}