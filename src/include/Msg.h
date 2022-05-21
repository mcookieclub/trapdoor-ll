//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_MSGBUILDER_H
#define TRAPDOOR_MSGBUILDER_H

#include <cstdarg>
#include <map>
#include <string>
#include <vector>

#define PH_DARK_RED "§4{}§r"
#define PH_RED "§c{}§r"
#define PH_GOLD "§6{}§r"
#define PH_DARK_GREEN "§2{}§r"
#define PH_YELLOW "§e{}§r"
#define PH_GREEN "§a{}§r"
#define PH_AQUA "§b{}§r"
#define PH_BLUE "§9{}§r"
#define PH_LIGHT_PURLPE "§d{}§r"
#define PH_WHITE "§f{}§r"
#define PH_GRAY "§7{}§r"
#define PH_DOUB "§f{:.3lf}§r"
#define PH_NUM "§2{}§r"
#define PH_POS "§a{},{},{}§r"

namespace tr {
    void BroadcastMessage(const std::string &msg, int level = 0);

    template <typename... Args>
    std::string format(const std::string &format, Args... args) {
        auto size = snprintf(nullptr, 0, format.c_str(), args...) +
                    1;  // Extra space for '\0'
        if (size <= 0) return "";
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args...);
        return std::string(
            buf.get(), buf.get() + size - 1);  // We don't want the '\0' inside
    }

    struct TVec3;
    struct TBlockPos;
    struct TAABB;
    class TextBuilder {
       public:
        static const uint8_t DARK_RED;
        static const uint8_t RED;
        static const uint8_t GOLD;
        static const uint8_t YELLOW;
        static const uint8_t GREEN;
        static const uint8_t DARK_GREEN;
        static const uint8_t AQUA;
        static const uint8_t BLUE;
        static const uint8_t LIGHT_PURPLE;
        static const uint8_t WHITE;
        static const uint8_t GRAY;
        static const uint8_t BLACK;

        static const uint8_t BOLD;
        static const uint8_t ITALIC;
        static const uint8_t RESET;

        TextBuilder &text(const std::string &s);

        template <typename... Args>
        TextBuilder &textF(const std::string &format, Args... args) {
            this->text(tr::format(format, args...));
            return *this;
        }

        template <typename... Args>
        TextBuilder &sTextF(uint8_t style, const std::string &format,
                            Args... args) {
            this->sText(trapdoor::format(format, args...), style);
            return *this;
        }
        TextBuilder &sText(uint8_t style, const std::string &s);

        TextBuilder &pos(const TBlockPos &pos);

        template <typename T>
        TextBuilder &num(T x) {
            if (std::is_arithmetic<T>()) {
                if (std::is_floating_point<T>()) {
                    char buffer[32];
                    sprintf(buffer, "%.3f", (double)x);
                    std::string s(buffer);
                    sText(s, DARK_GREEN | BOLD);
                } else {
                    sText(std::to_string(x), DARK_GREEN | BOLD);
                }
            }
            return *this;
        }

        TextBuilder &vec3(const TVec3 &vec3);

        TextBuilder &aabb(const TAABB &aabb);

        inline void clear() { this->messageBuffer.clear(); }

        std::string get();

        void broadcast();

        void operator+=(const std::string &str) { this->text(str); }

       private:
        const static std::map<uint8_t, std::string> STYLE_MAP;
        std::vector<std::string> messageBuffer;
    };

}  // namespace tr
#endif  // TRAPDOOR_MSGBUILDER_H
