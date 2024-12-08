#include <algorithm>
#include <iostream>
#include <array>
#include <map>

#define N 1000

// First part 

// std::array<int, N> arr1;
// std::array<int, N> arr2;
//
// int main() {
//     int j = 0;
//     while (!std::cin.eof()) {
//         std::cin >> arr1[j] >> arr2[j];
//         j++;
//     }
//
//     std::sort(arr1.begin(), arr1.end());
//     std::sort(arr2.begin(), arr2.end());
//
//     int sum = 0;
//     for (int i = 0; i < N; i++) {
//         sum += std::abs(arr1[i] - arr2[i]);
//     }
//
//     std::cout << sum << std::endl;
// }

std::array<int, N> arr1;
std::map<int, int> counts;

int main() {
    int j = 0;
    while (true) {
        int b;
        std::cin >> arr1[j++] >> b;
        if (std::cin.eof())
            break;
        // printf("%d loaded %d, b: %d\n", std::cin.eof(), arr1[j], b);
        counts[b]++;
    }

    int sum = 0;
    for (int i = 0; i < N; i++) {
        int a = arr1[i];
        // printf("a: %d, counts[a]: %d, score: %d\n", a, counts[a], a*counts[a]);
        sum += a*counts[a];
    }
    std::cout << sum << std::endl;
}

