#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 기록 가능한 학생 수
#define buf_lenth 100
// 저장 가능 정보 개수
#define inf_num 7

// 학생 정보 구조체s
struct student_information
{
	int number;
	char name[64];
	int age;
	int grade;
	char phone[64];
	char adress[64];
	char memo[1024];
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
	sprintf_s(student_inf, sizeof(student_inf), "%d,%s,%d,%d,%s,%s, \n", getTotalLine() + 1, stu_inf.name, stu_inf.age, stu_inf.grade, stu_inf.phone, stu_inf.adress);
	printf("saved\n");
	printf("number : %d\n", getTotalLine() + 1);
	printf("name : %s\n", stu_inf.name);
	printf("age : %d\n", stu_inf.age);
	printf("grade : %d\n", stu_inf.grade);
	printf("phone : %s\n", stu_inf.phone);
	printf("adress : %s\n", stu_inf.adress);

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

	while (true) {
		printf("------------------\n");
		printf("student name(no space): ");
		scanf_s(" %[^\n]", &stu_inf.name, 64);
		printf("student age: ");
		scanf_s("%d", &stu_inf.age);
		printf("student grade: ");
		scanf_s("%d", &stu_inf.grade);
		printf("student phone: ");
		scanf_s(" %[^\n]", &stu_inf.phone, 64);
		printf("student adress: ");
		scanf_s(" %[^\n]", &stu_inf.adress, 64);
		printf("is this collect? (y or n or exit): ");

		fflush(stdin);
		scanf_s(" %s", &col, 16);
		printf("------------------\n\n");
		if (!(strcmp(col, "y")) || !(strcmp(col, "yes"))) {
			save_student(stu_inf);
			return 1;
		}
		else if (!(strcmp(col, "exit")))
			return 0;
	}
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

// num번째 학생 정보를 구조체로 반환
struct student_information read_student_information(int num) {
	struct student_information stu_inf;
	FILE* fp;
	char buf[1024];
	fopen_s(&fp, "student.txt", "r");

	for (int i = 0; i < num; i++)
		fgets(buf, sizeof(buf), fp);

	// 몇번째를 기준으로 나누는지
	int i = 0;
	int j = 0;
	int dir[inf_num - 1];
	while (buf[i]) {
		if ((int)buf[i] == (int)*",") {
			dir[j] = i;
			j++;
		}
		i++;
	}

	char number_[64];
	char age_[64];
	char grade_[64];
	char phone_[64];
	char adress_[64];
	char memo_[1024];

	// 이 줄의 끝이 몇번째인지
	int last_null = 0;
	while (buf[last_null] != NULL)
		last_null++;


	int d = 0;
	for (int i = 0; i < dir[d]; i++)
		number_[i] = buf[i];
	number_[dir[0]] = NULL;
	stu_inf.number = atoi(number_);
	d++;

	for (int i = 0; i < dir[d] - dir[d - 1] - 1; i++)
		stu_inf.name[i] = buf[i + dir[d - 1] + 1];
	stu_inf.name[dir[d] - dir[d - 1] - 1] = NULL;
	d++;

	for (int i = 0; i < dir[d] - dir[d - 1] - 1; i++)
		age_[i] = buf[i + dir[d - 1] + 1];
	age_[dir[d] - dir[d - 1] - 1] = NULL;
	stu_inf.age = atoi(age_);
	d++;

	for (int i = 0; i < dir[d] - dir[d - 1] - 1; i++)
		grade_[i] = buf[i + dir[d - 1] + 1];
	grade_[dir[d] - dir[d - 1] - 1] = NULL;
	stu_inf.grade = atoi(grade_);
	d++;

	for (int i = 0; i < dir[d] - dir[d - 1] - 1; i++)
		stu_inf.phone[i] = buf[i + dir[d - 1] + 1];
	stu_inf.phone[dir[d] - dir[d - 1] - 1] = NULL;
	d++;

	for (int i = 0; i < last_null - dir[d - 1] - 2; i++)
		stu_inf.adress[i] = buf[i + dir[d - 1] + 1];
	stu_inf.adress[dir[d] - dir[d - 1] - 1] = NULL;
	d++;

	for (int i = 0; i < last_null - dir[d - 1] - 2; i++)
		stu_inf.memo[i] = buf[i + dir[d - 1] + 1];
	stu_inf.memo[last_null - dir[d - 1] - 2] = NULL;
	d++;

