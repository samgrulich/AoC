#include <iostream>
#include <vector>

int sign(int a) {
    return (a > 0) - (a < 0);
}

int main() {
    int sum = 0;

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

        int sgn = sign(line[1] - line[0]);
        bool isSafe = true;
        printf("line: ");
        for (int i = 1; i < line.size(); i++) {
            int d = line[i] - line[i - 1];
            // printf(" %d", std::abs(d));
            if (sign(d) != sgn || std::abs(d) < 1 || std::abs(d) > 3) {
                isSafe = false;
                break;
            }
        }
        printf(" %d\n", isSafe);

        if (isSafe)
            sum++;
    } 

    std::cout << sum << std::endl;
}
