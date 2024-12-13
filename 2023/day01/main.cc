#include <iostream>
#include <fstream>

std::string numbers[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line;
    int sum = 0;
    while (std::getline(file, line)) {
        char chf = -1, chl = -1;
        for (int i = 0; i < line.size(); i++) {
            char ch = line[i];
            ch -= '0';
            if (ch >= 0 && ch <= 9) {
                if (chf == -1)
                    chf = ch;
                else
                    chl = ch;
            } else {
                for (int j = 0; j < 10; j++) {
                    std::string number = numbers[j];
                    if (line.substr(i, number.size()).compare(number) == 0) {
                        if (chf == -1) 
                            chf = j;
                        else
                            chl = j;
                        break;
                    }
                }
            }
        }
        if (chl == -1)
            chl = chf;
        sum += chf * 10 + chl;
    }
    std::cout << sum << std::endl;
}
