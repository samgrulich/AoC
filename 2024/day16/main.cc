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
    long score;
    
    Move move() const;
    Move rotate(bool ccw = false) const;
};

struct TileInfo {
    long score;
    long prev = -1;
    long dx, dy;
};

size_t w, h;
std::string map;

// bfs
std::unordered_map<size_t, TileInfo> scores;
std::queue<Move> q;

// dfs for collecting the tiles
std::vector<bool> revisited;
size_t tiles = 0;

size_t toDirection(long dx, long dy);
size_t toIndex(size_t x, size_t y);
void fromIndex(size_t idx, size_t& out_x, size_t& out_y);
void fromDirection(size_t dir, long& out_dx, long& out_dy);

long getScore(size_t x, size_t y);
bool isWall(size_t x, size_t y);

bool search(size_t idx, long score, bool rotatiton = false);

void printScores();
void printPrevs();
void printRepeated();

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
    revisited.resize(w*h, false);
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
        scores[toIndex(m.x, m.y)] = {m.score, (long)toIndex(m.x - m.dx, m.y - m.dy), -m.dx, -m.dy};
        if (map[toIndex(m.x, m.y)] == END) {
            continue;
        }
        q.push(m.move());
        q.push(m.rotate().move());
        q.push(m.rotate(true).move());
    }
    printScores();
    printPrevs();
    long score = scores[toIndex(w-2, 1)].score;
    printf("Score: %ld\n", score);
    search(toIndex(w-2, 1), score);
    printRepeated();
    std::cout << tiles << std::endl;
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
    return it->second.score;
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

void fromIndex(size_t idx, size_t& out_x, size_t& out_y) {
    out_x = idx % w;
    out_y = idx / w;
}

bool search(size_t idx, long score, bool rotatiton) {
    static int i = 0;
    static bool watching = false;
    size_t x, y;
    fromIndex(idx, x, y);
    // if (rotatiton) {
    //     printf("search(r) %d: %lu (%lu %lu) %ld (rotation)\n", i++, idx, x, y, score);
    // } else {
    //     printf("search    %d: %lu (%lu %lu) %ld\n", i++, idx, x, y, score);
    // }
    if (scores[idx].score != score || map[idx] == WALL) {
        // printf("Invalid score: %ld\n", scores[idx].score);
        return false;
    }
    TileInfo tile = scores[idx];
    if (idx == toIndex(132-1, 131-1)) {
        watching = true;
    }
    if (tile.prev == -1) {
        return idx == toIndex(1, h-2);
    }
    long prevScore = scores[tile.prev].score;
    bool res = false;
    res |= search(tile.prev, prevScore);
    if (map[idx] == END) {
        return true;
    }
    Move lrm = Move{x, y, tile.dx, tile.dy, 0}.rotate().move();
    Move rrm = Move{x, y, tile.dx, tile.dy, 0}.rotate(true).move();
    res |= search(toIndex(lrm.x, lrm.y), prevScore + 1000, true);
    res |= search(toIndex(rrm.x, rrm.y), prevScore + 1000, true);
    if (res) {
        revisited[idx] = true;
        tiles++;
    }
    return res;
}

void printScores() {
    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            long score = getScore(x, y);
            if (score == std::numeric_limits<long>::max()) {
                printf("######");
            } else {
                printf("%6ld", score);
            }
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}

void printPrevs() {
    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            long prev = scores[toIndex(x, y)].prev;
            if (prev == -1) {
                printf("#######");
            } else {
                // size_t px, py;
                // fromIndex(prev, px, py);
                // printf("(%2ld,%2ld)", px, py);
                printf("%7ld", prev);
            }
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}

void printRepeated() {
    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            if (revisited[toIndex(x, y)]) {
                printf("O");
            } else {
                printf("%c", map[toIndex(x, y)]);
            }
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}
