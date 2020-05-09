#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

const int NO_PATH = 270100;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

struct Coor {
    int x;
    int y;
    int z;
};

bool operator==(const Coor& self, const Coor& other) {
    return self.x == other.x && self.y == other.y && self.z == other.z;
}

using Maze = vector<vector<vector<char>>>;

struct Input {
    Maze maze;
    Coor start;
    Coor end;
};

Input read_in() {
    UIN K, N, M;
    cin >> K >> N >> M;
    Input in;

    in.maze = vector<vector<vector<char>>>(
        K, vector<vector<char>>(N, vector<char>(M, ' ')));

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                cin >> in.maze[i][j][k];

                if (in.maze[i][j][k] == 'S') {
                    in.start = {i, j, k};
                } else if (in.maze[i][j][k] == 'E') {
                    in.end = {i, j, k};
                }
            }
        }
    }

    return in;
}

using EscapeTimes = vector<vector<vector<int>>>;
using VisitMap    = vector<vector<vector<bool>>>;

int escape(const Coor loc, const Maze& maze, EscapeTimes& escape_times,
           VisitMap& visited) {
    // out of bounds
    if ((loc.x >= maze.size() || loc.x < 0) ||
        (loc.y >= maze[0].size() || loc.y < 0) ||
        (loc.z >= maze[0][0].size() || loc.z < 0)) {
        return NO_PATH;
    }

    // cout << loc.x << " " << loc.y << " " << loc.z << endl;

    // already memoized
    if (escape_times[loc.x][loc.y][loc.z] != -1) {
        return escape_times[loc.x][loc.y][loc.z];
    }
    // return to prevent infinite cycle
    else if (visited[loc.x][loc.y][loc.z]) {
        return NO_PATH;
    }

    auto curr_maze_val = maze[loc.x][loc.y][loc.z];

    switch (curr_maze_val) {
        case 'E':
            return 0;
        case '#':
            return NO_PATH;
        default:
            visited[loc.x][loc.y][loc.z] = true;

            auto candidates = {
                // move up
                escape({loc.x + 1, loc.y, loc.z}, maze, escape_times, visited),
                // move left
                escape({loc.x, loc.y, loc.z - 1}, maze, escape_times, visited),
                // move right
                escape({loc.x, loc.y, loc.z + 1}, maze, escape_times, visited),
                // move south
                escape({loc.x, loc.y + 1, loc.z}, maze, escape_times, visited),
                // move north
                escape({loc.x, loc.y - 1, loc.z}, maze, escape_times, visited),
                // move down
                escape({loc.x - 1, loc.y, loc.z}, maze, escape_times, visited)};

            auto res = *min_element(candidates.begin(), candidates.end()) + 1;

            // cout << "escape time at " << loc.x << " " << loc.y << " " <<
            // loc.z
            //      << " is " << res << endl;

            escape_times[loc.x][loc.y][loc.z] = res;
            visited[loc.x][loc.y][loc.z]      = false;

            return res;
    }
}

int plan_escape(Input& in) {
    auto escape_times = vector<vector<vector<int>>>(
        in.maze.size(),
        vector<vector<int>>(in.maze[0].size(),
                            vector<int>(in.maze[0][0].size(), -1)));

    auto visit_map = vector<vector<vector<bool>>>(
        in.maze.size(),
        vector<vector<bool>>(in.maze[0].size(),
                             vector<bool>(in.maze[0][0].size(), false)));

    return escape(in.start, in.maze, escape_times, visit_map);
}

void fmtout(int out) {
    if (out >= NO_PATH) {
        cout << "Trapped!" << endl;
    } else {
        cout << "Escaped in " << out << " minute(s)." << endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in  = read_in();
    auto out = plan_escape(in);
    fmtout(out);
}
