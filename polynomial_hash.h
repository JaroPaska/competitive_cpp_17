//
// Created by jaroslavp on 5/21/2022.
//

#pragma once

#include "number_theory.h"

class Hash {
public:
    constexpr Hash(long long value, int size) : value_(value), size_(size) {}

    [[nodiscard]] constexpr Hash extend(const Hash& rhs) const {
        return Hash(mod(mod_mul(value_, power(rhs.size_), M) + rhs.value_, M), size_ + rhs.size_);
    }

    static constexpr long long P = 269;
    static constexpr long long M = 1e18 + 9;

private:
    static long long power(int exponent) {
        static std::vector<long long> powers{1};
        while (powers.size() <= exponent)
            powers.emplace_back(P * powers.back() % M);
        return powers[exponent];
    }

    long long value_ = 0;
    int size_ = 0;
};

template<long long P, long long M>
struct PolynomialHash {
    long long value;
    int size;

    static long long p_power(int exponent) {
        static std::vector<long long> powers{1};
        while (powers.size() <= exponent)
            powers.emplace_back(P * powers.back() % M);
        return powers[exponent];
    }
};

template<long long P, long long M>
PolynomialHash<P, M> operator+=(PolynomialHash<P, M>& lhs, const PolynomialHash<P, M>& rhs) {
    lhs.value = (PolynomialHash<P, M>::p_power(rhs.size) * lhs.value + rhs.value) % M;
    lhs.size += rhs.size;
    return lhs;
}

template<long long P, long long M>
PolynomialHash<P, M> operator-=(PolynomialHash<P, M>& lhs, const PolynomialHash<P, M>& rhs) {
    lhs.value = (PolynomialHash<P, M>::p_power(rhs.size) * lhs.value + rhs.value) % M;
    lhs.size += rhs.size;
    return lhs;
}