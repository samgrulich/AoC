#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include <unordered_map>

#define MAX_WIDTH 141
#define MAX_HEIGHT 141
#define MAX_SIZE MAX_WIDTH * MAX_HEIGHT
#define WALL '#'
#define END 'E'

#define THRESHOLD 20

size_t w, h;
std::string map;

size_t visited_sum = 0;
std::unordered_map<size_t, bool> visited;

size_t toDirection(long dx, long dy);
size_t toIndex(size_t x, size_t y);
void fromDirection(size_t dir, long& out_dx, long& out_dy);

bool move(size_t& out_x, size_t& out_y, const long& dx, const long& dy, size_t& out_score);
void rotate(long& out_dx, long& out_dy, size_t& out_score, bool ccw = false);
void clearVisited(const size_t& out_x, const size_t& out_y);
size_t search(size_t x, size_t y, long dx, long dy, size_t score, size_t apex = std::numeric_limits<size_t>::max());

void printVisited();

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

    visited.reserve(w*h);
    size_t start_x = 1, start_y = h-2;
    visited[toIndex(start_x, start_y)] = true;
    size_t score = search(start_x, start_y, 1, 0, 0);
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

bool move(size_t& out_x, size_t& out_y, const long& dx, const long& dy, size_t& out_score) {
    size_t x = out_x + dx;
    size_t y = out_y + dy;
    if (map[toIndex(x, y)] == WALL || visited[toIndex(x, y)]) {
        return false;
    }
    out_x = x;
    out_y = y;
    out_score++;
    visited[toIndex(x, y)] = true;
    return true;
}

void rotate(long& out_dx, long& out_dy, size_t& out_score, bool ccw) {
    size_t dx = out_dx;
    size_t dy = out_dy;
    size_t dir = toDirection(dx, dy);
    
    if (ccw) {
        dir = (dir + 3) % 4;
    } else {
        dir = (dir + 1) % 4;
    }
    
    out_score += 1000;
    fromDirection(dir, out_dx, out_dy);
}

void clearVisited(const size_t& out_x, const size_t& out_y) {
    visited[toIndex(out_x, out_y)] = false;
}

size_t search(size_t x, size_t y, long dx, long dy, size_t score, long apex) {
    if (map[toIndex(x, y)] == END) {
        printVisited();
        std::cout << "Score: " << score << std::endl;
        return score;
    }
    long distFromEnd = std::powl(((long)y - 1), 2) + std::powl((w - (long)x), 2);
    printf("Distance from end: %ld %ld\n", distFromEnd, apex);
    if (distFromEnd < apex) {
        apex = distFromEnd;
    } else if (distFromEnd > apex + THRESHOLD) {
        return std::numeric_limits<size_t>::max();
    }
    size_t best = std::numeric_limits<size_t>::max();
    bool moved = false;
    if (visited_sum > 500)
        printVisited();
    for (int i = 0; i < 3; i++) {
        if (move(x, y, dx, dy, score)) {
            visited_sum++;
            size_t new_score = search(x, y, dx, dy, score);
            if (new_score < best) {
                best = new_score;
            }
            clearVisited(x, y);
            visited_sum--;
            x -= dx; y -= dy;
            moved = true;
            score--;
        }
        if (i == 0) {
            rotate(dx, dy, score);
        } else if (i == 1) {
            rotate(dx, dy, score, true);
            rotate(dx, dy, score, true);
            score -= 2*1000;
        }
    }
    return best;
}

void printVisited() {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            std::cout << (visited[toIndex(x, y)] ? 'X' : map[toIndex(x, y)]);
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}
