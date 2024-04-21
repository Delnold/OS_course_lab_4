#include <iostream>
#include <windows.h>
#include <string>
#include <limits> // Include <limits> for std::numeric_limits

int main() {
    char firstWord[512];
    std::cout << "PID: " << GetCurrentProcessId() << " Addr: " << static_cast<const void *>(firstWord) << "\n";
    while (true) {
        memset(firstWord, 0, sizeof(firstWord));
        std::cout << "Enter a new message ('exit' to quit): " << std::endl;
        std::cin.getline(firstWord, sizeof(firstWord));
        if (std::string(firstWord) == "exit") {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Message: " << firstWord << "\t" << "Addr:" << static_cast<const void *>(firstWord) << std::endl;
        Sleep(1000);
    }

    return 0;
}
