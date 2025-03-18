#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <iostream>
#include <print>

#define fast_cin()                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);
    
static int64_t apply_ceilings(int64_t x, int64_t ceils) {
    while (ceils-- && x > 1) {
        if (x & 1) {
            x = (x >> 1) + 1;
        } else {
            x >>= 1;
        }
    }
    return x;
}

int main() {
    fast_cin();
    int32_t tc;
    std::cin >> tc;
    while (tc--) {
        int64_t x, n, m;
        std::cin >> x >> n >> m;
        n = std::clamp(n, static_cast<int64_t>(0), static_cast<int64_t>(32));
        m = std::clamp(m, static_cast<int64_t>(0), static_cast<int64_t>(32));

        int64_t mini = apply_ceilings(x, m) >> n;
        int64_t maxi = apply_ceilings((x >> n), m);
        std::println("{} {}", mini, maxi);
    }
}