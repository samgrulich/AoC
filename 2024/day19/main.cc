#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> patterns;
std::vector<std::string> combos;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line, pattern;
    std::getline(file, line);
    std::stringstream ss(line);
    while (std::getline(ss, pattern, ',')) {
        if (pattern[0] == ' ') // remove lading spaces
            pattern = pattern.substr(1);
        patterns.push_back(pattern);
    }
    std::getline(file, line);
    while (std::getline(file, line)) {
        combos.push_back(line);
    }
    file.close();

    unsigned long sum = 0;
    for (const std::string& combo : combos) {
        std::vector<unsigned long> perms(combo.size(), 0);
        for (int i = 0; i < combo.size(); i++) {
            for (const std::string& pattern : patterns) {
                // printf("checking: %s %s %s\n", combo.c_str(), pattern.c_str(), combo.substr(0, pattern.size()).c_str());
                if (combo.substr(i, pattern.size()).compare(pattern) == 0) {
                    if (i == 0)
                        perms[i + pattern.size() - 1]++;
                    else
                        perms[i + pattern.size() - 1] += perms[i-1];
                }
            }
        }
        sum += perms[combo.size() - 1];
    }
    std::cout << sum << std::endl;
}

