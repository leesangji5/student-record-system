#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct student_imformation
{
	char name[64];
	int age;
};

int getTotalLine() {
	FILE* fp = NULL;
	errno_t err;
	int line = 0;
	char c;

	fopen_s(&fp, "student.txt", "r");
	while ((c = fgetc(fp)) != EOF)
		if (c == '\n') line++;
	fclose(fp);
	return line;
}

void save_student(struct student_imformation stu_imf) {
	char student_imf[1024]="";
	sprintf_s(student_imf, sizeof(student_imf), "%d %s %d \n", getTotalLine()+1, stu_imf.name, stu_imf.age);
	printf("saved\n");
	printf("name : %s\n", stu_imf.name);
	printf("age : %d\n", stu_imf.age);

	FILE* fp;
	fopen_s(&fp, "student.txt", "a");
	fputs(student_imf, fp);
	fclose(fp);
}

int add_student() {
	struct student_imformation stu_imf;
	char col[16]="";
	bool save = false;

	while (true) {
		printf("------------------\n");
		printf("student name(no space): ");
		scanf_s("%s", &stu_imf.name, 32);
		printf("student age: ");
		scanf_s("%d", &stu_imf.age);
		printf("is this collect? (y or n or exit): ");
		scanf_s("%s", &col, 16);
		if (!(strcmp(col, "y")) || !(strcmp(col, "yes"))) {
			save = true;
			break;
		}
		else if (!(strcmp(col, "exit"))) {
			break;
		}
	}
	if (save) {
		save_student(stu_imf);
		printf("------------------\n\n");
		return 1;
	}
	printf("------------------\n\n");
	return 0;
}

int search_student() {
	FILE* fp;
	char buf[1024];
	char ex_buf[1024]="";
	char next_page[16]="";
	char _[16];
	int last_page = getTotalLine() / 10;
	int now_page = 0;
	fopen_s(&fp, "student.txt", "r");

	if (getTotalLine() % 10 != 0)
		last_page = (getTotalLine() / 10) + 1;

	while (true) {
		printf("------------------\n");

		for (int i = 0; i < 10; i++) {
			fgets(buf, sizeof(buf), fp);
			if (!strcmp(buf, ex_buf)) {
				strcpy_s(next_page, sizeof(next_page), "n");
				break;
			}
			printf("%s", buf);
			strcpy_s(ex_buf, sizeof(ex_buf), buf);
		}
		now_page++;

		if (last_page != now_page) {
			printf("------------------\n");
			printf("next page %d/%d (y or n):", now_page, last_page);
			scanf_s("%s", &next_page, 16);
			printf("\n");
		}
		else {
			printf("------------------\n");
			printf("this page is last page\n");
			printf("press any key");
			scanf_s("%s", &_, 16);
			strcpy_s(next_page, sizeof(next_page), "n");
		}

		if (!strcmp(next_page, "n") || !strcmp(next_page, "no")) {
			printf("\n\n");
			break;
		}
	}

	fclose(fp);

	return 0;
}

// read_line 함수 생성
struct student_imformation read_line(){
	struct student_imformation stu_imf;
	return stu_imf;
}

int find_student() {
	FILE* fp;
	char buf[1024];
	int num;
	fopen_s(&fp, "student.txt", "r");

	printf("student number: ");
	scanf_s("%d", &num);

	for (int i = 0; i < num; i++) {
		fgets(buf, sizeof(buf), fp);
	}
	
	int i = 0;
	int j = 0;
	int dir[4];
	while (buf[i]) {
		printf("%c", buf[i]);
		if ((int)buf[i] == (int)*" ") {
			dir[j] = i;
			j++;
		}
		i++;
	}
	int number;
	char name[64];
	int age;
	char number_[64];
	char age_[64];

	for (int i = 0; i < dir[0]; i++)
		number_[i] = buf[i];

	number = atoi(number_);
	printf("number: %d\n", number);

	for (int i = dir[0]+1; i < dir[1]; i++)
		name[i-dir[0]-1] = buf[i];
	name[dir[1]- dir[0] - 1] = NULL;
	printf("name: %s\n", name);

	int last_null = 0;
	while (buf[last_null] != NULL)
		last_null++;

	for (int i = dir[1] + 1; i < last_null-2; i++)
		age_[i-dir[1] - 1] = buf[i];
	age = atoi(age_);
	printf("age: %d\n", age);
	return 0;
}

int edit_student() {
	return 0;
}

int remove_student() {
	return 0;
}

// write file
// 파일 확인 후 생성 

int write_file(){
	return 0;
}

int main() {
	while (true) {
		int select = 0;
		printf("------------------\n");
		printf("Student Record System\n");
		printf("1. add student\n");
		printf("2. remove student\n");
		printf("3. search student\n");
		printf("4. find student\n");
		printf("5. edit student\n");
		printf("6. Exit\n");
		printf("select number: ");
		scanf_s("%d", &select);
		printf("------------------\n\n");
		if (select == 1) {
			add_student();
		}
		else if (select == 2) {
			remove_student();
		}
		else if (select == 3) {
			search_student();
		}
		else if (select == 4) {
			find_student();
		}
		else if (select == 5) {
			search_student();
		}
		else if (select == 6) {
			break;
		}
		else {
			printf("please enter again");
		}
	}
	return 0;
}
