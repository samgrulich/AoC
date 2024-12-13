#include <iostream>
#include <fstream>

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
        for (char ch : line) {
            ch -= '0';
            if (ch >= 0 && ch <= 9) {
                if (chf == -1) {
                    chf = ch;
                } else {
                    chl = ch;
                }
            }
        }
        if (chl == -1)
            chl = chf;
        std::cout << chf * 10 + chl << std::endl;
        sum += chf * 10 + chl;
    }
    std::cout << sum << std::endl;
}
