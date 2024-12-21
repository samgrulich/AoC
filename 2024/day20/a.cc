#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <limits>

struct Step {
    int x, y, score;
    Step(int x, int y, int score) : x(x), y(y), score(score) {}
};

int mapX, mapY;
std::vector<std::string> map;
std::vector<int> scores;
std::queue<Step> q;
int startX, startY, endX, endY;

bool isInside(int x, int y);
int toIndex(int x, int y);
int scoreDifference(int x, int y, int score);

void printMap();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    std::string line;
    while (std::getline(file, line)) {
        map.push_back(line);
    }
    mapX = map[0].size();
    mapY = map.size();
    file.close();

    // map initialization
    scores = std::vector<int>(mapX * mapY, std::numeric_limits<int>::max());
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            if (map[y][x] == '#') {
                scores[toIndex(x, y)] = -1;
            } else if (map[y][x] == 'S') {
                startX = x;
                startY = y;
            } else if (map[y][x] == 'E') {
                endX = x;
                endY = y;
            }
        }
    }

    // dfs scores initialization
    q.push({startX, startY, 0});
    while (!q.empty()) {
        Step step = q.front(); q.pop();
        int idx = toIndex(step.x, step.y);
        if (!isInside(step.x, step.y) || scores[idx] == -1 || scores[idx] < step.score) {
            continue;
        }
        scores[idx] = step.score;
        q.push({step.x + 1, step.y, step.score + 1});
        q.push({step.x - 1, step.y, step.score + 1});
        q.push({step.x, step.y + 1, step.score + 1});
        q.push({step.x, step.y - 1, step.score + 1});
    }


    // count the cheats :)
    std::map<int, int> cheats;
    q.push({startX, startY, 0});
    while (!q.empty()) {
        Step step = q.front(); q.pop();
        int idx = toIndex(step.x, step.y);
        if (!isInside(step.x, step.y) || scores[idx] == -1 || scores[idx] < step.score) {
            continue;
        }

        // checkout cheats
        int diff = 0;
        if ((diff = scoreDifference(step.x + 2, step.y, step.score+2)) > 1) {
            cheats[diff]++;
        }
        if ((diff = scoreDifference(step.x - 2, step.y, step.score+2)) > 1) {
            cheats[diff]++;
        }
        if ((diff = scoreDifference(step.x, step.y + 2, step.score+2)) > 1) {
            cheats[diff]++;
        }
        if ((diff = scoreDifference(step.x, step.y - 2, step.score+2)) > 1) {
            cheats[diff]++;
        }

        // continue
        q.push({step.x + 1, step.y, step.score + 1});
        q.push({step.x - 1, step.y, step.score + 1});
        q.push({step.x, step.y + 1, step.score + 1});
        q.push({step.x, step.y - 1, step.score + 1});
    }

    // for (auto& cheat : cheats) {
    //     std::cout << cheat.second << ": " << cheat.first << std::endl;
    // }
    //
    // printMap();
    long sum = 0;
    for (auto& cheat : cheats) {
        if (cheat.first >= 100) {
            sum += cheat.second;
        }
    }

    std::cout << sum << std::endl;
}

bool isInside(int x, int y) {
    return 0 <= x && x < mapX && 0 <= y && y < mapY;
}

int toIndex(int x, int y) {
    return y * mapX + x;
}

int scoreDifference(int x, int y, int score) {
    if (!isInside(x, y) || scores[toIndex(x, y)] == -1) {
        return 0;
    }
    return scores[toIndex(x, y)] - score;
}

void printMap() {
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            int score = scores[toIndex(x, y)];
            if (score == -1) {
                std::cout << "# ";
            } else if (score == std::numeric_limits<int>::max()) {
                std::cout << ". ";
            } else {
                printf("%02d", score);
            }
        }
        std::cout << std::endl;
    }
}
