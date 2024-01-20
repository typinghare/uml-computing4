#include <cstdlib>

int main() {
    const int arraySize = 10;

    int* pIntArray;
    pIntArray = (int*) malloc(arraySize * sizeof(int));
    free(pIntArray);

    return 0;
}
