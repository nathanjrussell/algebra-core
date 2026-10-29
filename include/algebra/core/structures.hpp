#pragma once

#include <type_traits>
#include <algebra/core/concepts.hpp>
#include <algebra/core/interfaces.hpp>

namespace algebra {

template<class E>
class AdditiveGroupStructure : public virtual interfaces::AbelianGroup<E, Addition> {
public:
    bool contains(const E&) const override {
        return true;
    }

    bool equal(const E& a, const E& b) const override {
        return a == b;
    }

    E combine(Addition, const E& a, const E& b) const override {
        return a.add(b);
    }

    E identity(Addition) const override {
        return E::zero();
    }

    E inverse(Addition, const E& a) const override {
        return a.negate();
    }
};

template<class E>
class CyclicGroupStructure : public AdditiveGroupStructure<E>,
                             public virtual interfaces::CyclicGroup<E, Addition> {
public:
    E generator() const override {
        return E::generator();
    }
};

template<class E>
class RingStructure : public AdditiveGroupStructure<E>,
                      public virtual interfaces::Ring<E> {
public:
    using AdditiveGroupStructure<E>::combine;
    using AdditiveGroupStructure<E>::identity;

    E combine(Multiplication, const E& a, const E& b) const override {
        return a.multiply(b);
    }

    E identity(Multiplication) const override {
        return E::one();
    }
};

template<class E>
class CommutativeRingStructure : public RingStructure<E>,
                                 public virtual interfaces::CommutativeRing<E> {};

template<class E>
class IntegralDomainStructure : public CommutativeRingStructure<E>,
                                public virtual interfaces::IntegralDomain<E> {};

template<class E>
class FieldStructure : public RingStructure<E>,
                       public virtual interfaces::Field<E> {
public:
    E reciprocal(const E& a) const override {
        return a.reciprocal();
    }
};

template<class E>
using RingStructureFor = std::conditional_t<IntegralDomainElement<E>,
    IntegralDomainStructure<E>, std::conditional_t<CommutativeRingElement<E>,
        CommutativeRingStructure<E>, RingStructure<E>>>;

template<class E>
class MultiplicativeGroupStructure : public virtual interfaces::Group<E, Multiplication> {
public:
    bool contains(const E&) const override {
        return true;
    }

    bool equal(const E& a, const E& b) const override {
        return a == b;
    }

    E combine(Multiplication, const E& a, const E& b) const override {
        return a.multiply(b);
    }

    E identity(Multiplication) const override {
        return E::one();
    }

    E inverse(Multiplication, const E& a) const override {
        return a.reciprocal();
    }
};

template<class E>
class MultiplicativeAbelianGroupStructure : public MultiplicativeGroupStructure<E>,
    public virtual interfaces::AbelianGroup<E, Multiplication> {};

}
