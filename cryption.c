#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// 추가 예정
// 키 수정

// 기록 가능한 학생 수
#define buf_lenth 100
// 저장 가능 정보 개수
#define inf_num 7

// 암호화에 필요한 것
#define nomalStrDefine "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*-_=+, "
#define numOfStr sizeof(nomalStrDefine)
char keyC[77] = " Vq*c1QXDv2djC@IyS+LnKJ3UxP-$0iuZ9Tw!b_,RgzWkM%sF=oYEfr6p4Bl85Ht7O^G#&AhNaem";

// 학생 정보 구조체
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

// 랜덤 키 생성
char* rand_key() {
	const char nomalStr[numOfStr] = nomalStrDefine;
	char key[numOfStr] = "";
	int random = 0;
	srand(time(NULL));

	int i = 0;
	while (true) {
		random = rand() % (numOfStr - 1);
		if (key[random] == NULL) {
			key[random] = nomalStr[i];
			i++;
		}
		if (i == (numOfStr - 1))
			break;
	}
	return key;
}

// 학생수 n명
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
	FILE* fp;
	char student_inf[1024] = "";

	sprintf_s(student_inf, sizeof(student_inf), "%d,%s,%d,%d,%s,%s, ", getTotalLine() + 1, stu_inf.name, stu_inf.age, stu_inf.grade, stu_inf.phone, stu_inf.adress);
	printf("\nsaved\n");
	printf("number : %d\n", getTotalLine() + 1);
	printf("name : %s\n", stu_inf.name);
	printf("age : %d\n", stu_inf.age);
	printf("grade : %d\n", stu_inf.grade);
	printf("phone : %s\n", stu_inf.phone);
	printf("adress : %s\n", stu_inf.adress);
	printf("------------------\n\n");

	char* studentInfPointer = cryption(student_inf, keyC, nomalStrDefine, 1024);
	for (int i = 0; i < sizeof(student_inf); i++) {
		student_inf[i] = *studentInfPointer;
		studentInfPointer++;
	}

	fopen_s(&fp, "student.txt", "a");
	fputs(student_inf, fp);
	fputs("\n", fp);
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

		fflush(stdin);
		printf("is this collect? (y or n or exit): ");
		scanf_s(" %s", &col, 16);

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
	fopen_s(&fp, "student.txt", "r");

	char buf[1024];
	char ex_buf[1024] = "";
	char next_page[16] = "";
	char _[16];
	int num = 10; // 페이지당 볼 수 있는 학생 수
	int last_page = getTotalLine() / num;
	int now_page = 0;

	if (getTotalLine() % num != 0)
		last_page = (getTotalLine() / num) + 1;

	while (true) {
		printf("------------------\n");

		// 1페이지 출력
		for (int i = 0; i < num; i++) {
			fgets(buf, sizeof(buf), fp);
			if (!strcmp(buf, ex_buf)) {
				strcpy_s(next_page, sizeof(next_page), "n");
				break;
			}
			for (int i = 0; i < sizeof(buf); i++) {
				if (buf[i] == '\n') {
					buf[i] = '\0';
					break;
				}
			}
			char* bufPointer = cryption(buf, nomalStrDefine, keyC, sizeof(buf));
			for (int i = 0; i < sizeof(buf); i++) {
				buf[i] = *bufPointer;
				bufPointer++;
			}
			printf("%s\n", buf);
			strcpy_s(ex_buf, sizeof(ex_buf), buf);
		}
		now_page++;

		// 계속 볼것인지
		while (true) {
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
			if (!strcmp(next_page, "y") || !strcmp(next_page, "yes")) {
				break;
			}
			else if (!strcmp(next_page, "n") || !strcmp(next_page, "no")) {
				printf("------------------\n\n");
				fclose(fp);
				return 0;
			}
			else printf("please enter again\n");
		}
	}

	fclose(fp);
	return 1;
}

