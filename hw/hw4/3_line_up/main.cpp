#include <deque>
#include <iostream>
#include <map>
#include <sstream>

#define ELEM_UNDEF 1000000

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

class GroupQueue {
   private:
    IDtoGroupMap id_to_group_;
    deque<deque<unsigned int>> gqueue_;
    map<unsigned int, deque<unsigned int>*> group_refs_;

   public:
    GroupQueue(IDtoGroupMap id_group_map) : id_to_group_(id_group_map){};

    void push(unsigned int x) {
        unsigned int next_elem_group_id = id_to_group_[x];
        if (group_refs_.find(next_elem_group_id) != group_refs_.end()) {
            group_refs_[next_elem_group_id]->push_back(x);
        } else {
            gqueue_.push_back(deque<unsigned int>({x}));
            group_refs_[next_elem_group_id] = &gqueue_.back();
        }
    }

    unsigned int pop() {
        if (!gqueue_.empty()) {
            const auto pop_target = gqueue_.front().front();
            if (gqueue_.front().size() == 1) {
                group_refs_.erase(id_to_group_[pop_target]);
                gqueue_.pop_front();
            } else {
                gqueue_.front().pop_front();
            }
            return pop_target;
        }
        return ELEM_UNDEF;
    }
};

IDtoGroupMap read_in() {
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

    return idmap;
}

ostringstream process_commands(IDtoGroupMap id_group_map) {
    auto gq = GroupQueue(id_group_map);
    string line, cmd;
    ostringstream oss;

    while (getline(cin, line)) {
        if (line == "Shutdown") {
            break;
        } else if (line == "Pop") {
            oss << gq.pop() << '\n';
        } else {
            unsigned int target;
            stringstream(line) >> cmd >> target;
            gq.push(target);
        }
    }

    return oss;
}

int main() {
    auto id_group_map = read_in();
    cout << process_commands(id_group_map).str();
}
