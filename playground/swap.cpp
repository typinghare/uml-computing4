#include <iostream>

using namespace std;

void printArray(const int* array, const int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

void swapArray4(int p1[4], int p2[4]) {
    for (int i= 0; i < 4; ++i) {
        const int temp = p1[0];
        p1[i] = p2[i];
        p2[i] = temp;
    }
}

int main() {
    int first[4];
    int second[4];
    for (int i = 0; i < 4; i++) {
        *(first + i) = i;
        *(second + i) = i + 10;
    }

    cout << "print first: ";
    printArray(first, 4);
    cout << "print second:";
    printArray(second, 4);

    swapArray4(first, second);

    cout << "print first: ";
    printArray(first, 4);
    cout << "print second:";
    printArray(second, 4);

    return 0;
}
