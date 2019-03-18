#include <iostream>
#include <Windows.h>

namespace Pomaransh {
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

        template <typename ANY>
        void color_log(const ANY &content, int text_color, int background_color)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (WORD)((0 << background_color) | text_color));
            console::log(content);
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
        }

        template<typename ANY>
        void warn(const ANY &content) {
            console::color_log(content, 14, 4);
        }

        template <typename ANY>
        void error(const ANY &content) {
            console::color_log(content, 4, 13);
        }
    }
}
