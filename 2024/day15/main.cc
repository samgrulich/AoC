#include <iostream>
#include <fstream>
#include <vector>

size_t mapX = 0, mapY = 0;
std::vector<std::string> map;
std::string moves;
int x = 0, y = 0;

bool isInside(const int& x, const int& y);
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
        std::string newLine;
        for (const char& c : line) {
            switch (c) { 
                case '#':
                    newLine += "##";
                    break;
                case '.':
                    newLine += "..";
                    break;
                case 'O':
                    newLine += "[]";
                    break;
                case '@':
                    x = newLine.size();
                    y = mapY;
                    newLine += "@.";
                    break;
            }
        }
        map.push_back(newLine);
        mapY++;
    }
    mapX = map[0].size();

    while (!file.eof() && std::getline(file, line)) {
        moves += line;
    }

    std::cout << mapX << " " << mapY << std::endl;

    for (char m : moves) {
        std::cout << "move: " << m << std::endl;
        switch (m) {
            case '>':
                if (canMove(x+1, y, 1, 0)) {
                    move(x, y, 1, 0);
                    x++;
                }
                break;
            case '<':
                if (canMove(x-1, y, -1, 0)) {
                    move(x, y, -1, 0);
                    x--;
                }
                break;
            case 'v':
                if (canMove(x, y+1, 0, 1)) {
                    move(x, y, 0, 1);
                    y++;
                }
                break;
            case '^':
                if (canMove(x, y-1, 0, -1)) {
                    move(x, y, 0, -1);
                    y--;
                }
                break;
        }
        printMap();
    }

    unsigned long sum = 0;
    int cY = 0, cX = 0;
    for (const std::string &line : map) {
        cX = 0;
        for (const char& c : line) {
            if (c == '[') {
                sum += cY * 100 + cX;
            }
            cX++;
        }
        cY++;
    }
    std::cout << sum << std::endl;
}

bool isInside(const int& x, const int& y) {
    return x >= 0 && x < mapX && y >= 0 && y < mapY;
}

bool canMove(int x, int y, int dx, int dy) {
    if (!isInside(x, y) || map[y][x] == '#')
        return false;

    if (map[y][x] == '.')
        return true;

    if (map[y][x] == '[') {
        if (dx == 1) {
            return canMove(x+2, y+dy, dx, dy); 
        }
        return canMove(x+1+dx, y+dy, dx, dy) && canMove(x+dx, y+dy, dx, dy);
    }
    if (map[y][x] == ']') {
        if (dx == -1) {
            return canMove(x-2, y+dy, dx, dy); 
        }
        return canMove(x+dx, y+dy, dx, dy) && canMove(x-1+dx, y+dy, dx, dy);
    }

    return canMove(x+dx, y+dy, dx, dy);
}

void move(int x, int y, int dx, int dy) {
    char c = map[y][x];
    if (map[y+dy][x+dx] == '[') {
        move(x+1+dx, y+dy, dx, dy);
        move(x+dx, y+dy, dx, dy);
    }
    if (map[y+dy][x+dx] == ']') {
        move(x-1+dx, y+dy, dx, dy);
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
