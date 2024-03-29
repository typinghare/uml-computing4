#include <iostream>

using namespace std;

template <int n>
struct funStruct {
    static const int val = 2 * funStruct<n - 1>::val;
};

template <>
struct funStruct<0> {
    static constexpr int val = 1;
};

int main() {
    constexpr auto M = 10;
    cout << funStruct<M>::val << endl;  // 1024

    return 0;
}
