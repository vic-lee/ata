#include <iostream>
#include <sstream>
#include <vector>

#define FOR_N(n) for (size_t i = 0; i < n; i++)

using namespace std;
using UIN = unsigned int;
using LL  = long long;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    std::ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    std::cout << oss.str();
}

struct SailDirection {
    bool should_sail_east;
    bool should_sail_south;
    bool should_sail_west;
    bool should_sail_north;
};

struct Coor {
    LL x;
    LL y;

    Coor(LL x, LL y) : x(x), y(y) {}

    void move_east() { x++; }

    void move_west() { x--; }

    void move_north() { y++; }

    void move_south() { y--; }

    bool operator==(const Coor& other) const {
        return x == other.x && y == other.y;
    }

    SailDirection relative_to(const Coor& dest) const {
        bool should_sail_east  = dest.x > x;
        bool should_sail_west  = dest.x < x;
        bool should_sail_north = dest.y > y;
        bool should_sail_south = dest.y < y;

        return {
            should_sail_east,
            should_sail_south,
            should_sail_west,
            should_sail_north,
        };
    }
};

struct ProcessedInput {
    std::vector<char> wind_directions;
    Coor              start;
    Coor              end;
    UIN               time_limit;

    ProcessedInput(UIN time_limit, Coor start, Coor end)
        : time_limit(time_limit), start(start), end(end) {
        wind_directions = vector<char>(time_limit, ' ');
    }
};

ProcessedInput read_in() {
    UIN time_lim;
    LL  s_x, s_y, e_x, e_y;

    std::cin >> time_lim >> s_x >> s_y >> e_x >> e_y;
    ProcessedInput in(time_lim, Coor(s_x, s_y), Coor(e_x, e_y));

    FOR_N(in.time_limit) { std::cin >> in.wind_directions[i]; }

    return in;
}

int attempt_sail(ProcessedInput& in) {
    for (size_t i = 0; i < in.wind_directions.size(); i++) {
        SailDirection dir = in.start.relative_to(in.end);

        const char curr_wind_dir = in.wind_directions[i];

        if (dir.should_sail_east && curr_wind_dir == 'E') {
            in.start.move_east();
        } else if (dir.should_sail_west && curr_wind_dir == 'W') {
            in.start.move_west();
        } else if (dir.should_sail_south && curr_wind_dir == 'S') {
            in.start.move_south();
        } else if (dir.should_sail_north && curr_wind_dir == 'N') {
            in.start.move_north();
        }

        if (in.start == in.end) {  // reached destination
            return i + 1;
        }
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    auto in = read_in();
    std::cout << attempt_sail(in) << std::endl;
}
