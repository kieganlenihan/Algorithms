#include <stdlib.h>
#include <stdio.h>

int seq2(int x) {
    return (x - 2) * (x-2) - 2;
}
int sum_seq2(int low, int high) {
    int sum = 0;
    for (int i = low;  i < high; i++) {
        sum += seq2(i);
    }
    return sum;
}
int main(void) {
    const int N = 4;
    int x[N] = {1, 2, 3, 4};
    for (int i = 0;  i < N; i++) {
        printf("seq2(%d) = %d\n", x[i], seq2(x[i]));
    }
    int low[N] = {0, 0, 3, 9};
    int high[N] = {0, 2, 6, 7};
    for (int i = 0; i < N; i++) {
        printf("sum_seq2(%d, %d) = %d\n\n", low[i], high[i], sum_seq2(low[i], high[i]));
    }
    return(EXIT_SUCCESS);
}