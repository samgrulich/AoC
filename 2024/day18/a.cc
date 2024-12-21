#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <limits>

#define MAP_SIDE 71

size_t map_side = MAP_SIDE;
size_t map_size = map_side * map_side;

struct Step {
    int x, y;
    size_t steps;
};

std::vector<int> map;
std::queue<Step> q;

bool isInside(int x, int y);
int toIndex(int x, int y);
void fromIndex(size_t index, int& x, int& y);
void printMap();

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input file> <map_side>" << std::endl;
        return 1;
    }

    if (argc == 3) {
        map_side = std::stoi(argv[2]);
        map_size = map_side * map_side;
    }
    std::ifstream file(argv[1]);
    std::string line;
    map = std::vector<int>(map_size, std::numeric_limits<int>::max());
    int i = 0;
    while (std::getline(file, line)) {
        int x, y;
        sscanf(line.c_str(), "%d,%d", &x, &y);
        if (i++ < 1024) {
            map[toIndex(x, y)] = -1;
        }
    }

    // BFS from top left
    q.push({0, 0, 0});
    while (!q.empty()) {
        Step step = q.front(); q.pop();
        int x = step.x, y = step.y, idx = toIndex(step.x, step.y);
        if (!isInside(step.x, step.y) || map[idx] == -1 || map[idx] <= step.steps) {
            continue;
        }
        map[idx] = step.steps;
        q.push({x + 1, y, step.steps + 1});
        q.push({x - 1, y, step.steps + 1});
        q.push({x, y + 1, step.steps + 1});
        q.push({x, y - 1, step.steps + 1});
    }
    
    // printMap();

    std::cout << map[toIndex(map_side - 1, map_side - 1)] << std::endl;
}

bool isInside(int x, int y) {
    return x >= 0 && x < map_side && y >= 0 && y < map_side;
}

void fromIndex(size_t index, int& x, int& y) {
    x = index % map_side;
    y = index / map_side;
}

int toIndex(int x, int y) {
    return x + y * map_side;
}

void printMap() {
    for (int y = 0; y < map.size()/map_side; y++) {
        for (int x = 0; x < map_side; x++) {
            if (map[toIndex(x, y)] == -1) {
                std::cout << "# " << " ";
            } else {
                if (map[toIndex(x, y)] == std::numeric_limits<int>::max()) {
                    std::cout << ". " << " ";
                } else {
                    std::cout << map[toIndex(x, y)] << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}
