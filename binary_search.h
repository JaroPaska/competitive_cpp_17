#pragma once

template<class Fn, class T>
T binary_search(Fn is_left, T left, T right, T epsilon = 1) {
    while (right - left > epsilon) {
        T mid = (left + right) / 2;
        if (is_left(mid))
            left = mid;
        else
            right = mid;
    }
    return left;
}