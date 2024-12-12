#include <iostream>
#include <fstream>
#include <vector>
#include <array>

size_t mapX = 0, mapY = 0;
std::vector<std::string> map;
std::vector<int> regions;
std::vector<std::array<int, 3>> regionsData;

bool isInside(int x, int y);
bool isEqual(int x, int y, const char& a);
size_t getIndex(int x, int y);
bool search(int x, int y, const char& a, int region);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line;
    while (file >> line) {
        map.push_back(line);
        mapY++;
    }
    mapX = line.size();
    regions = std::vector(mapX * mapY, 0);

    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            search(x, y, map[y][x], 0);
        }
    }
    
    // horizontal pass 
    for (int y = 0; y < mapY; y++) {
        bool top_edge = false;
        bool bottom_edge = false;
        for (int x = 0; x < mapX; x++) {
            int region = regions[getIndex(x, y)];
            char a = map[y][x];
            bool new_top_edge = !isEqual(x, y-1, a);
            bool new_bottom_edge = !isEqual(x, y+1, a);
            if ((!isEqual(x-1, y, a) || !top_edge) && new_top_edge) {
                regionsData[region-1][2]++;
            }
            if ((!isEqual(x-1, y, a) || !bottom_edge) && new_bottom_edge) {
                regionsData[region-1][2]++;
            }
            top_edge = new_top_edge;
            bottom_edge = new_bottom_edge;
        }
    }
        
    // vertical pass 
    for (int x = 0; x < mapX; x++) {
        bool left_edge = false;
        bool right_edge = false;
        for (int y = 0; y < mapY; y++) {
            int region = regions[getIndex(x, y)];
            char a = map[y][x];
            bool new_left_edge = !isEqual(x-1, y, a);
            bool new_right_edge = !isEqual(x+1, y, a);
            if ((!isEqual(x, y-1, a) || !left_edge) && new_left_edge) {
                regionsData[region-1][2]++;
            }
            if ((!isEqual(x, y-1, a) ||!right_edge) && new_right_edge) {
                regionsData[region-1][2]++;
            }
            left_edge = new_left_edge;
            right_edge = new_right_edge;
        }
    }

    int sum = 0; 
    for (const auto& [a, f, s]: regionsData) {
        sum += a * s;
    }
    std::cout << sum << std::endl;
}

bool isEqual(int x, int y, const char& a) {
    return isInside(x, y) && map[y][x] == a;
}

bool isInside(int x, int y) {
    return x >= 0 && x < mapX && y >= 0 && y < mapY;
}

size_t getIndex(int x, int y) {
    return y * mapX + x;
}

bool search(int x, int y, const char& a, int region) {
    if (!isInside(x, y)) {
        return false;
    }

    char b = map[y][x];
    if (regions[getIndex(x, y)] != 0 || a != b) {
        return a == b;
    }

    // region is not set and a == b
    if (region == 0) {
        regionsData.push_back({0, 0});
        region = regionsData.size();
    }
    regions[getIndex(x, y)] = region;
    regionsData[region-1][0]++;

    if (!search(x-1, y, a, region)) 
        regionsData[region-1][1]++;
    if (!search(x+1, y, a, region)) 
        regionsData[region-1][1]++;
    if (!search(x, y-1, a, region))
        regionsData[region-1][1]++;
    if (!search(x, y+1, a, region))
        regionsData[region-1][1]++;

    return true;
}
