#include <iostream>
#include <vector>

std::vector<int> idMap;

void printMap() {
    for (int i = 0; i < idMap.size(); i++) {
        if (idMap[i] == -1) 
            std::cerr << ".";
        else 
            std::cerr << idMap[i];
    }
    std::cerr << std::endl;
}

int main() {
    int id = 0;
    while (!std::cin.eof()) {
        char c = std::cin.get();
        if (c == 10) {
            break;
        }
        for (int i = 0; i < c-'0'; i++) {
            idMap.push_back(id % 2 == 0 ? id / 2 : -1);
        }
        id++;
    }
    
    auto start = idMap.begin();
    auto end = idMap.end()-1;

    // printMap();

    while (true) {
        while (*start != -1) {
            start++;
        }
        while(*end == -1) {
            end--;
        }
        if (start >= end) {
            break;
        }
        *start = *end;
        *end = -1;
        start++; end--;
    }
    
    // printMap();

    long checksum = 0;
    for (int i = 0; i < idMap.size(); i++) {
        if (idMap[i] == -1) 
            continue;
        checksum += i * idMap[i];
    }

    std::cout << checksum << std::endl;
}
