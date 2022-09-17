#pragma once

#include <iostream>

struct Rational {
    long long num{0};
    long long den{1};

    constexpr Rational() = default;
    constexpr Rational(long long n) : num(n) {}
    constexpr Rational(long long n, long long d) : num(n), den(d) {}

    operator long double() const {
        return num / static_cast<long double>(den);
    }

    constexpr Rational& operator+=(const Rational& rhs) {
        num *= rhs.den;
        num += rhs.num * den;
        den *= rhs.den;
        return *this;
    }

    constexpr Rational& operator-=(const Rational& rhs) {
        num *= rhs.den;
        num -= rhs.num * den;
        den *= rhs.den;
        return *this;
    }

    constexpr Rational& operator*=(const Rational& rhs) {
        num *= rhs.num;
        den *= rhs.den;
        return *this;
    }

    constexpr Rational& operator/=(const Rational& rhs) {
        num *= rhs.den;
        den *= rhs.num;
        return *this;
    }

    constexpr Rational operator+() const {
        return {num, den};
    }

    constexpr Rational operator-() const {
        return {-num, den};
    }
};

constexpr Rational operator+(Rational lhs, const Rational& rhs) {
    return lhs += rhs;
}

constexpr Rational operator-(Rational lhs, const Rational& rhs) {
    return lhs -= rhs;
}

constexpr Rational operator*(Rational lhs, const Rational& rhs) {
    return lhs *= rhs;
}

constexpr Rational operator/(Rational lhs, const Rational& rhs) {
    return lhs /= rhs;
}

constexpr bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.num * rhs.den == rhs.num * lhs.den;
}

constexpr bool operator!=(const Rational& lhs, const Rational& rhs) {
    return lhs.num * rhs.den != rhs.num * lhs.den;
}

constexpr bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.num * rhs.den < rhs.num * lhs.den;
}

constexpr bool operator>(const Rational& lhs, const Rational& rhs) {
    return lhs.num * rhs.den > rhs.num * lhs.den;
}

constexpr bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs.num * rhs.den <= rhs.num * lhs.den;
}

constexpr bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs.num * rhs.den >= rhs.num * lhs.den;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.num << '/' << r.den;
}
