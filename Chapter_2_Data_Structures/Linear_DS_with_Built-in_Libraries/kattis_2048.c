#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <stdio.h>

typedef long long ll;
int grid[4][4];
int main() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    int op;
    scanf("%d", &op);
    // left, up, right, down
    if (op == 0) {
        for (int i = 0; i < 4; i++) {  // for each row
            // shift all left
            for (int t = 0; t < 3; t++) {
                for (int j = 0; j < 3; j++) {
                    if (grid[i][j] == 0) {
                        grid[i][j] = grid[i][j + 1];
                        grid[i][j + 1] = 0;
                    }
                }
            }
            // combine adjacent
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == grid[i][j + 1]) {
                    grid[i][j] *= 2;
                    grid[i][j + 1] = 0;
                }
            }
            // shift all left
            for (int t = 0; t < 3; t++) {
                for (int j = 0; j < 3; j++) {
                    if (grid[i][j] == 0) {
                        grid[i][j] = grid[i][j + 1];
                        grid[i][j + 1] = 0;
                    }
                }
            }
        }
    } else if (op == 2) {
        for (int i = 0; i < 4; i++) {
            // shift all right
            for (int t = 0; t < 3; t++) {
                for (int j = 3; j > 0; j--) {
                    if (grid[i][j] == 0) {
                        grid[i][j] = grid[i][j - 1];
                        grid[i][j - 1] = 0;
                    }
                }
            }
            // combine adjacent
            for (int j = 3; j > 0; j--) {
                if (grid[i][j] == grid[i][j - 1]) {
                    grid[i][j] *= 2;
                    grid[i][j - 1] = 0;
                }
            }
            // shift all right
            for (int t = 0; t < 3; t++) {
                for (int j = 3; j > 0; j--) {
                    if (grid[i][j] == 0) {
                        grid[i][j] = grid[i][j - 1];
                        grid[i][j - 1] = 0;
                    }
                }
            }
        }
    } else if (op == 3) {
        for (int i = 0; i < 4; i++) {
            // shift all down
            for (int t = 0; t < 3; t++) {
                for (int j = 3; j > 0; j--) {
                    if (grid[j][i] == 0) {
                        grid[j][i] = grid[j - 1][i];
                        grid[j - 1][i] = 0;
                    }
                }
            }
            // combine adjacent
            for (int j = 3; j > 0; j--) {
                if (grid[j][i] == grid[j - 1][i]) {
                    grid[j][i] *= 2;
                    grid[j - 1][i] = 0;
                }
            }
            // shift all down
            for (int t = 0; t < 3; t++) {
                for (int j = 3; j > 0; j--) {
                    if (grid[j][i] == 0) {
                        grid[j][i] = grid[j - 1][i];
                        grid[j - 1][i] = 0;
                    }
                }
            }
        }
    } else if (op == 1) {
        for (int i = 0; i < 4; i++) {  // for each row
            // shift all up
            for (int t = 0; t < 3; t++) {
                for (int j = 0; j < 3; j++) {
                    if (grid[j][i] == 0) {
                        grid[j][i] = grid[j + 1][i];
                        grid[j + 1][i] = 0;
                    }
                }
            }
            // combine adjacent
            for (int j = 0; j < 3; j++) {
                if (grid[j][i] == grid[j + 1][i]) {
                    grid[j][i] *= 2;
                    grid[j + 1][i] = 0;
                }
            }
            // shift all up
            for (int t = 0; t < 3; t++) {
                for (int j = 0; j < 3; j++) {
                    if (grid[j][i] == 0) {
                        grid[j][i] = grid[j + 1][i];
                        grid[j + 1][i] = 0;
                    }
                }
            }
        }
    }

    // print grid
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}