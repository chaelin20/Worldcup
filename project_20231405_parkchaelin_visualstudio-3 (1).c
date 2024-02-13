#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �Լ� ����
void searchNation();
void attendCount();
void goalDiff();

// worldCup ����ü ����
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
	// ����ڷκ��� �Է°��� �޾� user_value�� ����
	char choice[20];

	// user_value�� ����ִ� ���� ���� ����
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

// searchNation �Լ� ����
void searchNation() {

	// ����ڷκ��� ���� �޾� user_value�� ����
	printf("Which country do you want to search? >>\n");
	char user_value[20];
	gets(user_value);
	gets(user_value);

	// WorldCupMatches.dat ������ ���� �б� ���� ����
	FILE* rf;	// �б� ��� ���� ������
	FILE* wf;	// ���� ��� ���� ������
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
	int process = 0;		// ���� �����Ͱ� �ִ��� ������ Ȯ���ϴ� ǥ��
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

	// ���� ������ �ݱ�
	fclose(rf);
	fclose(wf);

	// �ۼ��� ���Ͽ� �����Ͱ� ��������� ����
	if (process == 0) {
		printf("There is no game including this country.\n");
		remove("search_result.csv");
	}
}

// attendCount �Լ� ����
void attendCount() {

	// ����ڷκ��� ���� �Է¹޾� lower_limit�� ����
	printf("What is the lower limit for attendance? >>\n");
	int lower_limit;
	scanf("%d", &lower_limit);

	// WorldCupMatches.dat ������ ���� �б� ���� ����
	FILE* rf;	// �б� ��� ���� ������
	FILE* wf;	// ���� ��� ���� ������
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

	int process = 0;				// ���߿� ������ ������ ���� �����ϴ� ǥ��
	worldCup check;
	fread(&check, sizeof(worldCup), 1, rf);

	if (lower_limit < 0) {			// �Է°��� 0���� ������ Invalid input ���
		printf("Invalid input");
	}
	// �Է°��� 0 �Ǵ� ����̸� ������ ����
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

	// ����ڷκ��� ���� �Է¹޾� diff�� ����
	printf("Goal difference? >>\n");
	int diff;
	scanf("%d", &diff);

	// WorldCupMatches.dat ������ ���� �б� ���� ����
	FILE* rf;	// �б� ��� ���� ������
	FILE* wf;	// ���� ��� ���� ������
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

	int process = 0;				// ���߿� ������ ������ ���� �����ϴ� ǥ��
	worldCup check;
	fread(&check, sizeof(worldCup), 1, rf);

	if (diff < 0) {			// �Է°��� 0���� ������ Invalid input ���
		printf("Invalid input");
	}
	else {							// �Է°��� 0 �Ǵ� ����̸� ������ ����
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