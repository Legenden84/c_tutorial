#include <stdio.h>
#include <stdbool.h>

int main() {
    char a = 'C';
    char b[] = "Legenden";

    float c = 3.141592653589793;
    double d = 3.141592653589793;

    printf("float: %0.15f\n", c);
    printf("double: %0.15lf\n", d);

    return 0;
}