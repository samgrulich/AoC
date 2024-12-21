#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> patterns;
std::vector<std::string> combos;

bool match(const std::string combo);

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

    int sum = 0;
    for (const std::string& combo : combos) {
        if (match(combo)) {
            sum++;
        } 
    }
    std::cout << sum << std::endl;
}

bool match(const std::string combo) {
    if (combo.size() == 0)
        return true;
    for (const std::string& pattern : patterns) {
        // printf("checking: %s %s %s\n", combo.c_str(), pattern.c_str(), combo.substr(0, pattern.size()).c_str());
        if (combo.substr(0, pattern.size()).compare(pattern) == 0) {
            if (match(combo.substr(pattern.size()))) {
                return true;
            }
        }
    }
    return false;
}
