#include <iostream>

#define MAX_ROBOTS 500
#define MAX_TIME 100

int mod(int a, int b);
void addToQuadrant(int x, int y);
void printMap(int len);

struct Vec2 {
    int x, y;

    Vec2 operator+(const Vec2& other) const {
        return {x + other.x, y + other.y};
    }

    Vec2 operator*(const int& scalar) const {
        return {x * scalar, y * scalar};
    }

    Vec2 operator/(const int& scalar) const {
        return {x / scalar, y / scalar};
    }

    Vec2 operator%(const Vec2& other) const {
        return {mod(x, other.x), mod(y, other.y)};
    }
};


Vec2 max;
Vec2 positions[MAX_ROBOTS];
Vec2 velocities[MAX_ROBOTS];
unsigned int sums[4];


int main() {
    std::cin >> max.x >> max.y;
    int i = 0;
    do {
        std::string line;
        std::getline(std::cin, line);
        if (line.size() == 0) {
            continue;
        }
        sscanf(line.c_str(), "p=%d,%d v=%d,%d\n", &(positions[i].x), &(positions[i].y), &(velocities[i].x), &(velocities[i].y));
        i++;
    } while (!std::cin.eof());
    int len = i;
    
    for (int r = 0; r < len; r++) {
        Vec2 pos = (velocities[r] * MAX_TIME + positions[r]) % max;
        positions[r] = pos;
        addToQuadrant(pos.x, pos.y);
    }

    int sigma = 1;
    for (int i = 0; i < 4; i++) {
        sigma *= sums[i];
    }
    std::cout << sigma << std::endl;
}


int mod(int a, int b) {
    return (a % b + b) % b;
}

void printMap(int len) {
    for (int y = 0; y < max.y; y++) {
        for (int x = 0; x < max.x; x++) {
            int found = 0;
            for (int r = 0; r < len; r++) {
                if (positions[r].x == x && positions[r].y == y) {
                    found++;
                }
            }
            if (found) {
                std::cout << found << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

void addToQuadrant(int x, int y) {
    static Vec2 half = max / 2;
    if (x == half.x || y == half.y)
        return;
    int quad = (x > half.x) + 2 * (y > half.y);
    sums[quad]++;
}
