#include <stdio.h>

int main() {
    int age;

    printf("\nEnter your age: ");
    scanf("%d", &age);

    if (age >= 18) {
        printf("You are greater or older then 18!\n");
    } else {
        printf("You are younger then 18!\n");
    }

    return 0;
}