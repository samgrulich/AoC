#include <iostream>
#include <vector>

std::vector<int> idMap;
std::vector<int> blockSize;
std::vector<int> blockStart;
std::vector<int> fileSize;
std::vector<int> fileStart;

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
        int val = c - '0';
        if (id % 2 == 0) {
            fileSize.push_back(val);
            fileStart.push_back(idMap.size());
        } else {
            blockSize.push_back(val);
            blockStart.push_back(idMap.size());
        }
        for (int i = 0; i < val; i++) {
            idMap.push_back(id % 2 == 0 ? id / 2 : -1);
        }
        id++;
    }
    
    // printMap();
    // for (int i = 0; i < blockSize.size(); i++) {
    //     printf("Block %d: %d, %d\n", i, blockSize[i], blockStart[i]);
    // }

    for (int i = fileSize.size() - 1; i >= 0; i--) {
        for (int j = 0; j < blockSize.size() && j < i; j++) {
            const int& fsize = fileSize[i];
                  int& bsize = blockSize[j];
            if (bsize >= fsize) {
                // printf("File %d fits in %d, file(%d, %d), free(%d, %d)\n", i, j, fileStart[i], fsize, blockStart[j], bsize);
                for (int k = 0; k < fsize; k++) { // copy the file
                    idMap[fileStart[i]  + k] = -1;
                    idMap[blockStart[j] + k] = i;
                }
                bsize -= fsize;
                blockStart[j] += fsize;
                // printMap();
                break;
            }
        }
    }
    
    printMap();

    long checksum = 0;
    for (int i = 0; i < idMap.size(); i++) {
        if (idMap[i] == -1) 
            continue;
        checksum += i * idMap[i];
    }

    std::cout << checksum << std::endl;
}
