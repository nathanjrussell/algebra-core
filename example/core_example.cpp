#include <iostream>
#include <string>
#include <algebra/core/core.hpp>

using namespace algebra;

struct WordDescriptor : AlgebraDescriptor {
    using generic_category = MonoidCategory;
};

struct Word {
    using parent_type = Word;
    using algebra = WordDescriptor;
    std::string value;

    Word combine(const Word& other) const {
        return {value + other.value};
    }

    static Word identity() {
        return {};
    }

    bool is_identity() const {
        return value.empty();
    }

    bool operator==(const Word&) const = default;
};

int main() {
    const Word word{"ab"};
    const Word repeated = repeat<GenericOperation>(word, 3);
    std::cout << repeated.value << '\n';
}
