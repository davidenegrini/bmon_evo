/* C simple ASCII to number converter */
#include <conio.h>
#include <stdio.h>

int main() {
    char c;
    while (1) {
        c=getch();
        printf("%c %d\n", c, c);
    }
    return 0;
}
