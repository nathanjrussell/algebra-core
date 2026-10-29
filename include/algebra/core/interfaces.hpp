#pragma once

#include <algebra/core/descriptors.hpp>

namespace algebra::interfaces {

template<class E>
class CarrierSet {
public:
    virtual ~CarrierSet() = default;
    virtual bool contains(const E& value) const = 0;
    virtual bool equal(const E& a, const E& b) const = 0;
};

template<class E, class Op = GenericOperation>
class Magma : public virtual CarrierSet<E> {
public:
    virtual E combine(Op, const E& a, const E& b) const = 0;
};

template<class E, class Op = GenericOperation>
class SemiGroup : public virtual Magma<E, Op> {};

template<class E, class Op = GenericOperation>
class Monoid : public virtual SemiGroup<E, Op> {
public:
    virtual E identity(Op) const = 0;
};

template<class E, class Op = GenericOperation>
class Group : public virtual Monoid<E, Op> {
public:
    virtual E inverse(Op, const E& value) const = 0;
};

template<class E, class Op = GenericOperation>
class AbelianGroup : public virtual Group<E, Op> {};

template<class E, class Op = GenericOperation>
class CyclicGroup : public virtual AbelianGroup<E, Op> {
public:
    virtual E generator() const = 0;
};

template<class E>
class Rng : public virtual AbelianGroup<E, Addition>,
            public virtual SemiGroup<E, Multiplication> {};

template<class E>
class Ring : public virtual Rng<E>,
             public virtual Monoid<E, Multiplication> {
public:
    const AbelianGroup<E, Addition>& additive_group() const {
        return *this;
    }

    const Monoid<E, Multiplication>& multiplicative_monoid() const {
        return *this;
    }

    E add(const E& a, const E& b) const {
        return additive_group().combine(Addition{}, a, b);
    }

    E multiply(const E& a, const E& b) const {
        return multiplicative_monoid().combine(Multiplication{}, a, b);
    }
};

template<class E>
class CommutativeRing : public virtual Ring<E> {};

template<class E>
class IntegralDomain : public virtual CommutativeRing<E> {};

template<class E>
class DivisionRing : public virtual Ring<E> {
public:
    virtual E reciprocal(const E& value) const = 0;
};

template<class E>
class Field : public virtual IntegralDomain<E>,
              public virtual DivisionRing<E> {};

}
