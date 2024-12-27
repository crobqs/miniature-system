#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <vector>

#define REPEAT \
    auto repeat = [](const std::string& str, size_t times) { \
        std::ostringstream oss; \
        std::generate_n( \
            std::ostream_iterator<std::string>(oss), \
            times, \
            [&]() { \
                return str; \
            } \
        ); \
        return oss.str(); \
    }
#define STRINGIZE_(x__) #x__
#define STRINGIZE(x__) STRINGIZE_(x__)
#define FIELD_DUMMY {"", sizeof(FIELD_STRUCT), 0}
#define FIELD(name__, type__) {#name__, offsetof(FIELD_STRUCT, name__), sizeof(type__)}
#define FIELD_STRUCT
#define FIELD_VEC \
    {std::cout << STRINGIZE(FIELD_STRUCT) << std::endl; \
    const std::vector<std::tuple<std::string, size_t, size_t>> o
#define FIELD_PRINT \
    for (int i = 0; i < o.size() - 1; ++i) { \
        auto [name, offset, size] = o[i]; \
        auto [_, next_offset, __] = o[i + 1]; \
        std::cout << name << " | " \
        << repeat("* ", size) \
        << repeat("- ", next_offset - (offset + size)) \
        << std::endl; \
    } \
    std::cout << std::endl;}

struct X {
    char a;
    int b;
    char c;
};

#pragma pack(push, 1)
struct XX {
    char a;
    int b;
    char c;
};
#pragma pack(pop)

static void view_X(void) {
    REPEAT;

    #undef FIELD_STRUCT
    #define FIELD_STRUCT struct X
    FIELD_VEC = {
        FIELD(a, char),
        FIELD(b, int),
        FIELD(c, char),
        FIELD_DUMMY
    };
    FIELD_PRINT;

    #undef FIELD_STRUCT
    #define FIELD_STRUCT struct XX
    FIELD_VEC = {
        FIELD(a, char),
        FIELD(b, int),
        FIELD(c, char),
        FIELD_DUMMY
    };
    FIELD_PRINT;
}

static void foo(void) {
    view_X();
}

int main(void) {
    foo();
    return 0;
}