// num번째 학생 정보를 구조체로 반환
struct student_information read_student_information(int num) {
	FILE* fp;
	struct student_information stu_inf;
	char buf[1024];

	fopen_s(&fp, "student.txt", "r");
	for (int i = 0; i < num; i++)
		fgets(buf, sizeof(buf), fp);

	for (int i = 0; i < sizeof(buf); i++) {
		if (buf[i] == '\n') {
			buf[i] = '\0';
			break;
		}
	}

	char* bufPointer = cryption(buf, nomalStrDefine, keyC, sizeof(buf));
	for (int i = 0; i < sizeof(buf); i++) {
		buf[i] = *bufPointer;
		bufPointer++;
	}

	// 정보를 나누는 번호
	// ,단위로 나뉜는 위치
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

	for (int i = 0; i < dir[d] - dir[d - 1] - 1; i++)
		stu_inf.adress[i] = buf[i + dir[d - 1] + 1];
	stu_inf.adress[dir[d] - dir[d - 1] - 1] = NULL;
	d++;

	for (int i = 0; i < last_null - dir[d - 1] - 1; i++)
		stu_inf.memo[i] = buf[i + dir[d - 1] + 1];
	stu_inf.memo[last_null - dir[d - 1] - 1] = NULL;
	d++;

	fclose(fp);
	return stu_inf;
}

// 재저장
void resave(char buf[buf_lenth][1024], int num) {
	FILE* fp;
	int line = getTotalLine() - num;
	fopen_s(&fp, "student.txt", "w");
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < sizeof(buf[i]); j++) {
			if (buf[i][j] == '\n') {
				buf[i][j] = '\0';
				break;
			}
		}
		char* bufPointer = cryption(buf[i], keyC, nomalStrDefine, sizeof(buf[i]));
		for (int j = 0; j < sizeof(buf[i]); j++) {
			buf[i][j] = *bufPointer;
			bufPointer++;
		}
		fputs(buf[i], fp);
		fputs("\n", fp);
	}
	fclose(fp);
}

// 학생 삭제시 번호 재배열
void rearrangement(int num) {
	struct student_information stu_inf;
	int line = getTotalLine();
	char buf[buf_lenth][1024];

	for (int i = 0; i < line-num; i++) {
		stu_inf = read_student_information(i + 1);
		sprintf_s(buf[i], sizeof(buf[i]), "%d,%s,%d,%d,%s,%s,%s", i + 1, stu_inf.name, stu_inf.age, stu_inf.grade, stu_inf.phone, stu_inf.adress, stu_inf.memo);
	}
	resave(buf, num);
}

// 학생 구조체를 받아 출력
int print_student(struct student_information stu_inf) {
	printf("\nnumber: %d\n", stu_inf.number);
	printf("name : %s\n", stu_inf.name);
	printf("age : %d\n", stu_inf.age);
	printf("grade: %d\n", stu_inf.grade);
	printf("phone: %s\n", stu_inf.phone);
	printf("adress: %s\n", stu_inf.adress);
	printf("memo: %s\n", stu_inf.memo);
	return 0;
}

// 번호로 학생 정보 검색
void find_student_use_number() {
	struct student_information stu_inf;
	int num;

	while (true) {
		printf("student number: ");
		scanf_s("%d", &num);
		if (0 < num && num < getTotalLine() + 1)
			break;
		printf("please enter again\n");
	}
	stu_inf = read_student_information(num);
	print_student(stu_inf);
}

// 이름으로 학생 정보 검색
void find_student_use_name() {
	struct student_information stu_inf;
	char name[64] = "";
	char col[16] = "";

	while (true) {
		printf("\nstudent name: ");
		scanf_s(" %[^\n]", &name, 64);
		printf("is this collect (y or n): ");
		scanf_s("%s", &col, 16);
		if (!strcmp(col, "y") || !strcmp(col, "yes"))
			break;
	}
	for (int i = 1; i < getTotalLine() + 1; i++) {
		stu_inf = read_student_information(i);
		if (!strcmp(stu_inf.name, name)) {
			print_student(stu_inf);
		}
	}
}

