#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 기록 가능한 학생 수
#define buf_lenth 100
// 저장 가능 정보 개수
#define inf_num 3

// 학생 정보 구조체
// 추가 예정: 학번, 전번, 주소
struct student_information
{
	int number;
	char name[64];
	int age;
};

// 학생수
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

// 리스트 마지막에 학생 추가
void save_student(struct student_information stu_inf) {
	char student_inf[1024] = "";
	sprintf_s(student_inf, sizeof(student_inf), "%d %s %d\n", getTotalLine() + 1, stu_inf.name, stu_inf.age);
	printf("saved\n");
	printf("number: %d\n", getTotalLine() + 1);
	printf("name : %s\n", stu_inf.name);
	printf("age : %d\n", stu_inf.age);

	FILE* fp;
	fopen_s(&fp, "student.txt", "a");
	fputs(student_inf, fp);
	fclose(fp);
}

// 삭제된 학생 자리 제거
int resave(char buf[buf_lenth][1024]) {
	FILE* fp;
	int line = getTotalLine();
	fopen_s(&fp, "student.txt", "w");
	for (int i = 0; i < line; i++)
		fputs(buf[i], fp);
	fclose(fp);
}

// 학생 추가
int add_student() {
	struct student_information stu_inf;
	char col[16] = "";
	bool save = false;

	while (true) {
		printf("------------------\n");
		printf("student name(no space): ");
		scanf_s("%s", &stu_inf.name, 32);
		printf("student age: ");
		scanf_s("%d", &stu_inf.age);
		printf("is this collect? (y or n or exit): ");
		scanf_s("%s", &col, 16);
		if (!(strcmp(col, "y")) || !(strcmp(col, "yes"))) {
			save = true;
			break;
		}
		else if (!(strcmp(col, "exit")))
			break;
	}
	if (save) {
		save_student(stu_inf);
		printf("------------------\n\n");
		return 1;
	}
	printf("------------------\n\n");
	return 0;
}

// 학생 찾기
int search_student() {
	FILE* fp;
	char buf[1024];
	char ex_buf[1024] = "";
	char next_page[16] = "";
	char _[16];
	int num = 10; // 한번에 볼 수 있는 학생 수
	int last_page = getTotalLine() / num;
	int now_page = 0;
	fopen_s(&fp, "student.txt", "r");

	if (getTotalLine() % num != 0)
		last_page = (getTotalLine() / num) + 1;

	while (true) {
		printf("------------------\n");

		for (int i = 0; i < num; i++) {
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
			printf("\nnext page %d/%d (y or n):", now_page, last_page);
			scanf_s("%s", &next_page, 16);
		}
		else {
			printf("\nthis page is last page\n");
			printf("press any key");
			scanf_s("%s", &_, 16);
			strcpy_s(next_page, sizeof(next_page), "n");
		}
		if (!strcmp(next_page, "n") || !strcmp(next_page, "no")) {
			printf("------------------\n\n");
			break;
		}
	}

	fclose(fp);
	return 0;
}

// 학생이 없으면 return none
// num번째 학생 정보를 구조체로 반환
struct student_information read_student_information(int num) {
	struct student_information stu_inf;
	FILE* fp;
	char buf[1024];
	fopen_s(&fp, "student.txt", "r");

	for (int i = 0; i < num; i++)
		fgets(buf, sizeof(buf), fp);

	int i = 0;
	int j = 0;
	int dir[inf_num+1];
	while (buf[i]) {
		if ((int)buf[i] == (int)*" ") {
			dir[j] = i;
			j++;
		}
		i++;
	}
	char number_[64];
	char age_[64];

	for (int i = 0; i < dir[0]; i++)
		number_[i] = buf[i];

	stu_inf.number = atoi(number_);

	for (int i = dir[0] + 1; i < dir[1]; i++)
		stu_inf.name[i - dir[0] - 1] = buf[i];
	stu_inf.name[dir[1] - dir[0] - 1] = NULL;

	int last_null = 0;
	while (buf[last_null] != NULL)
		last_null++;

	for (int i = dir[1] + 1; i < last_null - 1; i++)
		age_[i - dir[1] - 1] = buf[i];
	stu_inf.age = atoi(age_);

	fclose(fp);
	return stu_inf;
}

