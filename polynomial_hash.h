//
// Created by jaroslavp on 5/21/2022.
//

#pragma once

#include "number_theory.h"

class Hash {
public:
    Hash(long long value, int size) : value_(value), size_(size) {}

    [[nodiscard]] Hash push_back(const Hash& h) const {
        return Hash(mod(mod_mul(value_, power(h.size_), M) + h.value_, M), size_ + h.size_);
    }

    [[nodiscard]] Hash push_front(const Hash& h) const {
        return h.push_back(*this);
    }

    static constexpr long long P = 269;
    static constexpr long long M = 1'000'000'000'000'000'009;

private:
    [[nodiscard]] static long long power(int exponent) {
        static std::vector<long long> powers{1};
        while (powers.size() <= exponent)
            powers.emplace_back(mod_mul(P, powers.back(), M));
        return powers[exponent];
    }

    long long value_ = 0;
    int size_ = 0;
};