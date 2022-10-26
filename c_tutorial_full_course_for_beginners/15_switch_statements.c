#include <stdio.h>

int main() {

    int grade;

    printf("Enter a grade (danish): ");
    scanf("%d", &grade);

    switch(grade) {
        case 12:
            printf("Perfect\n");
            break;
        case 10:
            printf("10\n");
            break;
        case 7:
            printf("7\n");
            break;
        case 4:
            printf("4\n");
            break;
        case 02:
            printf("02\n");
            break;
        case 00:
            printf("better luck next time!\n");
            break;
        case 03:
            printf("WTF!\n");
            break;
        default:
            return 1;

    }

    return 0;
}