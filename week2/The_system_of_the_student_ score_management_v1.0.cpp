#include <stdio.h>

void input_score(long student_ID[], int score[], int n);
void print_total_and_average(int n, int score[]);
void rank_by_grade_in_descending_order(long student_ID[], int score[], int n);
void print_score(long student_ID[], int score[], int n);
void rank_by_student_ID_in_ascending_order(long student_ID[], int score[], int n);
int search_student_rank_and_grade_by_student_ID(long student_ID[], int score[], int n);
void count_the_percentage_of_the_each_category(long student_ID[], int score[], int n);

int main()
{
	long student_ID[30];
	int score[30], n, choice;
	printf("1. Input record\n");
	printf("2. Caculate total and average score of course\n");
	printf("3. Sort in descending order by score\n");
	printf("4. Sort in ascending order by number\n");
	printf("5. search by number\n");
	printf("6. Statistic analysis\n");
	printf("0. Exit\n\n");
	do {
		printf("Please enter your choice:");
		scanf_s("%d", &choice);
		if (choice <= 6 && choice >= 0) {
			switch (choice)
			{
			case 1:
				printf("Please input the number of the students(n <= 30):");
				scanf_s("%d", &n);
				input_score(student_ID, score, n);
				break;
			case 2:
				print_total_and_average(n, score);
				break;
			case 3:
				rank_by_grade_in_descending_order(student_ID, score, n);
				printf("Rank by grade in descending order\n");
				print_score(student_ID, score, n);
				break;
			case 4:
				rank_by_student_ID_in_ascending_order(student_ID, score, n);
				printf("rank by student number in ascending order\n");
				print_score(student_ID, score, n);
				break;
			case 5:
				search_student_rank_and_grade_by_student_ID(student_ID, score, n);
				break;
			case 6:
				count_the_percentage_of_the_each_category(student_ID, score, n);
				break;
			case 0:
				printf("Exit successfully! \\*_*/");
				break;
			}
		}
		else {
			printf("Please input a correct choice.  !!-_-!!\n");
		}
	} while (choice != 0);
	return 0;
}

void input_score(long student_ID[], int score[], int n) {
	if (n > 30) {
		printf("The number exceeds limit.\n");
	}
	else {
		printf("Please input the student's number and his score\n");
		for (int i = 0; i < n; i++) {
			scanf_s("%ld %d", &student_ID[i], &score[i]);
		}
	}
}

void print_total_and_average(int n, int score[]) {
	int total = 0;
	float average;
	for (int i = 0; i < n; i++) {
		total += score[i];
	}
	average = total / (float)n;
	printf("total = %d\taverage = %.2f\n", total, average);
	printf("\n");
}

void rank_by_grade_in_descending_order(long student_ID[], int score[], int n) {
	int temp, k;
	for (int i = 0; i < n - 1; i++) {
		k = i;
		for (int j = i + 1; j < n; j++) {
			if (score[k] < score[j]) {
				k = j;
			}
		}
		if (k != i) {
			temp = score[i];
			score[i] = score[k];
			score[k] = temp;
			temp = student_ID[i];
			student_ID[i] = student_ID[k];
			student_ID[k] = temp;
		}
	}
}

void print_score(long student_ID[], int score[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%ld\t%d\n", student_ID[i], score[i]);
	}
	printf("\n");
}

void rank_by_student_ID_in_ascending_order(long student_ID[], int score[], int n) {
	int temp, k;
	for (int i = 0; i < n - 1; i++) {
		k = i;
		for (int j = i + 1; j < n; j++) {
			if (student_ID[k] > student_ID[j]) {
				k = j;
			}
		}
		if (k != i) {
			temp = score[i];
			score[i] = score[k];
			score[k] = temp;
			temp = student_ID[i];
			student_ID[i] = student_ID[k];
			student_ID[k] = temp;
		}
	}
}
int search_student_rank_and_grade_by_student_ID(long student_ID[], int score[], int n) {
	long num;
	rank_by_grade_in_descending_order(student_ID, score, n);
	printf("please input the student number:");
	scanf_s("%ld", &num);
	for (int i = 0; i < n; i++) {
		if (num == student_ID[i]) {
			printf("The student's ranking is %d\n", i + 1);
			printf("The student's score is %d\n\n", score[i]);
			return 0;
		}
	}
	printf("Not existence\n");
	return 0;
}

void count_the_percentage_of_the_each_category(long student_ID[], int score[], int n) {
	int excellent = 0, good = 0, medium = 0, pass = 0, fail = 0;
	float excellent_avg, good_avg, medium_avg, pass_avg, fail_avg;
	for (int i = 0; i < n; i++) {
		if (score[i] <= 100 && score[i] >= 90) {
			excellent++;
		}
		else if (score[i] < 90 && score[i] >= 80) {
			good++;
		}
		else if (score[i] < 80 && score[i] >= 70) {
			medium++;
		}
		else if (score[i] < 70 && score[i] >= 60) {
			pass++;
		}
		else if (score[i] < 60) {
			fail++;
		}
	}
	excellent_avg = excellent / (float)n;
	good_avg = good / (float)n;
	medium_avg = medium / (float)n;
	pass_avg = pass / (float)n;
	fail_avg = fail / (float)n;
	printf("Excellent account for %.2f\n", excellent_avg);
	printf("Good account for %.2f\n", good_avg);
	printf("Medium account for %.2f\n", medium_avg);
	printf("Pass account for %.2f\n", pass_avg);
	printf("Fail account for %.2f\n", fail_avg);
}
