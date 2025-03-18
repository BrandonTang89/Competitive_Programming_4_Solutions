// https://codeforces.com/contest/2082/problem/A
// Max of the number of odd sum rows and odd sum columns

#include <iostream>
#include <algorithm>
#include <vector>
#include <ranges>
#include <print>


int main() {
    int32_t tc;
    std::cin >> tc;
    while (tc--) {
        size_t h, w;
        std::cin >> h >> w;
        std::vector<int8_t> v(h * w, 0);
        for (auto &i : v) {
            char c;
            std::cin >> c;
            i = c == '1' ? 1 : 0;
        }

        auto const rows = v | std::views::chunk(w);
        auto const num_odd_rows = std::ranges::count_if(rows, [](auto const &row) {
            return std::ranges::count(row, 1) % 2 == 1;
        });

        auto const cols = std::views::iota(0u, w) | std::views::transform([&, w = w](auto const i) { return v | std::views::drop(i) | std::views::stride(w); });
        auto const num_odd_cols = std::ranges::count_if(cols, [](auto const &col) {
            return std::ranges::count(col, 1) % 2 == 1;
        });

        std::println("{}", std::max(num_odd_rows, num_odd_cols));
    }
    return 0;
}