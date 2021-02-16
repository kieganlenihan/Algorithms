#include <stdlib.h>
#include <stdio.h>

int seq1(int x) {
    return 3 * (x - 2) + 1;
}
void print_seq1_range(int low, int high) {
    for (int i = low;  i < high; i++) {
        if (i + 1 == high) {
            printf("%d", seq1(i));
        }
        else {
            printf("%d, ", seq1(i));
        }
    }
    printf("\n");
}
int main(void) {
    const int N = 4;
    // int x[N] = {-715827882, 2, 3, 4};
    // for (int i = 0;  i < N; i++) {
    //     printf("seq1(%d) = %d\n", x[i], seq1(x[i]));
    // }
    int low[N] = {0, 3, -1, -2};
    int high[N] = {0, 4, 7, -5};
    for (int i = 0; i < N; i++) {
        printf("print_seq1_range(%d, %d)\n", low[i], high[i]);
        print_seq1_range(low[i], high[i]);
    }
    return(EXIT_SUCCESS);
}