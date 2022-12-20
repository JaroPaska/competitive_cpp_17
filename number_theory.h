#pragma once

#include "base.h"

template<class T>
T extended_euclid(T a, T b, T& x, T& y) {
    std::pair<T, T> r{a, b};
    std::pair<T, T> s{1, 0};
    std::pair<T, T> t{0, 1};
    while (r.second) {
        T q = r.first / r.second;
        r = { r.second, r.first - q * r.second };
        s = { s.second, s.first - q * s.second };
        t = { t.second, t.first - q * t.second };
    }
    x = s.first;
    y = t.first;
    return r.first;
}

inline int trailing_zeros(long long n) {
    if (!n)
        return 0;
#ifdef _MSC_VER
    unsigned long z = 0;
    _BitScanForward64(&z, n);
    return z;
#else
    return __builtin_ctzll(n);
#endif
}

inline long long mod_mul(long long a, long long b, long long m = MOD) {
#ifdef _MSC_VER
    unsigned long long h, l, r;
    l = _umul128(llabs(a), llabs(b), &h);
    _udiv128(h, l, m, &r);
    return sgn(a) * sgn(b) >= 0 ? r : m - r;
#else
    long long r = a * static_cast<__int128>(b) % m;
    return r >= 0 ? r : r + m;
#endif
}
 
long long mod_exp(long long base, long long exp, long long m = MOD) {
    if (!exp)
        return mod(1, m);
    long long result = mod(1, m);
    base = mod(base, m);
    while (exp > 0) {
        if (exp & 1)
            result = mod_mul(result, base, m);
        exp >>= 1;
        base = mod_mul(base, base, m);
    }
    return result;
}

long long mod_inv(long long a, long long m = MOD) {
    return mod_exp(a, m - 2, m);
}

long long mod_div(long long a, long long b, long long m = MOD) {
    return mod(a * mod_inv(b, m), m);
}

long long factorial(size_t n, long long m = MOD) {
    static hash_map<long long, std::vector<long long>> memo;
    auto it = memo.find(m);
    if (it == memo.end())
        it = memo.insert({m, {mod(1, m)}}).first;
    auto& f = it->second;
    while (n >= f.size())
        f.push_back(mod(f.back() * f.size(), m));
    return f[n];
}

long long legendre(long long n, long long p = MOD) {
    long long x = n / p;
    long long sum = 0;
    while (x) {
        sum += x;
        x /= p;
    }
    return sum;
}

long long nck(size_t n, size_t k, long long p = MOD) {
    if (k > n || legendre(n, p) > legendre(k, p) + legendre(n - k, p))
        return 0;
    static hash_map<long long, std::vector<long long>> memo;
    auto it = memo.find(p);
    if (it == memo.end())
        it = memo.insert({p, {mod(1, p)}}).first;
    auto& f = it->second;
    while (n >= f.size()) {
        auto x = f.size();
        while (!(x % p))
            x /= p;
        f.push_back(mod(x * f.back(), p));
    }
    return mod_div(f[n], mod(f[k] * f[n - k], p), p);
}

std::vector<int> gpf;
void sieve(int n) {
    gpf.assign(n + 1, 0);
    gpf[0] = gpf[1] = -1;
    for (int i = 2; i <= n; i++) {
        if (gpf[i])
            continue;
        gpf[i] = i;
        for (int j = 2 * i; j <= n; j += i)
            gpf[j] = i;
    }
}

bool miller_test(long long n, long long d, long long r, long long a) {
    long long x = mod_exp(a, d, n);
    if (x == 1 || x == n - 1)
        return true;
    for (int i = 0; i < r - 1; i++) {
        x = mod_mul(x, x, n);
        if (x == n - 1)
            return true;
    }
    return false;
}

bool is_prime(long long n) {
    if (n < gpf.size())
        return gpf[n] == n;
    if (n < 2)
        return false;
    if (n < 4)
        return true;
    long long r = trailing_zeros(n - 1);
    long long d = (n - 1) >> r;
    static std::vector<long long> BASES{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }; 
    for (int i = 0; i < BASES.size() && BASES[i] <= n - 2; i++)
        if (!miller_test(n, d, r, BASES[i]))
            return false;
    return true;
}
 
long long pollard_rho(long long n) {
    for (long long sum = 3; sum <= n; ++sum)
        for (long long c = 1; sum - c >= 2; ++c) {
            auto g = [c, n](long long x) { return mod(mod_mul(x, x, n) + c, n); };
            long long x = sum - c;
            long long y = x;
            do {
                x = g(x);
                y = g(g(y));
                long long p = std::gcd(llabs(x - y), n);
                if (p > 1 && p < n)
                    return p;
            } while (x != y);
        }
    throw std::invalid_argument("no divisor found");
}
 
hash_map<long long, long long> factorize(long long n) {
    if (n < gpf.size()) {
        hash_map<long long, long long> m;
        while (n > 1) {
            m[gpf[n]]++;
            n /= gpf[n];
        }
        return m;
    }

    int twos = trailing_zeros(n);
    std::vector<long long> factors(twos, 2), st{n >> twos};
    while (!st.empty() && st.back() > 1) {
        long long x = st.back();
        st.pop_back();
        if (is_prime(x))
            factors.push_back(x);
        else {
            long long p = pollard_rho(x);
            long long q = x / p;
            st.push_back(p);
            st.push_back(q);
        }
    }
    hash_map<long long, long long> m;
    for (const auto& factor : factors)
        ++m[factor];
    return m;
}