#include <stdio.h>
#include <ctype.h>

int main() {
    char unit;
    float temp;

    printf("\nIs the temperature in (F) or (C)?: ");
    scanf("%c", &unit);

    // unit = toupper(unit);

    if (unit == 'C' || unit == 'c') {
        printf("\nEnter the temp in Celsius: ");
        scanf("%f", &temp);
        temp = (temp * 9 / 5 + 32);
        printf("\nThe temp in Farenheit is: %.1f\n", temp);
    } else if (unit == 'F' || unit == 'f') {
        printf("\nEnter the temp in Farenheit: ");
        scanf("%f", &temp);
        temp = ((temp - 32) * 5) / 9;
        printf("\nThe temp in Celsius is: %.1f\n", temp);
    } else {
        printf("The input %c is an invalid input!", unit);
    }

    return 0;
}