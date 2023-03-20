#include <stdio.h>
#include <stdbool.h>

int main() {
	printf("Student Record System");
	printf("1. add stuendt");
	printf("2. remove stuendt");
	printf("3. search stuendt");
	printf("4. add stuendt");
	printf("5. Exit");
	return 0;
}

int save() {
	printf("save");
}

int add_student() {
	char name[32];
	int age;
	char s;

	bool run = true;
	while (run) {
		printf("add student");
		if (scanf_s("name: %s", &name) == 0) {
			printf("input is wrong");
		}
		else {
			scanf_s("age: %d", &age);

			scanf_s("press y or yes to save this %c", s);
			
			run = false;
		}
	}

}
