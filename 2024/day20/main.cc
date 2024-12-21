#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <limits>

struct Step {
    int x, y, score, cheat_step = 0, cheat_origin = 0;
    Step(int x, int y, int score) : x(x), y(y), score(score) {}
    Step(int x, int y, int score, int cheat_step, int cheat_origin) : x(x), y(y), score(score), cheat_step(cheat_step), cheat_origin(cheat_origin){}
};

int mapX, mapY;
std::vector<std::string> map;
std::vector<int> scores;
std::queue<Step> q;
std::queue<Step> qq;
int startX, startY, endX, endY;

bool isInside(int x, int y);
int toIndex(int x, int y);
int scoreDifference(int x, int y, int score);

void printMap();
void printVisited(const std::vector<bool>& visited);

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
        std::vector<bool> visited(mapX * mapY, false);
        qq.push({step.x, step.y, step.score, 0, scores[idx]});
        while (!qq.empty()) {
            Step s = qq.front(); qq.pop();
            int idx = toIndex(s.x, s.y);
            if (!isInside(s.x, s.y) || s.cheat_step > 20 || visited[toIndex(s.x, s.y)]) {
                continue;
            }
            visited[toIndex(s.x, s.y)] = true;
            int diff = 0;
            if ((diff = scores[toIndex(s.x, s.y)] - (s.cheat_origin + s.cheat_step)) > 1) {
                cheats[diff]++;
            }
            qq.push({s.x + 1, s.y, s.score + 1, s.cheat_step + 1, s.cheat_origin});
            qq.push({s.x - 1, s.y, s.score + 1, s.cheat_step + 1, s.cheat_origin});
            qq.push({s.x, s.y + 1, s.score + 1, s.cheat_step + 1, s.cheat_origin});
            qq.push({s.x, s.y - 1, s.score + 1, s.cheat_step + 1, s.cheat_origin});
        }

        // continue
        q.push({step.x + 1, step.y, step.score + 1});
        q.push({step.x - 1, step.y, step.score + 1});
        q.push({step.x, step.y + 1, step.score + 1});
        q.push({step.x, step.y - 1, step.score + 1});
    }

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

void printVisited(const std::vector<bool>& visited) {
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            std::cout << visited[toIndex(x, y)];
        }
        std::cout << std::endl;
    }
}
