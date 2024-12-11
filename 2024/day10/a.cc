#include <iostream>
#include <fstream>
#include <vector>

size_t R = 0, C = 0;
std::string grid;

bool isInBounds(int x, int y) { return x >= 0 && x < C && y >= 0 && y < R; }
int getIndex(int x, int y) { return y * C + x; }
void getXY(int index, int& out_x, int& out_y) { out_x = index % C; out_y = index / C; }

bool isValid(char val, int x, int y) { return isInBounds(x, y) && grid[getIndex(x, y)] - val == 1; }
int search(int x, int y, char prev, std::vector<bool>& visited) {
    int idx = getIndex(x, y), val;
    if (!isInBounds(x, y) || (val = grid[idx]) - prev != 1) 
        return 0;
    if (val == '9' && !visited[idx]) {
        visited[idx] = true;
        return 1;
    }
    return search(x-1, y  , val, visited) +
           search(x+1, y  , val, visited) +
           search(x  , y-1, val, visited) +
           search(x  , y+1, val, visited);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line;
    while(file >> line) {
        grid += line;
        R++;
    }
    C = line.size();

    int sum = 0;
    for (int i = 0; i < grid.size(); i++) {
        if (grid[i] == '0') {
            int x, y; getXY(i, x, y);
            std::vector<bool> visited(grid.size(), false);
            sum += search(x, y, '0'-1, visited);
        }
    }

    std::cout << sum << std::endl;
}
