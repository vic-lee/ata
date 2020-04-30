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

struct GridCell {
    char value;
    int  visited_at;
};

struct Input {
    UIN                      entry_pos;
    vector<vector<GridCell>> grid;
};

Input read_in() {
    Input in;

    UIN num_rows, num_cols;
    cin >> num_rows >> num_cols >> in.entry_pos;
    in.grid = vector<vector<GridCell>>(num_rows,
                                       vector<GridCell>(num_cols, {' ', -1}));

    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_cols; j++) {
            cin >> in.grid[i][j].value;
        }
    }

    return in;
}

void process(Input& in) {
    bool has_loop = false;
    int  curr_x = 0, curr_y = in.entry_pos - 1;
    int  step_count = 0, loop_entry_step;

    do {
        if (in.grid[curr_x][curr_y].visited_at > 0) {
            has_loop        = true;
            loop_entry_step = in.grid[curr_x][curr_y].visited_at - 1;
            break;
        }

        step_count++;
        in.grid[curr_x][curr_y].visited_at = step_count;

        switch (in.grid[curr_x][curr_y].value) {
            case 'N':
                curr_x--;
                break;
            case 'S':
                curr_x++;
                break;
            case 'E':
                curr_y++;
                break;
            case 'W':
                curr_y--;
                break;
            default:
                break;
        }
    } while ((curr_y >= 0 && curr_y <= in.grid[0].size() - 1) &&
             (curr_x >= 0 && curr_x <= in.grid.size() - 1));

    if (has_loop) {
        cout << loop_entry_step << " step(s) before a loop of "
             << (step_count - loop_entry_step) << " step(s)" << endl;
    } else {
        cout << step_count << " step(s) to exit" << endl;
    }
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    process(in);
    fmtout();
}
