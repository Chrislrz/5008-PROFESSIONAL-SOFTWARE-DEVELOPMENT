#include <iostream>
#include <fstream>
#include <string>

// Function to process each line
int process_line(const std::string &line);

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int totalSum = 0;

    while (getline(file, line)) {
        totalSum += process_line(line);
    }
    // g++ -std=c++11 "1a(2).cpp" -o "1a(2)" && ./"1a(2)".
    // using this command to run the program.
    std::cout << "Total Sum: " << totalSum << std::endl;
    return 0;
}

int process_line(const std::string &line) {
    int firstNum = -1, lastNum = -1;
    for (char ch : line) {
        if (isdigit(ch)) {
            if (firstNum == -1) {
                firstNum = ch - '0';
            }
            lastNum = ch - '0';
        }
    }
    return (firstNum != -1 && lastNum != -1) ? (firstNum * 10 + lastNum) : 0;
}

    // g++ -std=c++11 "1a(2).cpp" -o "1a(2)" && ./"1a(2)".
    // using this command to run the program.