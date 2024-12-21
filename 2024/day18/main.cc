#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>

#define MAP_SIDE 71

size_t map_side = MAP_SIDE;
size_t map_size = map_side * map_side;

std::vector<int> map;
std::unordered_map<int, bool> visited;

bool isInside(int x, int y);
int toIndex(int x, int y);
void fromIndex(size_t index, int& x, int& y);

bool searchMap(int x, int y);

void printMap();
void printVisited() {
    for (int y = 0; y < map_side; y++) {
        for (int x = 0; x < map_side; x++) {
            printf("%d ", visited[toIndex(x, y)]);
        }
        printf("\n");
    }
}

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
    std::queue<int> bytes;
    while (std::getline(file, line)) {
        int x, y;
        sscanf(line.c_str(), "%d,%d", &x, &y);
        int idx = toIndex(x, y);
        if (i++ < 12) {
            map[idx] = -1;
        } else {
            bytes.push(idx);
        }
    }

    printf("Input read\n");
    // DFS from top left
    
    while (!bytes.empty()) {
        int idx = bytes.front(); bytes.pop();
        int x, y;
        fromIndex(idx, x, y);
        printf("Adding byte %d (%d %d)\n", idx, x, y);
        map[idx] = -1;
        // printMap();

        // check if there is a path to the end
        if (!searchMap(0, 0)) {
            int x, y;
            fromIndex(idx, x, y);
            std::cout << x << "," << y << std::endl;
            break;
        } 
    }
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

bool searchMap(int x, int y) {
    if (!isInside(x, y) || visited[toIndex(x, y)] || map[toIndex(x, y)] == -1){
        return false;
    }
    visited[toIndex(x, y)] = true;
    if (x == map_side - 1 && y == map_side - 1) {
        visited[toIndex(x, y)] = false;
        return true;
    }

    bool found = searchMap(x + 1, y) || searchMap(x, y + 1) || searchMap(x - 1, y) || searchMap(x, y - 1);

    // backtrack
    visited[toIndex(x, y)] = false;

    return found;
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