// 나이로 학생 정보 검색
void find_student_use_age() {
	struct student_information stu_inf;
	char age[64] = "";
	char col[16] = "";

	while (true) {
		printf("\nstudent age: ");
		scanf_s(" %[^\n]", &age, 64);
		printf("is this collect (y or n): ");
		scanf_s("%s", &col, 16);
		if (!strcmp(col, "y") || !strcmp(col, "yes"))
			break;
	}
	for (int i = 1; i < getTotalLine() + 1; i++) {
		stu_inf = read_student_information(i);
		if (stu_inf.age == atoi(age)) {
			print_student(stu_inf);
		}
	}
}

// 학번으로 학생 정보 검색
void find_student_use_grade() {
	struct student_information stu_inf;
	char grade[64] = "";
	char col[16] = "";

	while (true) {
		printf("\nstudent grade: ");
		scanf_s(" %[^\n]", &grade, 64);
		printf("is this collect (y or n): ");
		scanf_s("%s", &col, 16);
		if (!strcmp(col, "y") || !strcmp(col, "yes"))
			break;
	}
	for (int i = 1; i < getTotalLine() + 1; i++) {
		stu_inf = read_student_information(i);
		if (stu_inf.grade == atoi(grade)) {
			print_student(stu_inf);
		}
	}
}

// 폰번호로 학생 정보 검색
void find_student_use_phone() {
	struct student_information stu_inf;
	char phone[64] = "";
	char col[16] = "";

	while (true) {
		printf("\nstudent phone: ");
		scanf_s(" %[^\n]", &phone, 64);
		printf("is this collect (y or n): ");
		scanf_s("%s", &col, 16);
		if (!strcmp(col, "y") || !strcmp(col, "yes"))
			break;
	}
	for (int i = 1; i < getTotalLine() + 1; i++) {
		stu_inf = read_student_information(i);
		if (!strcmp(stu_inf.phone, phone)) {
			print_student(stu_inf);
		}
	}
}

// 메모의 특정 단어로 학생 검색
void find_student_use_memo() {
	struct student_information stu_inf;
	char str[64] = "";
	char col[16] = "";
	char txtStr[64] = "";

	while (true) {
		printf("\nEnter a specific word in the memo: ");
		scanf_s(" %[^\n]", &str, 64);
		printf("is this collect (y or n): ");
		scanf_s("%s", &col, 16);
		if (!strcmp(col, "y") || !strcmp(col, "yes"))
			break;
	}
	for (int i = 1; i < getTotalLine() + 1; i++) {
		stu_inf = read_student_information(i);
		int i = 0;
		int j = 0;
		strcpy_s(txtStr, 64, "");
		while (stu_inf.memo[i]) {
			if ((int)stu_inf.memo[i] == (int)*" ") {
				txtStr[j] = '\0';
				if (!strcmp(txtStr, str)) {
					strcpy_s(txtStr, 64, "");
					print_student(stu_inf);
					break;
				}
				strcpy_s(txtStr, 64, "");
				i++; j = 0;
			}
			else {
				txtStr[j] = stu_inf.memo[i];
				i++; j++;
			}
		}
		txtStr[j] = '\0';
		if (!strcmp(txtStr, str)) {
			print_student(stu_inf);
		}
	}
}

