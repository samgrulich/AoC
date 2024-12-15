#include <iostream>
#include <fstream>
#include <vector>

size_t mapX = 0, mapY = 0;
std::vector<std::string> map;
std::string moves;
int x = 0, y = 0;

bool isInside(int x, int y);
bool canMove(int x, int y, int dx, int dy);
void move(int x, int y, int dx, int dy);
void printMap();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line;
    while (std::getline(file, line) && !line.empty()) {
        map.push_back(line);
        if (y == 0 && (x = line.find('@')) != std::string::npos) {
            y = mapY;
        }
        mapY++;
    }
    mapX = map[0].size();

    while (!file.eof() && std::getline(file, line)) {
        moves += line;
    }

    for (char m : moves) {
        switch (m) {
            case '>':
                if (canMove(x, y, 1, 0)) {
                    move(x, y, 1, 0);
                    x++;
                }
                break;
            case '<':
                if (canMove(x, y, -1, 0)) {
                    move(x, y, -1, 0);
                    x--;
                }
                break;
            case 'v':
                if (canMove(x, y, 0, 1)) {
                    move(x, y, 0, 1);
                    y++;
                }
                break;
            case '^':
                if (canMove(x, y, 0, -1)) {
                    move(x, y, 0, -1);
                    y--;
                }
                break;
        }
    }

    unsigned long sum = 0;
    int cY = 0, cX = 0;
    for (std::string &line : map) {
        cX = 0;
        for (char c : line) {
            if (c == 'O') {
                sum += cY * 100 + cX;
            }
            cX++;
        }
        cY++;
    }
    std::cout << sum << std::endl;
}

bool isInside(int x, int y) {
    return x >= 0 && x < mapX && y >= 0 && y < mapY;
}

bool canMove(int x, int y, int dx, int dy) {
    if (!isInside(x + dx, y + dy) || map[y+dy][x+dx] == '#')
        return false;

    if (map[y+dy][x+dx] == '.')
        return true;

    return canMove(x+dx, y+dy, dx, dy);
}

void move(int x, int y, int dx, int dy) {
    char c = map[y][x];
    if (map[y+dy][x+dx] == 'O') {
        move(x+dx, y+dy, dx, dy);
    }
    map[y+dy][x+dx] = c;
    map[y][x] = '.';
}

void printMap() {
    for (std::string &line : map) {
        std::cout << line << '\n';
    }
    std::cout << std::endl;
}
