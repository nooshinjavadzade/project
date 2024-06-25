#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    ifstream file("example.txt"); // باز کردن فایل برای خواندن

    if (!file.is_open()) {
        cerr << "فایل قابل باز کردن نیست!";
        return 1;
    }

    string wordToFind = "mewo";
    string line;
    const int MAX_LINES = 1000; // حداکثر تعداد خطوط ممکن در فایل
    string linesContainingWord[MAX_LINES];
    int linesCount = 0;

    while (getline(file, line)) {
        if (line.find(wordToFind) != string::npos) {
            if (linesCount < MAX_LINES) {
                linesContainingWord[linesCount] = line;
                linesCount++;
            } else {
                cout << "تعداد خطوط حاوی کلمه mewo بیش از حد مجاز است." << endl;
                break;
            }
        }
    }

    if (linesCount == 0) {
        cout << "هیچ کلمه mewo در فایل یافت نشد." << endl;
        return 0;
    }

    srand(time(0));
    int randomIndex = rand() % linesCount;
    cout << "یکی از خطوطی که کلمه mewo در آن وجود دارد به صورت تصادفی انتخاب شد:" << endl;
    cout << linesContainingWord[randomIndex] << endl;

    if (randomIndex < linesCount - 2) {
        cout << linesContainingWord[randomIndex + 1] << endl;
        cout << linesContainingWord[randomIndex + 2] << endl;
    }

    file.close(); // بستن فایل
    return 0;
}
