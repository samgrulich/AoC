#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>

struct Vec2 {
    int x, y;
    
    bool operator==(const Vec2& vec) const { return x == vec.x && y == vec.y; }
    bool operator!=(const Vec2& vec) const { return x != vec.x || y != vec.y; }
    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec) { return os << "(" << vec.x << ", " << vec.y << ")"; }
};

class Keypad {
    std::vector<char> keys_;
    Vec2 size_;
    Vec2 pos_;

protected:
    Keypad(std::initializer_list<char> keys, Vec2 size, Vec2 pos) : keys_(keys), size_(size), pos_(pos) {}
    bool isInside() const;
    bool isInside(const Vec2& vec) const;
public:
    static void printKeypads(const Keypad& k0, const Keypad& k1, const Keypad& k2);
    void move(const Vec2& dir);
    Vec2 getPos(const char& c) const;
    void gotoPos(const Vec2& pos);
    std::string getPath(const Vec2& pos) const;
    std::string getPathAndGoto(const char& c);
};

class NumericKeypad : public Keypad {
public:
    NumericKeypad() : Keypad(
            {
            '7', '8', '9',
            '4', '5', '6',
            '1', '2', '3',
            ' ', '0', 'A'
            },
            {3, 4}, 
            {2, 3}
            ) {}
};

class DirectionalKeypad : public Keypad {
public:
    DirectionalKeypad() : Keypad(
            {
            ' ', '^', 'A',
            '<', 'v', '>'
            },
            {3, 2},
            {2, 0}
            ) {}
};

std::vector<std::string> codes;
NumericKeypad k0;
DirectionalKeypad k1;
DirectionalKeypad k2;


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    std::string line;
    while (std::getline(file, line)) {
        codes.push_back(line);
    }
    file.close();

    for (const std::string& code : codes) {
        std::string path = "";
        for (const char& c : code) {
            std::string path0 = k0.getPathAndGoto(c);
            for (const char& p0 : path0) {
                std::string path1 = k1.getPathAndGoto(p0);
                // printf("%c: %s\n", c, path1.c_str());
                for (const char& p1 : path1) {
                    std::string path2 = k2.getPathAndGoto(p1);
                    for (const char& p2 : path2) {
                        path += p2;
                    }
                }
            }
        }
        std::cout << code << ": " << path.length() << "; " << path << std::endl;
        path.clear();
    }
}

bool Keypad::isInside() const {
    return pos_.x >= 0 && pos_.x < size_.x && pos_.y >= 0 && pos_.y < size_.y;
}

bool Keypad::isInside(const Vec2& vec) const {
    return vec.x >= 0 && vec.x < size_.x && vec.y >= 0 && vec.y < size_.y;
}

void Keypad::move(const Vec2& dir) {
    Vec2 newPos = {pos_.x + dir.x, pos_.y + dir.y};
    if (isInside(newPos)) {
        pos_ = newPos;
    } else {
        std::cerr << "Invalid move: " << pos_  << "; " << dir << std::endl;
    }
}

Vec2 Keypad::getPos(const char& c) const {
    for (int i = 0; i < keys_.size(); i++) {
        if (keys_[i] == c) {
            return {i % size_.x, i / size_.x};
        }
    }
    return {-1, -1};
}

void Keypad::gotoPos(const Vec2& pos) {
    if (isInside(pos)) {
        pos_ = pos;
    } else {
        std::cerr << "Invalid position: " << pos << std::endl;
    }
}

std::string Keypad::getPath(const Vec2& pos) const {
    std::string path;
    Vec2 tmp = pos_;
    while (tmp != pos) {
        if (tmp.x < pos.x) {
            path += '>';
            tmp.x++;
        } else if (tmp.y < pos.y) {
            path += 'v';
            tmp.y++;
        } else if (tmp.y > pos.y) {
            path += '^';
            tmp.y--;
        } else if (tmp.x > pos.x) {
            path += '<';
            tmp.x--;
        }
    }
    return path + 'A';
}

void Keypad::printKeypads(const Keypad &k0, const Keypad &k1, const Keypad &k2) {
    for (int y = 0; y < k0.size_.y; y++) {
        for (int x = 0; x < k0.size_.x; x++) {
            char c = k0.keys_[y * k0.size_.x + x];
            std::cout << (k0.pos_ == Vec2{x, y} ? '*' : c); 
        }
        std::cout << "  ";
        if (y >= k1.size_.y) {
            std::cout << std::endl;
            continue;
        }
        for (int x = 0; x < k1.size_.x; x++) {
            char c = k1.keys_[y * k1.size_.x + x];
            std::cout << (k1.pos_ == Vec2{x, y} ? '*' : c); 
        }
        std::cout << "  ";
        for (int x = 0; x < k2.size_.x; x++) {
            char c = k2.keys_[y * k2.size_.x + x];
            std::cout << (k2.pos_ == Vec2{x, y} ? '*' : c);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
    

std::string Keypad::getPathAndGoto(const char& c) { 
    Vec2 pos = getPos(c); 
    std::string path = getPath(pos); 
    // Keypad::printKeypads(k0, k1, k2); 
    gotoPos(pos); 
    return path; 
}