// 학생 검색
void find_student() {
	char how[16] = "";
	printf("------------------");
	while (true) {
		printf("\nwhat use to find student\n");
		printf("num, name, age, grade, phone, memo, exit\n");
		printf("select: ");
		scanf_s("%s", how, 16);

		if (!strcmp(how, "num") || !strcmp(how, "number"))
			find_student_use_number();
		else if (!strcmp(how, "name"))
			find_student_use_name();
		else if (!strcmp(how, "age"))
			find_student_use_age();
		else if (!strcmp(how, "grade"))
			find_student_use_grade();
		else if (!strcmp(how, "phone"))
			find_student_use_phone();
		else if (!strcmp(how, "memo"))
			find_student_use_memo();
		else if (!strcmp(how, "exit"))
			break;
		else
			printf("please enter again\n");
	}

	printf("------------------\n\n");
}

// 학생 정보 수정
void edit_student() {
	FILE* fp;
	struct student_information stu_inf;
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
	int number;

	printf("------------------");
	while (true) {
		printf("\nstudent number: ");
		scanf_s("%d", &number);
		if (0 < number && number < getTotalLine() + 1)
			break;
		printf("please enter again\n");
	}
	stu_inf = read_student_information(number);

	printf("\nstudent information");
	print_student(stu_inf);

	// 무엇을 수정할 것인지
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

	fopen_s(&fp, "student.txt", "r");
	for (int i = 0; i < getTotalLine(); i++) {
		fgets(buf[i], sizeof(buf[i]), fp);

		for (int j = 0; j < sizeof(buf[i]); j++) {
			if (buf[i][j] == '\n') {
				buf[i][j] = '\0';
				break;
			}
		}

		char* bufPointer = cryption(buf[i], nomalStrDefine, keyC, sizeof(buf[i]));
		for (int j = 0; j < sizeof(buf[i]); j++) {
			buf[i][j] = *bufPointer;
			bufPointer++;
		}
	}
	fclose(fp);

	sprintf_s(buf[stu_inf.number - 1], sizeof(buf[stu_inf.number]), "%d,%s,%d,%d,%s,%s,%s\n", stu_inf.number, stu_inf.name, stu_inf.age, stu_inf.grade, stu_inf.phone, stu_inf.adress, stu_inf.memo);
	resave(buf, 0);
	printf("saved\n");
	printf("------------------\n\n");
}

// 학생 제거
int remove_student() {
	FILE* fp;
	struct student_information stu_inf;
	char buf[buf_lenth][1024];
	char answer[64];
	int num = 1;

	fopen_s(&fp, "student.txt", "r");
	for (int i = 0; i < getTotalLine(); i++) {
		fgets(buf[i], sizeof(buf[i]), fp);
		for (int j = 0; j < sizeof(buf[i]); j++) {
			if (buf[i][j] == '\n') {
				buf[i][j] = '\0';
				break;
			}
		}

		char* bufPointer = cryption(buf[i], nomalStrDefine, keyC, sizeof(buf[i]));
		for (int j = 0; j < sizeof(buf[i]); j++) {
			buf[i][j] = *bufPointer;
			bufPointer++;
		}
	}
	fclose(fp);

	printf("------------------");
	while (true) {
		printf("\nremove student number: ");
		scanf_s("%d", &num);
		if (0 < num && num < getTotalLine() + 1)
			break;
		printf("please enter again\n");
	}
	stu_inf = read_student_information(num);

	while (true) {
		printf("\nremove student information");
		print_student(stu_inf);
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

		resave(buf, 0);
		rearrangement(1);
		printf("------------------\n\n");
		return 1;
	}
	printf("------------------\n\n");
	return 0;
}

// 파일 있는지 확인 후 없으면 생성
void file_check() {
	FILE* fp;

	fopen_s(&fp, "student.txt", "a");
	fclose(fp);
}

// 아이디 갯수
int getTotalLineId() {
	FILE* fp = NULL;
	errno_t err;
	int line = 0;
	char c;

	fopen_s(&fp, "id.txt", "r");
	while ((c = fgetc(fp)) != EOF)
		if (c == '\n') line++;
	fclose(fp);
	return line;
}

