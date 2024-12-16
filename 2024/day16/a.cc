#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include <queue>
#include <unordered_map>

#define MAX_WIDTH 141
#define MAX_HEIGHT 141
#define MAX_SIZE MAX_WIDTH * MAX_HEIGHT
#define WALL '#'
#define END 'E'

struct Move {
    size_t x, y;
    long dx, dy;
    size_t score;
    
    Move move() const;
    Move rotate(bool ccw = false) const;
};

size_t w, h;
std::string map;

std::unordered_map<size_t, long> scores;
std::queue<Move> q;

size_t toDirection(long dx, long dy);
size_t toIndex(size_t x, size_t y);
void fromDirection(size_t dir, long& out_dx, long& out_dy);

long getScore(size_t x, size_t y);
bool isWall(size_t x, size_t y);

void printScores();

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    std::string line;
    map.reserve(MAX_SIZE);
    while (!file.eof() && std::getline(file, line)) {
        map += line;
        w = line.size();
    }
    h = map.size() / w;
    printf("Map size: %lu %lu\n", h, w);

    scores.reserve(w*h);
    size_t start_x = 1, start_y = h - 2;
    q.push({start_x+1, start_y  , 1,  0, 1});
    q.push({start_x,   start_y-1, 0, -1, 1001});
    while (!q.empty()) {
        Move m = q.front();
        q.pop();
        if (isWall(m.x, m.y) || getScore(m.x, m.y) <= m.score) {
            continue;
        }
        scores[toIndex(m.x, m.y)] = m.score;
        q.push(m.move());
        q.push(m.rotate().move());
        q.push(m.rotate(true).move());
    }
    printScores();
    long score = scores[toIndex(w-2, 1)];
    std::cout << score << std::endl;
}

size_t toDirection(long dx, long dy) {
    if (dx == 1 && dy == 0) {
        return 0;
    } else if (dx == 0 && dy == 1) {
        return 1;
    } else if (dx == -1 && dy == 0) {
        return 2;
    } else if (dx == 0 && dy == -1) {
        return 3;
    }
    std::cerr << "Invalid direction: " << dx << ", " << dy << std::endl;
    exit(1);
}

size_t toIndex(size_t x, size_t y) {
    return x + y * w;
}

void fromDirection(size_t dir, long& out_dx, long& out_dy) {
    switch (dir) {
        case 0:
            out_dx = 1;
            out_dy = 0;
            break;
        case 1:
            out_dx = 0;
            out_dy = 1;
            break;
        case 2:
            out_dx = -1;
            out_dy = 0;
            break;
        case 3:
            out_dx = 0;
            out_dy = -1;
            break;
        default:
            std::cerr << "Invalid direction: " << dir << std::endl;
            exit(1);
    }
}

long getScore(size_t x, size_t y) {
    auto it = scores.find(toIndex(x, y));
    if (it == scores.end()) {
        return std::numeric_limits<long>::max();
    }
    return it->second;
}

bool isWall(size_t x, size_t y) {
    return map[toIndex(x, y)] == WALL;
}

Move Move::move() const {
    return {x+dx, y+dy, dx, dy, score + 1};
}

Move Move::rotate(bool ccw) const {
    Move res = {x, y, dx, dy, score + 1000};
    size_t dir = toDirection(dx, dy);
    
    if (ccw) {
        dir = (dir + 3) % 4;
    } else {
        dir = (dir + 1) % 4;
    }
    
    fromDirection(dir, res.dx, res.dy);
    return res;
}

void printScores() {
    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            long score = getScore(x, y);
            if (score == std::numeric_limits<long>::max()) {
                printf("####");
            } else {
                printf("%4ld", score);
            }
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}
