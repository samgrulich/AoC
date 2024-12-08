#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <numeric>

struct Vec2;

unsigned int maxX, maxY;
std::vector<std::string> lines;
std::map<char, std::vector<Vec2>> positions;

struct Vec2 {
    long x, y;

    int magnitude() const {
        return x * x + y * y;
    }

    Vec2 operator-(const Vec2& other) const {
        return {x - other.x, y - other.y};
    }

    Vec2 operator+(const Vec2& other) const {
        return {x + other.x, y + other.y};
    }

    bool operator<(const Vec2& other) const {
        return y*maxX + x < other.y*maxX + other.x;
    }

    Vec2 operator/(long d) const {
        return {x / d, y / d};
    }
};


bool isInBounds(int x, int y);
bool isInBounds(Vec2 v);
void printLines();

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }

    // positions loading
    std::fstream file(argv[1]);
    std::string line;
    while (file >> line) {
        unsigned int x = 0;
        for (char ch : line) {
            if (ch != '.')
                positions[ch].push_back({x, maxY});
            x++;
        }
        lines.push_back(line);
        maxY++;
        maxX = x;
    }

    // line search
    int antinodes = 0;
    for (auto& [freq, v] : positions) {
        for (int i = 0; i < v.size(); i++) {
            const Vec2& pos0 = v[i];
            for (int j = 0; j < v.size(); j++) {
                if (i == j) 
                    continue;
                const Vec2& pos1 = v[j];
                Vec2 dir = pos1 - pos0;
                Vec2 newPos = pos1;
                Vec2 dirNorm = dir / std::gcd(dir.x, dir.y);
                while (isInBounds(newPos)) {
                    if (lines[newPos.y][newPos.x] != '#') {
                        lines[newPos.y][newPos.x] = '#';
                        antinodes++;
                    }
                    newPos = newPos + dirNorm;
                }
            }
        }
    }

    printLines();

    std::cout << antinodes << std::endl;
}

bool isInBounds(int x, int y) { return 0 <= x && x < maxX && 0 <= y && y < maxY; }
bool isInBounds(Vec2 v) { return isInBounds(v.x, v.y); }
void printLines() {
    for (const std::string& line : lines)
        std::cerr << line << std::endl;
    std::cerr << std::endl;
}
