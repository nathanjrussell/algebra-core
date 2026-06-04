#pragma once

namespace njr::algebra {

template<class Derived>
struct AdditiveOperators {
    friend Derived operator+(const Derived& a, const Derived& b) {
        return a.add(b);
    }

    friend Derived operator-(const Derived& a, const Derived& b) {
        return a.add(b.negate());
    }

    friend Derived operator-(const Derived& a) {
        return a.negate();
    }

    Derived& operator+=(const Derived& b) {
        auto& a = static_cast<Derived&>(*this);
        a = a.add(b);
        return a;
    }

    Derived& operator-=(const Derived& b) {
        auto& a = static_cast<Derived&>(*this);
        a = a.add(b.negate());
        return a;
    }
};

template<class Derived>
struct MultiplicativeOperators {
    friend Derived operator*(const Derived& a, const Derived& b) {
        return a.multiply(b);
    }

    Derived& operator*=(const Derived& b) {
        auto& a = static_cast<Derived&>(*this);
        a = a.multiply(b);
        return a;
    }
};

template<class Derived>
struct DivisionOperators {
    friend Derived operator/(const Derived& a, const Derived& b) {
        return a.multiply(b.reciprocal());
    }

    Derived& operator/=(const Derived& b) {
        auto& a = static_cast<Derived&>(*this);
        a = a.multiply(b.reciprocal());
        return a;
    }
};

}