	fclose(fp);
	return stu_inf;
}

// 학생 삭제시 번호 재배열
int rearrangement() {
	struct student_information stu_inf;
	int line = getTotalLine();
	char buf[buf_lenth][1024];

	for (int i = 0; i < line; i++) {
		stu_inf = read_student_information(i + 1);
		sprintf_s(buf[i], sizeof(buf[i]), "%d,%s,%d,%d,%s,%s,%s\n", i + 1, stu_inf.name, stu_inf.age, stu_inf.grade, stu_inf.phone, stu_inf.adress, stu_inf.memo);
	}
	resave(buf);
}

// 번호로 학생 정보 찾기
int find_student_use_number() {
	int num;

	while (true) {
		printf("\nstudent number: ");
		scanf_s("%d", &num);
		if (0 < num && num < getTotalLine() + 1)
			break;
		printf("please enter again\n");
	}
	struct student_information stu_inf = read_student_information(num);
	printf("%d, %s, %d, %d, %s, %s\n\n", stu_inf.number, stu_inf.name, stu_inf.age, stu_inf.grade, stu_inf.phone, stu_inf.adress);
	return 0;
}

int find_studnet_use_name() {
	char name;
}

// 학생 검색
int find_student() {
	char how[16] = "";
	printf("------------------\n");
	while (true) {
		printf("what use to find student\n");
		printf("num, name, age, grade, phone, exit\n");
		printf("select : ");
		scanf_s("%s", how, 16);

		if (!strcmp(how, "num") || !strcmp(how, "number")) {
			find_student_use_number();
		}
		else if (!strcmp(how, "exit"))
			break;
		else
			printf("please enter again\n");
	}

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
	char what[64] = "";
	char name[64] = "";
	char phone[64] = "";
	char adress[64] = "";
	char memo[1024] = "";
	char _[1024] = "";
	int num = 0;
	int age = 0;
	int grade = 0;

	fopen_s(&fp, "student.txt", "r");
	for (int i = 0; i < getTotalLine(); i++)
		fgets(buf[i], sizeof(buf[i]), fp);
	fclose(fp);

	printf("\nstudent information\n");

	printf("number: %d\n", stu_inf.number);
	printf("name : %s\n", stu_inf.name);
	printf("age : %d\n", stu_inf.age);
	printf("grade: %d\n", stu_inf.grade);
	printf("phone: %s\n", stu_inf.phone);
	printf("adress: %s\n", stu_inf.adress);
	printf("memo: %s\n", stu_inf.memo);

	while (true) {
		printf("\nedit inf (exit): ");
		scanf_s("%s", &what, 64);
		fflush(stdin);

		if (!(strcmp(what, "name"))) {
			printf("name: ");
			scanf_s(" %[^\n]", &name, 64);
			strcpy_s(stu_inf.name, 64, name);
		}
		else if (!(strcmp(what, "age"))) {
			printf("age: ");
			scanf_s("%d", &age);
			stu_inf.age = age;
		}
		else if (!(strcmp(what, "grade"))) {
			printf("grade: ");
			scanf_s("%d", &grade);
			stu_inf.grade = grade;
		}
		else if (!(strcmp(what, "phone"))) {
			printf("phone: ");
			scanf_s("%s", &phone, 64);
			strcpy_s(stu_inf.phone, 64, phone);
		}
		else if (!(strcmp(what, "adress"))) {
			printf("adress: ");
			scanf_s("%s", &adress, 64);
			strcpy_s(stu_inf.adress, 64, adress);
		}
		else if (!(strcmp(what, "memo"))) {
			printf("memo: ");
			scanf_s(" %[^\n]", &memo, 64);
			strcpy_s(stu_inf.memo, 1024, memo);
		}
		else if (!(strcmp(what, "exit")))
			break;
		else
			printf("please enter again");
	}
	sprintf_s(buf[stu_inf.number - 1], sizeof(buf[stu_inf.number]), "%d,%s,%d,%d,%s,%s,%s\n", stu_inf.number, stu_inf.name, stu_inf.age, stu_inf.grade, stu_inf.phone, stu_inf.adress, stu_inf.memo);
	resave(buf, stu_inf);
	printf("saved\n");
	printf("------------------\n\n");
	return 0;
}

// 학생 제거
int remove_student() {
	FILE* fp;
	char buf[buf_lenth][1024];
	int num = 1;

	fopen_s(&fp, "student.txt", "r");
	for (int i = 0; i < getTotalLine(); i++)
		fgets(buf[i], sizeof(buf[i]), fp);
	fclose(fp);

	printf("------------------");
	while (true) {
		printf("\nremove student number: ");
		scanf_s("%d", &num);
		if (0 < num && num < getTotalLine() + 1)
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
		printf("grade: %d\n", stu_inf.grade);
		printf("phone: %s\n", stu_inf.phone);
		printf("adress: %s\n", stu_inf.adress);
		printf("memo: %s\n", stu_inf.memo);
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
		rearrangement();
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
	int num_of_student = getTotalLine();
	int select = 0;

	while (true) {
		select = 0;
		printf("------------------\n");
		printf("Student Record System\n");
		printf("1. add student\n");
		printf("2. remove student\n");
		printf("3. search student\n");
		printf("4. find student\n");
		printf("5. edit student(memo)\n");
		printf("6. Exit\n");
		if (num_of_student == 0)
			printf("you should add student\n");
		fflush(stdin);
		printf("select number: ");
		scanf_s("%d", &select);
		printf("------------------\n\n");

		if (select == 1)
			add_student();
		else if (num_of_student == 0 && select != 1)
			printf("please enter again\nyou should add student\n\n");
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
