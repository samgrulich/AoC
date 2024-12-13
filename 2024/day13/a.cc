#include <iostream>
#include <fstream>

#define A_PRIZE 3
#define B_PRIZE 1

struct Vec2 {
    int x;
    int y;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string lineA, lineB, linePrize, throwaway;
    int i = 0;
    int sum = 0;
    while (getline(file, lineA) && getline(file, lineB) && getline(file, linePrize) && (getline(file, throwaway) || file.eof())) {
        Vec2 a, b, p;
        sscanf(lineA.c_str(), "Button A: X+%d, Y+%d", &a.x, &a.y);
        sscanf(lineB.c_str(), "Button B: X+%d, Y+%d", &b.x, &b.y);
        sscanf(linePrize.c_str(), "Prize: X=%d, Y=%d", &p.x, &p.y);
        float A = (float)(p.y * b.x - b.y * p.x) / (a.y * b.x - b.y * a.x);
        float B = (float)(p.x - a.x * A) / b.x;
        if (A == (int)A && B == (int)B) {
            sum += A * A_PRIZE + B * B_PRIZE;
        } 
    }
    std::cout << sum << std::endl;
}

