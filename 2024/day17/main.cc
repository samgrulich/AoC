#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

int ip = 0;
long regs[3] = {0, 0, 0};
std::vector<short> program;
std::vector<short> output;

// long val = std::pow(8, 16);
std::vector<long> vals;

int combo(short operand);
int op(short code, short operand);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // Read registers
    std::ifstream file(argv[1]);
    std::string line;
    int i = 0;
    while (std::getline(file, line) && !line.empty()) {
        regs[i++] = std::stoi(line.substr(12));
    }
    regs[0] = 0; // reset register 0
    // Read program
    std::getline(file, line);
    line = line.substr(9);
    while (line.size() > 1) {
        program.push_back(std::stoi(line.substr(0, 1))); 
        line = line.substr(2);
    }
    program.push_back(std::stoi(line.substr(0, 1))); 


    // Find possible vals
    size_t section_end = 0;
    for (int i = 0; i < 16; i++) {

    }

    // Test them
    while (true) {
        // Run program
        // if (val % 100000000 == 0) {
        //     std::cout << "Trying solution: " << val << std::endl;
        // }
        while (ip < program.size()) {
            short code = program[ip];
            short operand = program[ip+1];
            // printf("ip=%d, code=%d, operand=%d, regs=[%d, %d, %d]\n", ip, code, operand, regs[0], regs[1], regs[2]);
            if (op(code, operand) == 0) {
                ip += 2;
            }
            if (code == 5) {
                int idx = output.size() - 1;
                if (output[idx] != program[idx]) {
                    break;
                }
            }
        }
        // if (output == program) {
        //     std::cout << "Found solution: " << val << std::endl;
        //     return 0;
        // }
        // std::cout << "Failed solution: " << val << std::endl;
        // regs[0] = val++;
        regs[1] = 0;
        regs[2] = 0;
        ip = 0;
        output.clear();
    }
}

int combo(short operand) {
    if (operand >= 0 && operand <= 3) {
        return operand;
    } else if (operand > 3 && operand <= 6) {
        return regs[operand - 4];
    } else {
        std::cerr << "Invalid operand: " << operand << std::endl;
        return -1;
    }
}

int op(short code, short operand) {
    switch(code) {
        case 0: // adv 
            regs[0] = regs[0] >> combo(operand);
            break;
        case 1: // bxl
            regs[1] = regs[1] ^ operand;
            break;
        case 2: // bst
            regs[1] = combo(operand) & 0x7;
            break;
        case 3: // jnz 
            if (regs[0] != 0) {
                ip = operand;
                return 1; // jump occurred
            }
            break;
        case 4: // bxc 
            regs[1] = regs[1] ^ regs[2];
            break;
        case 5: // out
            output.push_back(combo(operand) & 0x7);
            break;
        case 6: // bdv
            regs[1] = regs[0] >> combo(operand);
            break;
        case 7: // bdv
            regs[2] = regs[0] >> combo(operand);
            break;
    }
    return 0;
}
