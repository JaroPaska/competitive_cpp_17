//
// Created by jaroslavp on 5/21/2022.
//

#pragma once

#include "base.h"

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