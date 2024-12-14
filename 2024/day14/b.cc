#include <iostream>
#include <limits>
#include <vector>

#define MAX_ROBOTS 500
#define MAX_TIME 100000
#define THRESHOLD 40

int mod(int a, int b);
void printMap(int len);
bool isInside(int x, int y);

struct Vec2 {
    long x, y;

    size_t toIndex(int width) const {
        return y * width + x;
    }

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
std::vector<long> densities;
std::vector<int> map;


int main() {
    std::cin >> max.x >> max.y;
    int i = 0;
    do {
        std::string line;
        std::getline(std::cin, line);
        if (line.size() == 0) {
            continue;
        }
        sscanf(line.c_str(), "p=%ld,%ld v=%ld,%ld\n", &(positions[i].x), &(positions[i].y), &(velocities[i].x), &(velocities[i].y));
        i++;
    } while (!std::cin.eof());
    size_t len = i;
    
    for (int t = 0; t < MAX_TIME; t++) {
        if (t % 10000 == 0) {
            std::cerr << "Time: " << t << std::endl;
        }
        map = std::vector<int>(max.x * max.y, 0);
        densities = std::vector<long>((max.x/10+1) * (max.y/10+1), 0);
        for (int r = 0; r < len; r++) {
            Vec2 pos = (velocities[r] + positions[r]) % max;
            positions[r] = pos;
            densities[Vec2{pos.x/10, pos.y/10}.toIndex(max.x/10)]++;
            int c = ++map[pos.toIndex(max.x)];
        }
        long min = std::numeric_limits<long>::max();
        long max = 0;
        for (auto density : densities) {
            min = std::min(density, min);
            max = std::max(density, max);
            if (max - min > THRESHOLD) {
                std::cerr << "Time: " << t+1 << ", " << density << std::endl;
                std::cout << "Time: " << t+1 << '\n';
                printMap(len);
                break;
            }
        }
    }
    std::cout << std::flush;
}


int mod(int a, int b) {
    return (a % b + b) % b;
}

bool isInside(int x, int y) {
    return x >= 0 && x < max.x && y >= 0 && y < max.y;
}

void printMap(int len) {
    for (int y = 0; y < max.y; y++) {
        for (int x = 0; x < max.x; x++) {
            if (map[Vec2{x, y}.toIndex(max.x)]) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << '\n';
    }
}