// 마스터 아이디 추가
void add_master_id() {
	FILE* fp;
	char id[7] = "master";
	char password[12] = "master1234!";
	if (!getTotalLineId()) {
		fopen_s(&fp, "id.txt", "a");
		char* idPointer = cryption(id, keyC, nomalStrDefine, sizeof(id));
		for (int i = 0; i < sizeof(id); i++) {
			id[i] = *idPointer;
			idPointer++;
		}
		fputs(id, fp);
		fputs("\n", fp);
		fclose(fp);

		fopen_s(&fp, "password.txt", "a");
		char* passwordPointer = cryption(password, keyC, nomalStrDefine, sizeof(password));
		for (int i = 0; i < sizeof(password); i++) {
			password[i] = *passwordPointer;
			passwordPointer++;
		}
		fputs(password, fp);
		fputs("\n", fp);
		fclose(fp);
	}
}

// 아이디, 비번 파일 확인
void id_file_check() {
	FILE* fp;

	fopen_s(&fp, "id.txt", "a");
	fclose(fp);

	fopen_s(&fp, "password.txt", "a");
	fclose(fp);
	add_master_id();
}

// 로그인
int login() {
	FILE* fp;
	char id[17] = "";
	char password[17] = "";
	char ids[17] = "";
	char passwords[17] = "";
	int numOfId = getTotalLineId();

	printf("------------------\n");
	printf("enter your id: ");
	fflush(stdin);
	scanf_s("%s", &id, 17);
	printf("enter your password: ");
	fflush(stdin);
	scanf_s("%s", &password, 17);

	// 마스터 아이디 로그인
	if (!strcmp("master", id) && !strcmp("master1234!", password)) {
		printf("master id logged in\n");
		printf("------------------\n\n");
		return 3;
	}

	// 일반 아이디 로그인
	for (int i = 0; i < getTotalLineId(); i++) {
		fopen_s(&fp, "id.txt", "r");
		for (int j = 0; j < i + 2; j++) {
			fgets(ids, sizeof(ids), fp);
			for (int k = 0; k < sizeof(ids); k++) {
				if (ids[k] == '\n') {
					ids[k] = '\0';
					break;
				}
			}
			char* idsPointer = cryption(ids, nomalStrDefine, keyC, sizeof(ids));
			for (int i = 0; i < sizeof(ids); i++) {
				ids[i] = *idsPointer;
				idsPointer++;
			}
		}
		fclose(fp);

		fopen_s(&fp, "password.txt", "r");
		for (int j = 0; j < i + 2; j++) {
			fgets(passwords, sizeof(passwords), fp);
			for (int k = 0; k < sizeof(passwords); k++) {
				if (passwords[k] == '\n') {
					passwords[k] = '\0';
					break;
				}
			}
			char* passwordsPointer = cryption(passwords, nomalStrDefine, keyC, sizeof(passwords));
			for (int i = 0; i < sizeof(passwords); i++) {
				passwords[i] = *passwordsPointer;
				passwordsPointer++;
			}
		}
		fclose(fp);

		for (int j = 0; j < sizeof(ids) - 1; j++) {
			if (ids[j] == '\n') {
				ids[j] = '\0';
				break;
			}
		}
		for (int j = 0; j < sizeof(passwords) - 1; j++) {
			if (passwords[j] == '\n') {
				passwords[j] = '\0';
				break;
			}
		}

		if (!strcmp(ids, id) && !strcmp(passwords, password)) {
			printf("logged in\n");
			printf("------------------\n\n");
			return 1;
		}
	}
	printf("wrong id or password\n");
	printf("------------------\n\n");
	return 0;
}

