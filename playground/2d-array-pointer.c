#include <stdio.h>

int main() {
    const int a[2][3] = {{1, 2, 3}, {4, 5, 6}};

    const int* p = &a[0][0];
    printf("%d\n", *(p + 4)); // 5

    const int (*p2)[3] = a;
    const int** p3 = (int **)p2;
    printf("%d\n", p2[1][0]); // 4
    printf("%d\n", *(p3 + 2)); // 5
    printf("%s\n", (int **)p2 == p3 ? "p2 == p3" : "p2 != p3");
}
