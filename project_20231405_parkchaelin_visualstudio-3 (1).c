#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 함수 선언
void searchNation();
void attendCount();
void goalDiff();

// worldCup 구조체 선언
typedef struct worldCup {
	int year;
	char gametype[30];
	char country1[30];
	char country2[30];
	int score1;
	int score2;
	char explanation[100];
	int attendance;
} worldCup;

int main()
{
	// 사용자로부터 입력값을 받아 user_value에 저장
	char choice[20];

	// user_value에 들어있는 값에 따라 실행
	while (1) {
		printf("Write your command >>\n");
		scanf("%s", choice);

		if (strcmp(choice, "searchNation") == 0) {
			searchNation();
		}
		else if (strcmp(choice, "attendCount") == 0) {
			attendCount();
		}
		else if (strcmp(choice, "goalDiff") == 0) {
			goalDiff();
		}
		else if (strcmp(choice, "exit") == 0) {
			return 0;
		}
		else {
			printf("Invalid command\n");
		}
	}
}

// searchNation 함수 정의
void searchNation() {

	// 사용자로부터 값을 받아 user_value에 저장
	printf("Which country do you want to search? >>\n");
	char user_value[20];
	gets(user_value);
	gets(user_value);

	// WorldCupMatches.dat 파일을 이진 읽기 모드로 열기
	FILE* rf;	// 읽기 모드 파일 포인터
	FILE* wf;	// 쓰기 모드 파일 포인터
	char fname[] = "WorldCupMatches.dat";
	if ((rf = fopen(fname, "rb")) == NULL) {
		printf("fail to open the file");
		exit(1);
	};
	if ((wf = fopen("search_result.csv", "w")) == NULL) {
		printf("fail to open the file");
		exit(1);
	};

	fprintf(wf, "Year,Game Type,Country 1,Country 2,Score 1,Score 2,Explanation,Attendence\n");
	int process = 0;		// 파일 데이터가 있는지 없는지 확인하는 표시
	worldCup check;
	fread(&check, sizeof(worldCup), 1, rf);
	while (!feof(rf)) {
		if (strcmp(check.country1, user_value) == 0) {
			fprintf(wf, "%d,%s,%s,%s,%d,%d,%s,%d\n", check.year, check.gametype, check.country1, check.country2, check.score1, check.score2, check.explanation, check.attendance);
			process = 1;
		}
		else if (strcmp(check.country2, user_value) == 0) {
			fprintf(wf, "%d,%s,%s,%s,%d,%d,%s,%d\n", check.year, check.gametype, check.country1, check.country2, check.score1, check.score2, check.explanation, check.attendance);
			process = 1;
		}
		else if (strcmp("all", user_value) == 0) {
			fprintf(wf, "%d,%s,%s,%s,%d,%d,%s,%d\n", check.year, check.gametype, check.country1, check.country2, check.score1, check.score2, check.explanation, check.attendance);
			process = 1;
		}
		fread(&check, sizeof(worldCup), 1, rf);
	}

	// 파일 포인터 닫기
	fclose(rf);
	fclose(wf);

	// 작성한 파일에 데이터가 비어있으면 제거
	if (process == 0) {
		printf("There is no game including this country.\n");
		remove("search_result.csv");
	}
}

// attendCount 함수 정의
void attendCount() {

	// 사용자로부터 값을 입력받아 lower_limit에 저장
	printf("What is the lower limit for attendance? >>\n");
	int lower_limit;
	scanf("%d", &lower_limit);

	// WorldCupMatches.dat 파일을 이진 읽기 모드로 열기
	FILE* rf;	// 읽기 모드 파일 포인터
	FILE* wf;	// 쓰기 모드 파일 포인터
	char fname[] = "WorldCupMatches.dat";
	if ((rf = fopen(fname, "rb")) == NULL) {
		printf("fail to open the file");
		exit(1);
	};
	if ((wf = fopen("attend_result.csv", "w")) == NULL) {
		printf("fail to open the file");
		exit(1);
	};

	fprintf(wf, "Year,Game Type,Country 1,Country 2,Score 1,Score 2,Explanation,Attendence\n");

	int process = 0;				// 나중에 파일을 없앨지 말지 결정하는 표시
	worldCup check;
	fread(&check, sizeof(worldCup), 1, rf);

	if (lower_limit < 0) {			// 입력값이 0보다 작으면 Invalid input 출력
		printf("Invalid input");
	}
	// 입력값이 0 또는 양수이면 다음을 실행
	while (!feof(rf) && lower_limit >= 0) {
		if (check.attendance >= lower_limit) {
			process = 1;
			fprintf(wf, "%d,%s,%s,%s,%d,%d,%s,%d\n", check.year, check.gametype, check.country1, check.country2, check.score1, check.score2, check.explanation, check.attendance);
		}
		fread(&check, sizeof(worldCup), 1, rf);
	}

	fclose(rf);
	fclose(wf);

	if (process == 0) {
		remove("attend_result.csv");
		if (lower_limit >= 0)
			printf("There is no corresponding game.\n");
	}
}

void goalDiff() {

	// 사용자로부터 값을 입력받아 diff에 저장
	printf("Goal difference? >>\n");
	int diff;
	scanf("%d", &diff);

	// WorldCupMatches.dat 파일을 이진 읽기 모드로 열기
	FILE* rf;	// 읽기 모드 파일 포인터
	FILE* wf;	// 쓰기 모드 파일 포인터
	char fname[] = "WorldCupMatches.dat";
	if ((rf = fopen(fname, "rb")) == NULL) {
		printf("fail to open the file");
		exit(1);
	};
	if ((wf = fopen("diff_result.csv", "w")) == NULL) {
		printf("fail to open the file");
		exit(1);
	};

	fprintf(wf, "Year,Game Type,Country 1,Country 2,Score 1,Score 2,Explanation,Attendence\n");

	int process = 0;				// 나중에 파일을 없앨지 말지 결정하는 표시
	worldCup check;
	fread(&check, sizeof(worldCup), 1, rf);

	if (diff < 0) {			// 입력값이 0보다 작으면 Invalid input 출력
		printf("Invalid input");
	}
	else {							// 입력값이 0 또는 양수이면 다음을 실행
		while (!feof(rf)) {
			if ((check.score1 - check.score2 == diff) || (check.score2 - check.score1 == diff)) {
				fprintf(wf, "%d,%s,%s,%s,%d,%d,%s,%d\n", check.year, check.gametype, check.country1, check.country2, check.score1, check.score2, check.explanation, check.attendance);
				process = 1;
			}
			fread(&check, sizeof(worldCup), 1, rf);
		}
	}

	fclose(rf);
	fclose(wf);

	if (process == 0) {
		remove("attend_result.csv");
		if (diff >= 0)
			printf("There is no corresponding game.\n");
	}
}