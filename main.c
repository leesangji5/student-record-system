#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void save_student(char name[32], int age) {
	char student_imf[64]="";
	sprintf_s(student_imf, sizeof(student_imf), "%s %d \n", name, age);
	printf("saved\n");
	printf("name : %s\n", name);
	printf("age : %d", age);

	FILE* sn;
	fopen_s(&sn, "student.txt", "a");
	fputs(student_imf, sn);
	fclose(sn);
}

int add_student() {
	char name[32];
	int age = 0;
	char col[16];
	bool save_imf = false;

	while (true) {
		printf("student name: ");
		scanf_s("%s", &name, 32);
		printf("student age: ");
		scanf_s("%d", &age);
		printf("is this collect? (y, yes or n, no or exit): ");
		scanf_s("%s", &col, 16);
		if (!(strcmp(col, "y")) || !(strcmp(col, "yes"))) {
			save_imf = true;
			break;
		}
		else if (!(strcmp(col, "exit"))) {
			break;
		}
	}
	if (save_imf) {
		save_student(name, age);
		return 1;
	}
	return 0;
}

int remove_student() {
	return 0;
}

int main() {
	int select = 0;
	printf("Student Record System\n");
	printf("1. add student\n");
	printf("2. remove student\n");
	printf("3. search student\n");
	printf("4. edit student\n");
	printf("5. Exit\n");
	printf("select number: ");
	scanf_s("%d", &select);
	if (select == 1) {
		add_student();
	}
	if (select == 2) {
		remove_student();
	}
	return 0;
}
