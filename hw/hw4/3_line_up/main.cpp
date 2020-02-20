#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;
using IDtoGroupMap = map<unsigned int, unsigned int>;

enum CommandTypes {
    Push,
    Pop,
    Shutdown,
};

struct Command {
    CommandTypes cmd;
    unsigned int tgt;
};

struct Input {
    unsigned int group_cnt;
    unsigned int elem_cnt;
    IDtoGroupMap id_group_map;
};

Input read_in() {
    unsigned short group_cnt;
    unsigned int elem_cnt = 0;
    cin >> group_cnt;
    cin.ignore(256, '\n');

    IDtoGroupMap idmap;
    string line;
    for (int id = 0; id < group_cnt; ++id) {
        getline(cin, line);
        istringstream iss(line);
        unsigned int group_size;
        iss >> group_size;
        for (int j = 0; j < group_size; ++j) {
            unsigned int x;
            iss >> x;
            idmap[x] = id;
            elem_cnt++;
        }
    }

    return {group_cnt, elem_cnt, idmap};
}

ostringstream process_commands(IDtoGroupMap id_group_map,
                               unsigned int group_cnt) {
    auto gqueue = deque<deque<unsigned int>>();
    auto group_refs = map<unsigned int, deque<unsigned int>*>();

    string line, cmd;
    ostringstream oss;

    while (getline(cin, line)) {
        if (line == "Shutdown") {
            break;
        } else if (line == "Pop") {
            if (!gqueue.empty()) {
                const auto to_pop = gqueue.front().front();
                oss << to_pop << '\n';
                if (gqueue.front().size() == 1) {
                    group_refs.erase(id_group_map[to_pop]);
                    gqueue.pop_front();
                } else {
                    gqueue.front().pop_front();
                }
            }
        } else {  // Push xx
            unsigned int tgt;
            stringstream(line) >> cmd >> tgt;
            unsigned int tgt_group = id_group_map[tgt];
            if (group_refs.find(tgt_group) != group_refs.end()) {
                group_refs[tgt_group]->push_back(tgt);
            } else {
                gqueue.push_back(deque<unsigned int>({tgt}));
                group_refs[tgt_group] = &gqueue.back();
            }
        }
    }

    return oss;
}

int main() {
    auto in = read_in();
    cout << process_commands(in.id_group_map, in.group_cnt).str();
}
