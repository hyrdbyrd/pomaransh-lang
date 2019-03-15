#include <iostream>
#include <Windows.h>

namespace console {
    template<typename ANY>
    void log(const ANY &content) {
        std::cout << content << " ";
    }
    
    template<typename FIRST, typename ...REST>
    void log(const FIRST &first, const REST &...rest) {
        console::log(first);
        console::log(rest...);
    }

    template<typename ANY>
    void warn(const ANY &content) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 14));
        console::log(content);
        SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
    }
}

int main()
{
    console::warn("Hello there");
    console::log("Alala", "Alala", 56);
    return 0;
}