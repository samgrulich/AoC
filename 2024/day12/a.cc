#include <iostream>
#include <fstream>
#include <vector>
#include <array>

size_t mapX = 0, mapY = 0;
std::vector<std::string> map;
std::vector<int> regions;
std::vector<std::array<int, 2>> regionsData;

bool isInside(int x, int y);
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
    
    int sum = 0; 
    for (auto& [a, b] : regionsData) {
        sum += a * b;
    }

    std::cout << sum << std::endl;
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
