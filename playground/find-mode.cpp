
#include <iostream>

std::vector<int>* find_mode(const int* array, const int length) {
    std::unordered_map<int, int> frequencyMap;
    for (int i = 0; i < length; ++i) {
        const int num = array[i];
        if (frequencyMap.find(num) == frequencyMap.end()) {
            // num does not exist in the frequency map
            frequencyMap[num] = 0;
        }

        frequencyMap[num]++;
    }

    // Find the minium and maximum frequency
    int minFrequency = length, maxFrequency = 0;
    for (const auto& [num, frequency] : frequencyMap) {
        minFrequency = std::min(frequency, minFrequency);
        maxFrequency = std::max(frequency, maxFrequency);
    }

    // Return nullptr if mode does not exist
    if (minFrequency == maxFrequency)
        return nullptr;

    // Extract modes
    const auto modes = new std::vector<int>;
    for (const auto& [num, frequency] : frequencyMap) {
        if (frequency == maxFrequency) {
            modes->push_back(num);
        }
    }

    return modes;
}

int main() {
    constexpr int SIZE = 6;
    const int array[SIZE] = { 1, 2, 3, 3, 4, 4 };

    const auto modes = find_mode(array, SIZE);
    if (modes != nullptr) {
        for (auto it = modes->begin(); it != modes->end(); ++it) {
            std::cout << *it << " " << std::endl;
        }
    }

    delete modes;

    return 0;
}
