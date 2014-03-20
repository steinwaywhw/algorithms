#include <stdio.h>

void logger(int i, int from, int to) {
    printf("Move %d from %d to %d\n", i, from, to);
}

int other(int from, int to) {
    if (from + to == 3)
        return 3;
    if (from + to == 4)
        return 2;
    if (from + to == 5)
        return 1;
        
    return -1;
}

void hanoi(int n, int from, int to) {
    if (n == 0)
        return;
    
    if (n == 1) {
        logger (n, from, to);
        return;
    }
    
    hanoi (n - 1, from, other (from, to));
    logger (n, from, to);
    hanoi (n - 1, other (from, to), to);
}

int main() {
    hanoi(3, 1, 3);
}
        