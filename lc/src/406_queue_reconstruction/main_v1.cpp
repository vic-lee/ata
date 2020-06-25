#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct QueueEntry {
    int height;
    int shorterThan;
};

ostream& operator<<(ostream& os, const QueueEntry& qe) {
    os << "<" << qe.height << ", " << qe.shorterThan << ">";
    return os;
}

struct QueueEntryComparator {
    bool operator()(QueueEntry const& q1, QueueEntry const& q2) {
        // an entry w/ a lower `shorterThan` will appear earlier in the queue
        return q1.shorterThan > q2.shorterThan;
    }
};

using AscendingQueueEntries =
    priority_queue<QueueEntry, vector<QueueEntry>, QueueEntryComparator>;

class Solution {
   public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<vector<int>> res;

        map<int, AscendingQueueEntries> sortedHeightMap;

        for (auto const pair : people) {
            QueueEntry qe = {.height = pair[0], .shorterThan = pair[1]};

            if (sortedHeightMap.find(qe.height) == sortedHeightMap.end()) {
                sortedHeightMap[qe.height] = AscendingQueueEntries();
            }

            sortedHeightMap.at(qe.height).push(qe);
        }

        for (auto rit = sortedHeightMap.rbegin(); rit != sortedHeightMap.rend();
             rit++) {
            while (!rit->second.empty()) {
                auto queueEntry = rit->second.top();
                rit->second.pop();

                auto insertEntry = {queueEntry.height, queueEntry.shorterThan};

                if (queueEntry.shorterThan >= res.size()) {
                    res.push_back(insertEntry);
                } else {
                    res.insert(res.begin() + queueEntry.shorterThan,
                               insertEntry);
                }
            }
        }

        return res;
    }
};

int main() {
    auto s = Solution();

    vector<vector<int>> people = {{7, 0}, {4, 4}, {7, 1},
                                  {5, 0}, {6, 1}, {5, 2}};
    s.reconstructQueue(people);
}