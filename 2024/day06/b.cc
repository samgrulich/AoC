#include <iostream>
#include <fstream>
#include <vector>

int guardX = 0;
int guardY = 0;
int dX = 0;
int dY = -1;
std::vector<std::string> map;
size_t mapX = 0;
size_t mapY = 0;

bool isInBounds(int x, int y);
int getDirection();
void rotateRight();
void printMap(std::vector<std::string> map);
void printVisited(std::vector<bool[4]> &visited);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }

    // input loading
    std::ifstream file(argv[1]);
    std::string line;
    
    int y = 0;
    while (file >> line) {
        size_t x = 0;
        if (guardX == 0 && (x = line.find("^")) != std::string::npos) {
            guardX = x;
            guardY = y;
        }
        map.push_back(line);
        y++;
    }
    mapX = map[0].size();
    mapY = map.size();

    // algorithm
    int loops = 0;
    for (int y = 0; y < mapY; y++) {
        printf("Row: %d\n", y);
        for (int x = 0; x < mapX; x++) {
            if (map[y][x] == '.') {
                auto new_map = map; 
                std::vector<bool[4]> visited(mapY*mapX);
                new_map[y][x] = 'O';
                int gX = guardX, gY = guardY;
                dX = 0, dY = -1;
                while (isInBounds(gX, gY)) {
                    int x = gX + dX, y = gY + dY;
                    if (!isInBounds(x, y)){
                        break;
                    }
                    
                    visited[gY*mapX+gX][getDirection()] = true;
                    if (visited[y*mapX+x][getDirection()]) {
                        loops++;
                        break;
                    }

                    while (new_map[y][x] == '#' || new_map[y][x] == 'O') {
                        visited[y*mapX+x][getDirection()] = true;
                        rotateRight();
                        x = gX + dX;
                        y = gY + dY;
                        if (!isInBounds(x, y)){
                            break;
                        }
                    }
                    
                    if (new_map[gY][gX] != 'X') {
                        new_map[gY][gX] = 'X';
                    }

                    gX += dX;
                    gY += dY;
                }
                // printf("New map\n");
                // printMap(new_map);
            }
        }
    }

    std::cout << loops << std::endl;
}

bool isInBounds(int x, int y) {
    return x >= 0 && x < mapX && y >= 0 && y < mapY;
}

int getDirection() {
    if (dX == 0 && dY == -1) {
        return 0;
    } else if (dX == 1 && dY == 0) {
        return 1;
    } else if (dX == 0 && dY == 1) {
        return 2;
    } else if (dX == -1 && dY == 0) {
        return 3;
    }
    std::cerr << "Invalid direction" << std::endl;
    exit(1);
}

void rotateRight() {
    if (dX == 0 && dY == -1) {
        dX = 1;
        dY = 0;
    } else if (dX == 1 && dY == 0) {
        dX = 0;
        dY = 1;
    } else if (dX == 0 && dY == 1) {
        dX = -1;
        dY = 0;
    } else if (dX == -1 && dY == 0) {
        dX = 0;
        dY = -1;
    }
}

void printMap(std::vector<std::string> map) {
    for (auto line : map) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}

void printVisited(std::vector<bool[4]>& visited) {
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            for (int i = 0; i < 4; i++) {
                printf("%d ", visited[y*mapX+x][i]);
            }
            printf(": ");
        }
        printf("\n");
    }
}
