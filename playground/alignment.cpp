#include <iostream>

// // 28
// struct A {
//     double b;       // 8
//     char a[5];      // 8
//     int c[2];       // 8
// };
//
// struct B {
//     A a[2]; // 56
//     int b;
// };

#define unit bool

auto a = 14;
int* x = &a; // let x = ref 64 in

class Example {
 public:
    int* cell = x;

    int inc(unit u) { return *x = *x + 1; }
};

int main() {
    Example example;
    example.inc(true);

    std::cout << *example.cell;

    return 0;
}
