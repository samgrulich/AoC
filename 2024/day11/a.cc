#include <cstdio>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <unordered_map>

#define STEPS 1

std::unordered_map<unsigned long, unsigned int> nums;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    unsigned long num;
    while (file >> num) {
        nums[num]++;
    }

    int steps = argc == 2 ? STEPS : std::stoi(argv[2]);

    for (int i = 0; i < steps; i++) {
        std::unordered_map<unsigned long, unsigned int> next;
        for (auto& [k, v] : nums) {
            std::string s;
            if (k == 0) {
                next[1] += v;
            } else if (((s = std::to_string(k)).length() % 2) == 0) {
                unsigned long a = 0, b = 0;
                a = std::stoul(s.substr(0, s.length() / 2));
                b = std::stoul(s.substr(s.length() / 2));
                next[a] += v;
                next[b] += v;
            } else {
                next[k*2024] += v;
            }
        }
        nums = next;
    }

    size_t sum = std::accumulate(nums.begin(), nums.end(), 0, [](size_t p_sum, const auto& v) {
        return p_sum + v.second;
    });

    std::cout << sum << std::endl;
}
