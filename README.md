# ApiHashing

This project demonstrates API hashing techniques for locating and calling Windows APIs without directly referencing their names, a method often used in advanced malware development.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Code Overview](#code-overview)
- [License](#license)

## Introduction

ApiHashing is a C project that showcases how to use hash values to identify and call Windows API functions dynamically. This method can be used to obfuscate API calls, making reverse engineering more challenging.

## Features

- Hashes API names using the Jenkins one-at-a-time hash algorithm.
- Retrieves function addresses based on their hashed names.
- Demonstrates usage with the `MessageBoxA` function from `user32.dll`.

## Installation

To compile and run this project, you need to have a C compiler and Windows SDK installed.

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/ApiHashing.git
    cd ApiHashing
    ```

2. Compile the source code:
    ```sh
    gcc -o apihashing apihashing.c -luser32
    ```

## Usage

1. Run the compiled executable:
    ```sh
    ./apihashing
    ```

2. The program will display a message box with the text "Building Malware With Maldev".

## Code Overview

### Hash Functions

The project includes two hash functions to compute Jenkins one-at-a-time hash for both ANSI and wide strings.

```c
UINT32 HashStringJenkinsOneAtATime32BitA(_In_ PCHAR String);
UINT32 HashStringJenkinsOneAtATime32BitW(_In_ PWCHAR String);
```
### GetProcAddressH Function

Retrieves the address of an API function based on its hashed name.

```c
FARPROC GetProcAddressH(HMODULE hModule, DWORD dwApiNameHash);
```
### GetModuleHandleH Function

Retrieves the handle of a module based on its hashed name.

```c
HMODULE GetModuleHandleH(DWORD dwModuleNameHash);
```
## Example Usage
The main function demonstrates how to use the hashed API retrieval functions to call MessageBoxA.
```c
int main() {
    // Load user32.dll to the current process
    if (LoadLibraryA("USER32.DLL") == NULL) {
        printf("[!] LoadLibraryA Failed With Error : %d \n", GetLastError());
        return 0;
    }

    // Get handle of user32.dll
    HMODULE hUser32Module = GetModuleHandleH(USER32DLL_HASH);
    if (hUser32Module == NULL){
        printf("[!] Couldn't Get Handle To User32.dll \n");
        return -1;
    }

    // Get address of MessageBoxA function
    fnMessageBoxA pMessageBoxA = (fnMessageBoxA)GetProcAddressH(hUser32Module, MessageBoxA_HASH);
    if (pMessageBoxA == NULL) {
        printf("[!] Couldn't Find Address Of Specified Function \n");
        return -1;
    }

    // Call MessageBoxA
    pMessageBoxA(NULL, "Api Hashing Example", "Raulisr00t", MB_OK | MB_ICONEXCLAMATION);

    printf("[#] Press <Enter> To Quit ... ");
    getchar();

    return 0;
}
```
## License
This project is licensed under the MIT License. See the LICENSE file for details.
