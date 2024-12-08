#include <iostream>
#include <vector>

int sign(int a) {
    return (a > 0) - (a < 0);
}

bool isValid(int d, int sgn) {
    return sign(d) == sgn && std::abs(d) >= 1 && std::abs(d) <= 3;
}

bool isSafe(std::vector<int> line) {
    int sgn = sign(line[1] - line[0]);
    for (int i = 1; i < line.size(); i++) {
        int d = line[i] - line[i - 1];
        if (!isValid(d, sgn))
            return false;
    }
    return true;
}

bool isSafeP2(std::vector<int> line) {
    if (isSafe(line)) return true;

    for (int i = 0; i < line.size(); i++) {
        std::vector<int> line2(line.begin(), line.end());
        line2.erase(line2.begin() + i);
        if (isSafe(line2)) return true;
    }

    return false;
}

int main() {
    int sum = 0;
    int l = 0;

    while (true) {
        std::vector<int> line;
        line.reserve(10);

        do {
            int a;
            std::cin >> a;
            line.push_back(a);
        } while (std::cin.get() != '\n' && !std::cin.eof()); // load line
        if (std::cin.eof())
            break;
        // printf("loaded %ld elements\n", line.size());
        // printf("loaded line: ");
        // for (int i = 0; i < line.size(); i++)
        //     printf(" %d", line[i]);
        // printf("\n");

        // int err = 0;
        // printf("line %d: ", l);
        // printf(" %d\n", isSafe);

        if (isSafeP2(line))
            sum++;
        l++;
    } 

    std::cout << sum << std::endl;
}
