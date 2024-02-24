
template <class T>
void swap(T& var1, T& var2) noexcept {
    T temp = var1;
    var1 = var2;
    var2 = temp;
}

int main() { return 0; }