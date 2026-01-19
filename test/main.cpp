#include <Windows.h>
#include <iostream>

typedef void (*StartFlavorFunc)();

int main()
{
    HMODULE hModule = LoadLibraryW(L"../x64/Release/Flavor.dll");
    if (!hModule)
    {
        std::cerr << "Failed to load Flavor.dll, error: " << GetLastError() << std::endl;
        return 1;
    }

    StartFlavorFunc StartFlavor = (StartFlavorFunc)GetProcAddress(hModule, "StartFlavor");
    if (!StartFlavor)
    {
        std::cerr << "Failed to get StartFlavor function" << std::endl;
        FreeLibrary(hModule);
        return 1;
    }

    std::cout << "Starting Flavor..." << std::endl;
    StartFlavor();
    std::cout << "Flavor closed." << std::endl;

    FreeLibrary(hModule);
    return 0;
}
