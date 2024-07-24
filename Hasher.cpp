#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

#define INITIAL_HASH 3117 // IF you want change these values
#define SEED 7

DWORD StringDJB2(const string& str) {
    ULONG HASH = INITIAL_HASH;
    for (char c : str) {
        HASH = ((HASH << SEED) + HASH) + c;
    }
    return HASH;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "[!] Error: No string provided. Error code: " << GetLastError() << endl;
        return EXIT_FAILURE;
    }

    DWORD result;
    string str = argv[1];
    result = StringDJB2(str);

    cout << "Your Hashed String is: 0x" << hex << uppercase << result << endl;
    return EXIT_SUCCESS;
}
