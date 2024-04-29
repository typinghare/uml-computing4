#include <functional>
#include <iostream>

template <typename X>
X fun(X x) {
    return x;
}

auto g1 = fun<std::function<int(int)>>;
auto g2 = fun<int>;

int main() {
    std::cout << (*g1)(g2)(21) << std::endl;
    std::cout << fun(fun<int>)(21) << std::endl;

    return 0;
}
