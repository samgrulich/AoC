#include <algorithm>
#include <iostream>
#include <array>

#define N 1000

std::array<int, N> arr1;
std::array<int, N> arr2;

int main() {
    int j = 0;
    while (!std::cin.eof()) {
        std::cin >> arr1[j] >> arr2[j];
        j++;
    }

    std::sort(arr1.begin(), arr1.end());
    std::sort(arr2.begin(), arr2.end());

    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += std::abs(arr1[i] - arr2[i]);
    }

    std::cout << sum << std::endl;
}
