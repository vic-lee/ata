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

/**
 * Returns the optimal (lowest) amount Luna has to pay.
 *
 * After carefully analyzing the prompt, one should realize that the output
 * pathway does not depend on the Eto's choices. A previously mutual-recursive
 * solution, where we optimize (maximize) Eto's score at every his turn, is
 * abandonded.
 *
 * Further, one should note that the _order_ of picking columns does not matter.
 * This is because the final score is the summation of all the cells picked,
 * and summation is commutative. This can reduce the program's recursive
 * for loop from a 2-D one to onr that's 1-D.
 *
 * Previous implementation takes ~ 7 secs on N = 7. This takes 0 secs.
 */
int play_board_game(Grid& grid, UIN luna_col) {
    if (luna_col >= grid.cells[0].size()) {
        return 0;
    }

    // the balance luna has to pay out; lower is better for luna
    int luna_optimal_score = INT_MAX;

    for (size_t row = 0; row < grid.cells.size(); row++) {
        if (!grid.row_visited[row] && !grid.col_visited[luna_col]) {
            grid.row_visited[row]      = true;
            grid.col_visited[luna_col] = true;

            int luna_score =
                play_board_game(grid, luna_col + 1) + grid.cells[row][luna_col];
            luna_optimal_score = min(luna_score, luna_optimal_score);

            grid.row_visited[row]      = false;
            grid.col_visited[luna_col] = false;
        }
    }

    return luna_optimal_score;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto grid = read_in();
    auto out  = play_board_game(grid, 0);
    cout << out << endl;
}
