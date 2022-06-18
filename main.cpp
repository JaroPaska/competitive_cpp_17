//
// Created by jaroslavp on 5/13/2022.
//

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

constexpr bool endl = false; // used to discourage use of endl
constexpr char newl = '\n';  // use newl instead

int main() {
#ifdef SYNC_IO
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    cout << setprecision(numeric_limits<long double>::max_digits10) << fixed;
    cout << boolalpha;

    list<int> l(3);
    cin >> l;

    LOG(l);
}
