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
#define FIELD_DUMMY(structure__) {"", sizeof(structure__), 0}
#define FIELD(structure__, name__, type__) {#name__, offsetof(structure__, name__), sizeof(type__)}
#define FIELD_VEC(vecname__) const std::vector<std::tuple<std::string, size_t, size_t>> vecname__
#define FIELD_PRINT(vec__) \
    for (int i = 0; i < o.size() - 1; ++i) { \
        auto [name, offset, size] = vec__[i]; \
        auto [_, next_offset, __] = vec__[i + 1]; \
        std::cout << name << " | " \
        << repeat("* ", size) \
        << repeat("- ", next_offset - (offset + size)) \
        << std::endl; \
    }

//#pragma pack(push, 1)
struct X {
    char a;
    int b;
    char c;
};
//#pragma pack(pop)

static void view_X(void) {
    REPEAT;
    FIELD_VEC(o) = {
        FIELD(struct X, a, char),
        FIELD(struct X, b, int),
        FIELD(struct X, c, char),
        FIELD_DUMMY(struct X)
    };
    FIELD_PRINT(o);
}

static void foo(void) {
    view_X();
}

int main(void) {
    foo();
    return 0;
}
