#include <queue>

using namespace std;

template <typename T>
using MinQueue = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
using MaxQueue = priority_queue<T>;