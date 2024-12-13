#include <cmath>
#include <iostream>
#include <fstream>

#define A_PRIZE 3
#define B_PRIZE 1
#define C 10000000000000 

struct Vec2 {
    long long x;
    long long y;

    void operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
    }

    Vec2 operator+(const Vec2& other) {
        return {x + other.x, y + other.y};
    }

    Vec2 operator*(long long scalar) {
        return {x * scalar, y * scalar};
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string lineA, lineB, linePrize, throwaway;
    unsigned long long sum = 0;
    Vec2 c = {C, C};
    while (getline(file, lineA) && getline(file, lineB) && getline(file, linePrize) && (getline(file, throwaway) || file.eof())) {
        Vec2 a, b, p;
        sscanf(lineA.c_str(), "Button A: X+%lld, Y+%lld", &a.x, &a.y);
        sscanf(lineB.c_str(), "Button B: X+%lld, Y+%lld", &b.x, &b.y);
        sscanf(linePrize.c_str(), "Prize: X=%lld, Y=%lld", &p.x, &p.y);
        p += c;
        double A = (double)(p.y * b.x - b.y * p.x) / (a.y * b.x - b.y * a.x);
        double B = (double)(p.x - a.x * A) / b.x;
        if (A == (unsigned long long)A && B == (unsigned long long)B) {
            sum += A * A_PRIZE + B * B_PRIZE;
        } 
    }
    std::cout << sum << std::endl;
}

