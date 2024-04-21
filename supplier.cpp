#include <iostream>
#include <windows.h>
#include <string>

int main() {
    std::string prevMessage;
    DWORD targetPid = 19592;
    uintptr_t baseAddress = 0xd459dff430;

    while (true) {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, targetPid);
        if (hProcess == NULL) {
            std::cerr << "Failed to open process. Error code: " << GetLastError() << std::endl;
            return 1;
        }
        const int bufferSize = 512;
        char buffer[bufferSize];
        SIZE_T bytesRead;
        if (!ReadProcessMemory(hProcess, (LPCVOID) baseAddress, buffer, bufferSize, &bytesRead)) {
            std::cerr << "Failed to read memory. Error code: " << GetLastError() << std::endl;
            CloseHandle(hProcess);
            return 1;
        }

        std::string currMessage;
        for (int i = 0; i < bytesRead; ++i) {
            if (buffer[i] >= 32 && buffer[i] <= 126) {
                currMessage += buffer[i];
            }
        }
        if (!currMessage.empty() && currMessage != prevMessage) {
            std::cout << "Message read from process " << targetPid << ": " << currMessage << std::endl;
            prevMessage = currMessage; // Update the previous message
        }
        CloseHandle(hProcess);
    }
}
