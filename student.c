#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct student {
    char id[20];
    char name[30];
    int m[5];
    int total;
    float per;
    char grade[3];
    int cgpa;
};

int main() {

    FILE *fp;
    struct student s[50];
    int n, i, j;
    float avg = 0, high = 0, low = 100;
    int gradeCount[8] = {0};

    fp = fopen("students.txt", "r");

    if (fp == NULL) {
        printf("File not found\n");
        return 0;
    }

    fscanf(fp, "%d", &n);

    for (i = 0; i < n; i++) {

        fscanf(fp, "%s %s", s[i].id, s[i].name);

        // ID validation
        for (j = 0; s[i].id[j] != '\0'; j++) {
            if (!isalnum(s[i].id[j])) {
                printf("Invalid ID for student %d\n", i + 1);
            }
        }

        // Name validation
        for (j = 0; s[i].name[j] != '\0'; j++) {
            if (!isalpha(s[i].name[j])) {
                printf("Invalid Name for student %d\n", i + 1);
            }
        }
        s[i].total = 0;
        int fail = 0;

        for (j = 0; j < 5; j++) {
            fscanf(fp, "%d", &s[i].m[j]);

            if (s[i].m[j] < 0 || s[i].m[j] > 100) {
                printf("Invalid marks for %s\n", s[i].id);
                s[i].m[j] = 0;
            }

            if (s[i].m[j] < 50)
                fail = 1;

            s[i].total += s[i].m[j];
        }
        s[i].per = s[i].total / 5.0;

        if (fail || s[i].per < 50) {
            strcpy(s[i].grade, "F");
            s[i].cgpa = 0;
            gradeCount[7]++;
        }
        else if (s[i].per >= 90) {
            strcpy(s[i].grade, "O");
            s[i].cgpa = 10;
            gradeCount[0]++;
        }
        else if (s[i].per >= 85) {
            strcpy(s[i].grade, "A+");
            s[i].cgpa = 9;
            gradeCount[1]++;
        }
        else if (s[i].per >= 75) {
            strcpy(s[i].grade, "A");
            s[i].cgpa = 8;
            gradeCount[2]++;
        }
        else if (s[i].per >= 65) {
            strcpy(s[i].grade, "B+");
            s[i].cgpa = 7;
            gradeCount[3]++;
        }
        else if (s[i].per >= 60) {
            strcpy(s[i].grade, "B");
            s[i].cgpa = 6;
            gradeCount[4]++;
        }
        else if (s[i].per >= 55) {
            strcpy(s[i].grade, "C");
            s[i].cgpa = 5;
            gradeCount[5]++;
        }
        else {
            strcpy(s[i].grade, "D");
            s[i].cgpa = 4;
            gradeCount[6]++;
        }
        avg += s[i].per;
        if (s[i].per > high) high = s[i].per;
        if (s[i].per < low) low = s[i].per;
    }
    fclose(fp);
    printf("\nID\tName\tTotal\t%%\tGrade\tCGPA\n");
    printf("----------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%s\t%s\t%d\t%.2f\t%s\t%d\n",
               s[i].id, s[i].name, s[i].total,
               s[i].per, s[i].grade, s[i].cgpa);
    }
    printf("\nClass Average = %.2f\n", avg / n);
    printf("Highest = %.2f\n", high);
    printf("Lowest = %.2f\n", low);
    printf("\nGrade Count:\n");
    printf("O:%d A+:%d A:%d B+:%d B:%d C:%d D:%d F:%d\n",
           gradeCount[0], gradeCount[1], gradeCount[2],
           gradeCount[3], gradeCount[4], gradeCount[5],
           gradeCount[6], gradeCount[7]);
    return 0;
}
