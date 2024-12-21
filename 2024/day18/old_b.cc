#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
#include <limits>

#define MAP_SIDE 71

size_t map_side = MAP_SIDE;
size_t map_size = map_side * map_side;

struct Node {
    int x, y;
    std::set<Node*> children;

    bool isEnd();
};

std::vector<int> map;
std::vector<Node> nodes;
std::unordered_map<int, bool> visited;

bool isInside(int x, int y);
int toIndex(int x, int y);
void fromIndex(size_t index, int& x, int& y);

Node* searchMap(int x, int y);
bool search(Node* n);

void printMap();
void printNodesChildren() {
    for (Node n : nodes) {
        printf("%d, %d: ", n.x, n.y);
        for (Node* c : n.children) {
            printf("%d, %d ", c->x, c->y);
        }
        printf("\n");
    }

    for (int y = 0; y < map_side; y++) {
        for (int x = 0; x < map_side; x++) {
            printf("%ld ", nodes[toIndex(x, y)].children.size());
        }
        printf("\n");
    }
}

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
    nodes = std::vector<Node>(map_size, Node());
    int i = 0;
    std::queue<int> bytes;
    while (std::getline(file, line)) {
        int x, y;
        sscanf(line.c_str(), "%d,%d", &x, &y);
        int idx = toIndex(x, y);
        if (i++ < 1024) {
            map[idx] = -1;
        } else {
            bytes.push(idx);
        }
    }

    printf("Input read\n");
    // DFS from top left
    searchMap(0, 0);
    printNodesChildren();
    printf("Map size: %ld\n", map_size);
    printMap();
    
    while (!bytes.empty()) {
        int idx = bytes.front(); bytes.pop();
        int x, y;
        fromIndex(idx, x, y);
        printf("Adding byte %d (%d %d)\n", idx, x, y);
        map[idx] = -1;
        nodes[idx].children.clear();
        printMap();

        // check if there is a path to the end
        if (!search(&nodes[0])) {
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

Node* searchMap(int x, int y) {
    if (!isInside(x, y) || visited[toIndex(x, y)] || map[toIndex(x, y)] == -1){
        return nullptr;
    }
    visited[toIndex(x, y)] = true;
    Node* n = &nodes[toIndex(x, y)];
    n->x = x;
    n->y = y;
    if (n->isEnd()) {
        visited[toIndex(x, y)] = false;
        return n;
    }
    printVisited();

    // search children
    bool found = false;
    Node* child;
    if ((child = searchMap(x + 1, y)) != nullptr) {
        n->children.insert(child);
        found = true;
    }
    if ((child = searchMap(x, y + 1)) != nullptr) {
        n->children.insert(child);
        found = true;
    }
    if ((child = searchMap(x - 1, y)) != nullptr) {
        n->children.insert(child);
        found = true;
    }
    if ((child = searchMap(x, y - 1)) != nullptr) {
        n->children.insert(child);
        found = true;
    }

    // backtrack
    visited[toIndex(x, y)] = false;

    return found ? n : nullptr;
}

bool search(Node* n) {
    if (visited[toIndex(n->x, n->y)] || map[toIndex(n->x, n->y)] == -1)
        return false;
    if (n->isEnd()) 
        return true;
    
    visited[toIndex(n->x, n->y)] = true;

    for (Node* child : n->children) {
        if (search(child)) {
            visited[toIndex(n->x, n->y)] = false;
            return true;
        }
    }

    visited[toIndex(n->x, n->y)] = false;
    return false;
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

bool Node::isEnd() {
    return x == map_side - 1 && y == map_side - 1;
}
