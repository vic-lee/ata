#include <cmath>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

vector<bool> readInput() {
    int N, M;
    cin >> N >> M;
    vector<int> missingPlayers;
    for (int i = 0; i < M; i++) {
        int x;
        cin >> x;
        missingPlayers.push_back(x);
    }

    const int totalUserCount = pow(2, N);
    vector<bool> round(totalUserCount, true);

    for (auto &c : missingPlayers) round[c-1] = false;

    return round;
}

int calcWalkoverCount(vector<bool> &round) {
    int walkoverCount = 0;

    while (round.size() > 1) {
        vector<bool> nextRound(round.size() / 2, true);

        for (int i = 0; i < nextRound.size(); i++) {
            bool p1 = round[i*2];
            bool p2 = round[i*2+1];
            if ((p1 && !p2) || (!p1 && p2)) walkoverCount++;
            nextRound[i] = p1 || p2;
        }

        round = nextRound;
    }

    return walkoverCount;
}

int main() {
    auto round = readInput();
    int walkoverCount = calcWalkoverCount(round);
    printf("%d", walkoverCount);
}