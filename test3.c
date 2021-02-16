#include <stdlib.h>
#include <stdio.h>

int seq3(int x, int y) {
    return (y + 4) * (x - 1) + 3;
}
int is_negative(int num) {
    if (num < 0) {
        return 1;
    }
    return 0;
}
int count_neg_seq3_range(int xLow, int xHi, int yLow, int yHi) {
    int count = 0;
    for (int i = xLow; i < xHi; i++) {
        for (int j = yLow; j < yHi; j++) {
            count += is_negative(seq3(i, j));
        }
    }
    return count;
}
int main(void) {
    const int N = 4;
    int x[N] = {-5, -4, -3, -2};
    int y[N] = {-5, -4, 0, 5};
    for (int i = 0;  i < N; i++) {
        printf("seq3(%d, %d) = %d\n", x[i], x[i], seq3(x[i], x[i]));
    }
    int xLow[N] = {0, 0, 3, 9};
    int xHi[N] = {2, 2, 6, 7};
    int yLow[N] = {0, 4, 5, -2};
    int yHi[N] = {3, -6, 2, 5};
    for (int i = 0; i < N; i++) {
        printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n\n", xLow[i], xHi[i], yLow[i], yHi[i], count_neg_seq3_range(xLow[i], xHi[i], yLow[i], yHi[i]));
    }
    return(EXIT_SUCCESS);
}