#include "base.h"

#define F first
#define S second
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define ROF(i, a, b) for (int i = a - 1; i >= b; i--)
#define all(x) (x).begin(), (x).end()
#define PB push_back
#define POP pop_back
#define MP make_pair
#define MT make_tuple

using namespace std;

using pi = pair<int, int>;
using vi = vector<int>;
using vpi = vector<pi>;
using vvi = vector<vi>;
using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
using vvll = vector<vll>;
using ld = long double;
using ull = unsigned long long;
using vc = vector<char>;
using vvc = vector<vc>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

template<class T>
using max_heap = priority_queue<T>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, p;
    cin >> n >> m >> p;

    vector<int> free_seats(n, m);

    int blocks = sqrt(n);
    int block_size = (n + blocks - 1) / blocks;

    vector<int> block_minimums(blocks, m);
    vector<int> lazy_subtract(blocks, 0);
    while (p--) {
        LOG(free_seats);
        LOG(block_minimums);
        LOG(lazy_subtract);
        int x, y, z;
        cin >> x >> y >> z;

        auto is_block_start = [&](int index) {
            return index % block_size == 0;
        };
        auto block_from_index = [&](int index) {
            return index / block_size;
        };
        auto index_from_block = [&](int block) {
            return block * block_size;
        };
        auto propagate = [&](int block) {
            int block_start = index_from_block(block);
            int block_end = min(index_from_block(block + 1), n);
            for (int i = block_start; i < block_end; ++i)
                free_seats[i] -= lazy_subtract[block];
            lazy_subtract[block] = 0;
        };

        int index = y;
        int minimum = INT_MAX;

        if (index < z && !is_block_start(index))
            propagate(block_from_index(index));
        while (index < z && !is_block_start(index)) {
            minimum = min(minimum, free_seats[index]);
            ++index;
        }
        while (block_from_index(index) < block_from_index(z)) {
            int block = block_from_index(index);
            minimum = min(minimum, block_minimums[block]);
            index += block_size;
        }
        if (index < z)
            propagate(block_from_index(index));
        while (index < z) {
            minimum = min(minimum, free_seats[index]);
            ++index;
        }

        if (minimum < x) {
            cout << "odmietnuta\n";
            continue;
        }

        cout << "prijata\n";
        index = y;

        while (index < z && !is_block_start(index)) {
            int block = block_from_index(index);
            free_seats[index] -= x;
            block_minimums[block] = min(block_minimums[block], free_seats[index]);
            ++index;
        }
        while (block_from_index(index) < block_from_index(z)) {
            int block = block_from_index(index);
            block_minimums[block] -= x;
            lazy_subtract[block] += x;
            index += block_size;
        }
        while (index < z) {
            int block = block_from_index(index);
            free_seats[index] -= x;
            block_minimums[block] = min(block_minimums[block], free_seats[index]);
            ++index;
        }
    }
    LOG(free_seats);
    LOG(block_minimums);
    LOG(lazy_subtract);
}