// 학생 삭제시 번호 재배열
int rearrangement() {
	FILE* fp;
	struct student_information stu_inf;
	int line = getTotalLine();
	char buf[buf_lenth][1024];

	for (int i = 0; i < line; i++) {
		stu_inf = read_student_information(i+1);
		sprintf_s(buf[i], sizeof(buf[i]), "%d %s %d\n", i+1, stu_inf.name, stu_inf.age);
	}
	resave(buf);
}

// 번호로 학생 정보 찾기
int find_student() {
	int num;
	printf("------------------");
	while (true) {
		printf("\nstudent number: ");
		scanf_s("%d", &num);
		if (0 < num && num < getTotalLine() + 1)
			break;
		printf("please enter again\n");
	}
	struct student_information stu_inf = read_student_information(num);
	printf("%d %s %d\n", stu_inf.number, stu_inf.name, stu_inf.age);
	printf("------------------\n\n");
	return 0;
}

// 학생 정보 수정
int edit_student() {
	int number;
	printf("------------------");
	while (true) {
		printf("\nstudent number: ");
		scanf_s("%d", &number);
		if (0 < number && number < getTotalLine() + 1)
			break;
		printf("please enter again\n");
	}
	struct student_information stu_inf = read_student_information(number);
	FILE* fp;
	char buf[buf_lenth][1024];
	char what[64]="";
	char name[64]="";
	char _[1024]="";
	int num=0;
	int age = 0;

	fopen_s(&fp, "student.txt", "r");
	for (int i = 0; i < getTotalLine(); i++)
		fgets(buf[i], sizeof(buf[i]), fp);
	fclose(fp);

	printf("\nstudent information\n");

	printf("number: %d\n", stu_inf.number);
	printf("name : %s\n", stu_inf.name);
	printf("age : %d\n", stu_inf.age);

	while (true) {
		printf("\nedit inf: ");
		scanf_s("%s", &what, 64);

		if (!(strcmp(what, "name"))) {
			printf("name: ");
			scanf_s("%s", &name, 64);
			strcpy_s(stu_inf.name, 64, name);
			break;
		}
		else if (!(strcmp(what, "age"))) {
			printf("age: ");
			scanf_s("%d", &age);
			stu_inf.age = age;
			break;
		}
		else {
			printf("please enter again");
		}
	}
	sprintf_s(buf[stu_inf.number - 1], sizeof(buf[stu_inf.number]), "%d %s %d\n", stu_inf.number, stu_inf.name, stu_inf.age);
	resave(buf, stu_inf);
	printf("saved");
	printf("------------------\n\n");
	return 0;
}

// 학생 제거
int remove_student() {
	FILE* fp;
	char buf[buf_lenth][1024];
	int num=1;

	fopen_s(&fp, "student.txt", "r");
	for (int i = 0; i < getTotalLine(); i++)
		fgets(buf[i], sizeof(buf[i]), fp);
	fclose(fp);

	printf("------------------");
	while (true) {
		printf("\nremove student number: ");
		scanf_s("%d", &num);
		if (0 < num && num < getTotalLine()+1)
			break;
		printf("please enter again\n");
	}

	struct student_information stu_inf = read_student_information(num);
	char answer[64];
	while (true) {
		printf("\nremove student information\n");
		printf("number: %d\n", stu_inf.number);
		printf("name: %s\n", stu_inf.name);
		printf("age: %d\n", stu_inf.age);
		printf("remove this student (y or n):");
		scanf_s("%s", &answer, 64);

		if (!strcmp(answer, "n") || !strcmp(answer, "no") || 
			!strcmp(answer, "y") || !strcmp(answer, "yes"))
			break;
		printf("please enter again\n");
	}
	if (!strcmp(answer, "y") || !strcmp(answer, "yes")) {
		for (int i = num - 1; i < getTotalLine() - 1; i++)
			sprintf_s(buf[i], 1024, buf[i + 1]);
		sprintf_s(buf[getTotalLine() - 1], 1024, "\0");

		resave(buf);
		printf("------------------\n\n");
		return 1;
	}
	printf("------------------\n\n");
	return 0;
}

// 파일 있는지 확인 후 없으면 생성
int file_check() {
	FILE* fp;

	fopen_s(&fp, "student.txt", "a");
	fclose(fp);
	return 0;
}

int main() {
	file_check();
	rearrangement();
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
		if (select == 1)
			add_student();
		else if (select == 2)
			remove_student();
		else if (select == 3)
			search_student();
		else if (select == 4)
			find_student();
		else if (select == 5)
			edit_student();
		else if (select == 6)
			break;
		else 
			printf("please enter again");
	}
	return 0;
}
