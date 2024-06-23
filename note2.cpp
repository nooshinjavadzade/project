#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    std::string line;

    if (inputFile.is_open() && outputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            if (line.find("hi") != 0) {
                outputFile << line << std::endl;
            }
        }

        inputFile.close();
        outputFile.close();
        std::cout << "Filtered lines saved to output.txt" << std::endl;
    } else {
        std::cout << "Unable to open files." << std::endl;
    }

    return 0;
}
