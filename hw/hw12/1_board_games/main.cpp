#include <climits>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

template <typename InIt, typename Predicate, typename UnaryFunction>
UnaryFunction for_each_if(InIt first, InIt last, UnaryFunction fn,
                          Predicate pr) {
    for (; first != last; ++first) {
        if (pr(*first)) fn(*first);
    }
    return fn;
}

struct Grid {
    vector<vector<int>> cells;
    vector<bool>        row_visited;
    vector<bool>        col_visited;
};

Grid read_in() {
    UIN N;
    cin >> N;

    Grid grid;
    grid.cells       = vector<vector<int>>(N, vector<int>(N, 0));
    grid.row_visited = vector<bool>(N, false);
    grid.col_visited = vector<bool>(N, false);

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            cin >> grid.cells[i][j];
        }
    }

    return grid;
}

int play_board_game(Grid& grid, UIN num_moves, int prev_row, int prev_col,
                    bool is_eto) {
    if (num_moves >= (grid.cells.size() - 1) * 2) {
        // there is only 1 remaining unvisited cell; return that cell's value
        // as the amount luna has to pay (she's always the last player)
        for (size_t row = 0; row < grid.row_visited.size(); row++) {
            if (!grid.row_visited[row]) {
                for (size_t col = 0; col < grid.col_visited.size(); col++) {
                    if (!grid.col_visited[col]) {
                        return grid.cells[row][col];
                    }
                }
            }
        }
        return 0;
    }

    if (is_eto) {
        // the balance eto will receive from luna; higher is better
        int luna_optimal_score = INT_MIN;

        for (size_t row = 0; row < grid.cells.size(); row++) {
            if (!grid.row_visited[row]) {
                grid.row_visited[row] = true;

                int luna_score =
                    play_board_game(grid, num_moves + 1, row, prev_col, false);

                luna_optimal_score = max(luna_score, luna_optimal_score);

                grid.row_visited[row] = false;
            }
        }

        return luna_optimal_score;
    } else {
        // the balance luna has to pay out; lower is better for luna
        int luna_optimal_score = INT_MAX;

        for (size_t col = 0; col < grid.cells[0].size(); col++) {
            if (!grid.col_visited[col]) {
                grid.col_visited[col] = true;

                int luna_score =
                    play_board_game(grid, num_moves + 1, prev_row, col, true) +
                    grid.cells[prev_row][col];

                luna_optimal_score = min(luna_score, luna_optimal_score);

                grid.col_visited[col] = false;
            }
        }

        return luna_optimal_score;
    }

    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto grid = read_in();
    auto out  = play_board_game(grid, 0, -1, -1, true);
    cout << out << endl;
}
