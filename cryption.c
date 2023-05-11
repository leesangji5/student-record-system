#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define numOfStr 77
#define nomalStrDefine "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*-_=+, "

#define keyC " Vq*c1QXDv2djC@IyS+LnKJ3UxP-$0iuZ9Tw!b_,RgzWkM%sF=oYEfr6p4Bl85Ht7O^G#&AhNaem"

// 암호화 복호화
char* cryption(char* strPointer, char* keyAPointer, char* keyBPointer, int strSize) {
	char str[1024] = "";
	char reStr[numOfStr] = "";
	char keyA[numOfStr] = "";
	char keyB[numOfStr] = "";
	// 포인터로 받아 문자열을 다시 만들기
	for (int i = 0; i < strSize; i++) {
		str[i] = *strPointer;
		strPointer++;
	}
	for (int i = 0; i < (numOfStr - 1); i++) {
		keyA[i] = *keyAPointer;
		keyAPointer++;
	}
	for (int i = 0; i < (numOfStr - 1); i++) {
		keyB[i] = *keyBPointer;
		keyBPointer++;
	}
	// 암호화 복호화
	int k = 0;
	int i = 0;
	while (str[k] != NULL) k++;
	while (true) {
		for (int j = 0; j < (numOfStr - 1); j++) {
			if (str[i] == keyB[j]) {
				reStr[i] = keyA[j];
				i++;
				break;
			}
		}
		if (i == k)
			break;
	}
	return reStr;
}
char *rand_str() {
	const char nomalStr[numOfStr] = nomalStrDefine;
	char key[numOfStr] = "";
	int random = 0;
	srand(time(NULL));
	int i = 0;
	while (true) {
		random = rand() % (numOfStr-1);
		if (key[random] == NULL) {
			key[random] = nomalStr[i];
			i++;
		}
		if (i == (numOfStr-1))
			break;
	}
	return key;
}
int main() {
	char* str = rand_str();
	char key[numOfStr] = "";
	for (int i = 0; i < (numOfStr-1); i++) {
		key[i] = *str;
		str++;
	}
	printf("%s\n", nomalStrDefine);
	printf("%s\n", key);

	char a[38] = "13,sangji,19,1234,1234-1234,sldkfnwe,";
	char* encStrPointer = cryption(a, key, nomalStrDefine, sizeof(a));
	char a[1024] = "5Ad,KsrBdztdNvz#vdT5TRNvztR#yXTdG,oK4_od0lo0lo";
	char* encStrPointer = cryption(a, keyC, nomalStrDefine, sizeof(a));
	char encStr[sizeof(a)] = "";
	for (int i = 0; i < (sizeof(a) - 1); i++) {
	for (int i = 0; i < sizeof(a); i++) {
		encStr[i] = *encStrPointer;
		encStrPointer++;
	}
	printf("%s\n", encStr);

	char* decStrPointer = cryption(encStr, nomalStrDefine, key, sizeof(encStr));
	char* decStrPointer = cryption(encStr, nomalStrDefine, keyC, sizeof(encStr));
	char decStr[sizeof(a)] = "";
	for (int i = 0; i < (sizeof(a) - 1); i++) {
	for (int i = 0; i < sizeof(a); i++) {
		decStr[i] = *decStrPointer;
		decStrPointer++;
	}
	printf("%s\n", decStr);
}
