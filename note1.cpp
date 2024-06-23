#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    // ایجاد یک فایل جدید برای نوشتن
    std::ofstream file("example.txt");
    if (file.is_open()) {
        // نوشتن محتوا به فایل
        for (int i = 1; i <= 20; ++i) {
            file << "Line " << i << std::endl;
        }
        file.close();
    } else {
        std::cout << "Unable to create file." << std::endl;
        return 1;
    }

    // باز کردن فایل برای خواندن و نوشتن
    std::ifstream inputFile("example.txt");
    std::ofstream outputFile("temp.txt");
    std::string line;
    int linesToSkip = 10;
    int linesSkipped = 0;

    if (inputFile.is_open() && outputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            if (linesSkipped >= linesToSkip) {
                outputFile << line << std::endl;
            } else {
                linesSkipped++;
            }
        }

        inputFile.close();
        outputFile.close();

        // حذف فایل اصلی
        std::remove("example.txt");
        // تغییر نام فایل temp.txt به example.txt
        std::rename("temp.txt", "example.txt");

        std::cout << "First 10 lines removed from the file." << std::endl;
    } else {
        std::cout << "Unable to open files." << std::endl;
    }

    return 0;
}
