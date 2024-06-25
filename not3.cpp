#include <iostream>
#include <string>

int main() {
    std::string input;
    std::cout << "لطفاً یک رشته وارد کنید که حرف f در آن وجود داشته باشد: ";
    std::cin >> input;

    size_t found = input.find('f');

    if (found != std::string::npos && found + 2 < input.length() && isalpha(input[found + 1]) && isalpha(input[found + 2])) {
        std::cout << "پیام: مثبت - دو کاراکتر بعد از حرف f کاراکتری هستند." << std::endl;
    } else {
        std::cout << "پیام: منفی - دو کاراکتر بعد از حرف f کاراکتری نیستند." << std::endl;
    }

    return 0;
}
