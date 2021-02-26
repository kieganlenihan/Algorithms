#include <stdlib.h>
#include <stdio.h>

void read_file(FILE *f, char matrix[10][10]) {
    int i = 0; //row index
    int j = 0; //column index
    for (;;) {
        int ch = fgetc(f);
        switch (ch) {
            case '\n':
                if (j % 10 == 0) {
                    printf("reached end of line correctly, char is %d\n", ch);
                    matrix[i][j] = ch;
                    j = 0;
                    i ++;
                }
                else {
                    fprintf(stderr, "line %d ends at wrong place\n", i + 1);
                    exit(EXIT_FAILURE);
                }
                break;
            case EOF:
                fprintf(stderr, "unexpected EOF\n");
                exit(EXIT_FAILURE);
                break;
            default:
                printf("char is %d, i is %d, j is %d\n", ch, i, j);
                matrix[i][j] = ch;
                j++;
                break;
        }
        if (i == 10) {
            break;
        }
    }
}

void rotate_matrix(char matrix[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c", matrix[9 - j][i]);
        }
        printf("%c", '\n');
    }
}

int main(int argc, char *argv[]) {
    char matrix[10][10];
    FILE *f;

    if (argc != 2) {
        fprintf(stderr, "Usage: rotateMatrix input %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "could not open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    read_file(f, matrix);

    int ch = fgetc(f);
    if (ch != EOF) {
        fprintf(stderr, "File is wrong length\n");
        exit(EXIT_FAILURE);
    }
    
    fclose(f);

    rotate_matrix(matrix);

    return EXIT_SUCCESS;
}