// 아이디 생성
void create_id() {
	FILE* fp=NULL;
	char id[17] = "";
	char password[17] = "";
	char col[16] = "";
	char dupId[17] = "";
	int duplicate = 1;

	printf("------------------");
	while (true) {
		printf("\nenter your id (max lenth 16): ");
		fflush(stdin);
		scanf_s("%s", &id, 17);
		printf("enter your password (max lenth 16): ");
		fflush(stdin);
		scanf_s("%s", &password, 17);
		printf("this is collect (y or n or exit): ");
		fflush(stdin);
		scanf_s("%s", &col, 16);

		// 아이디 중복 확인
		fopen_s(&fp, "id.txt", "r");
		for (int i = 0; i < getTotalLineId(); i++) {
			fgets(dupId, sizeof(dupId), fp);
			for (int j = 0; j < sizeof(dupId) - 1; j++) {
				if (dupId[j] == '\n') {
					dupId[j] = '\0';
					break;
				}
			}
			char* dupIdPointer = cryption(dupId, nomalStrDefine, keyC, sizeof(dupId));
			for (int i = 0; i < sizeof(dupId); i++) {
				dupId[i] = *dupIdPointer;
				dupIdPointer++;
			}
			if (!strcmp(id, dupId)) {
				duplicate = 0;
				break;
			}
		}
		fclose(fp);

		if (!duplicate)
			printf("duplicated id\n");
		else if (!strcmp(col, "y") || !strcmp(col, "yes")) {
			fopen_s(&fp, "id.txt", "a");
			char* idPointer = cryption(id, keyC, nomalStrDefine, sizeof(id));
			for (int i = 0; i < sizeof(id); i++) {
				id[i] = *idPointer;
				idPointer++;
			}
			fputs(id, fp);
			fputs("\n", fp);
			fclose(fp);

			fopen_s(&fp, "password.txt", "a");
			char* passwordPointer = cryption(password, keyC, nomalStrDefine, sizeof(password));
			for (int i = 0; i < sizeof(password); i++) {
				password[i] = *passwordPointer;
				passwordPointer++;
			}
			fputs(password, fp);
			fputs("\n", fp);
			fclose(fp);

			printf("created id\n");
			printf("------------------\n\n");
			return 1;
		}
		else if (!strcmp(col, "exit")) {
			printf("------------------\n\n");
			return 0;
		}
	}
}

int main() {
	file_check();
	id_file_check();
	rearrangement(0);

	int num_of_student = getTotalLine();
	int select = 0;
	int logged = 0;

	while (true) {
		select = 0;
		printf("------------------\n");
		printf("Student Record System\n");
		printf("1. add student\n");
		printf("2. remove student\n");
		printf("3. search student\n");
		printf("4. find student\n");
		printf("5. edit student(memo)\n");
		printf("6. login\n");
		printf("7. create id\n");
		printf("8. log out\n");
		printf("9. create key\n");
		printf("10. Exit\n");

		num_of_student = getTotalLine();
		if (num_of_student == 0)
			printf("you should add student\n");
		fflush(stdin);
		printf("select number: ");
		scanf_s("%d", &select);
		printf("------------------\n\n");

		if (select == 1 && logged == 1)
			add_student();
		else if (!logged && select != 6 && select < 10)
			printf("you should login\n\n");
		else if (logged == 3 && select != 7 && select != 8 && select != 10)
			printf("master id can only create id\n\n");
		else if (num_of_student == 0 && select == 1)
			printf("please enter again\nyou should add student\n\n");
		else if (logged && select == 6)
			printf("you already logged in\n\n");
		else if (logged != 3 && select == 7)
			printf("create id can only master\n\n");
		else if (select == 2 && logged == 1)
			remove_student();
		else if (select == 3 && logged == 1)
			search_student();
		else if (select == 4 && logged == 1)
			find_student();
		else if (select == 5 && logged == 1)
			edit_student();
		else if (select == 6)
			logged = login();
		else if (select == 7 && logged == 3)
			create_id();
		else if (select == 8 && logged) {
			printf("logged out");
			logged = 0;
		}
		else if (select == 10)
			break;
		else
			printf("please enter again\n\n");
	}
	return 0;
}
