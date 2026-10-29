#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <algebra/core/concepts.hpp>

namespace algebra {

constexpr bool is_prime(std::uint32_t value) {
    if (value < 2) {
        return false;
    }
    for (std::uint64_t divisor = 2; divisor * divisor <= value; ++divisor) {
        if (value % divisor == 0) {
            return false;
        }
    }
    return true;
}

constexpr std::uint64_t checked_power(std::uint64_t base, std::size_t exponent) {
    std::uint64_t result = 1;
    for (std::size_t i = 0; i < exponent; ++i) {
        if (base != 0 && result > std::numeric_limits<std::uint64_t>::max() / base) {
            throw std::overflow_error("Cardinality exceeds the supported integer range");
        }
        result *= base;
    }
    return result;
}

template<class Op, class T>
    requires MonoidElement<T, Op>
T repeat(const T& value, std::uint64_t count) {
    T result = operation<T, Op>::identity();
    for (std::uint64_t i = 0; i < count; ++i) {
        result = operation<T, Op>::apply(result, value);
    }
    return result;
}

template<class Op, class T>
    requires GroupElement<T, Op>
T repeat_signed(const T& value, std::int64_t count) {
    if (count >= 0) {
        return repeat<Op>(value, static_cast<std::uint64_t>(count));
    }
    const auto magnitude = static_cast<std::uint64_t>(-(count + 1)) + 1;
    return repeat<Op>(operation<T, Op>::inverse(value), magnitude);
}

template<class T, class Op>
    requires MonoidElement<T, Op>
bool identity_law(const T& a) {
    const T identity = operation<T, Op>::identity();
    return operation<T, Op>::apply(a, identity) == a &&
           operation<T, Op>::apply(identity, a) == a;
}

template<class T, class Op>
    requires MagmaElement<T, Op>
bool associative_law(const T& a, const T& b, const T& c) {
    const T left = operation<T, Op>::apply(operation<T, Op>::apply(a, b), c);
    const T right = operation<T, Op>::apply(a, operation<T, Op>::apply(b, c));
    return left == right;
}

template<RingElement T>
bool distributive_law(const T& a, const T& b, const T& c) {
    return a.multiply(b.add(c)) == a.multiply(b).add(a.multiply(c)) &&
           a.add(b).multiply(c) == a.multiply(c).add(b.multiply(c));
}

}
