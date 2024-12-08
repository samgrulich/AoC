#include <iostream>
#include <array>
#include <map>

#define N 1000

std::array<int, N> arr1;
std::map<int, int> counts;

int main() {
    int j = 0;
    while (true) {
        int b;
        std::cin >> arr1[j++] >> b;
        if (std::cin.eof())
            break;
        counts[b]++;
    }

    int sum = 0;
    for (int i = 0; i < N; i++) {
        int a = arr1[i];
        sum += a*counts[a];
    }
    std::cout << sum << std::endl;
}

