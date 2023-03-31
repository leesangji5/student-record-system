#include <stdio.h>
#include <stdbool.h>

struct students
{
	char name[32];
	int age;
};

int save_student() {
	printf("save");
}

int add_student() {
	char name[32];
	int age=0;
	char col[16];
	bool save=true;
	printf("a");

	while (save) {
		printf("student name: ");
		scanf_s("%c", &name);
		printf("student age: ");
		scanf_s("%d", &age);
		printf("is this collect? (y, yes or n, no): ");
		scanf_s("%c", col);
		if (col == ("y" || "yes")) {
			save = false;
		}
	}
	struct students student = { name, age };
	save_student();
}

int main() {
	int sel = 0;
	printf("Student Record System\n");
	printf("1. add student\n");
	printf("2. remove student\n");
	printf("3. search student\n");
	printf("4. edit student\n");
	printf("5. Exit\n");
	printf("select number: ");
	scanf_s("%d", &sel);
	if (sel == 1) {
		add_student();
	}
	return 0;
}
