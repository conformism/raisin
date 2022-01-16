#pragma once

#include "domain/core/types.hpp"
// #include <array>

namespace domain::language {

enum class Name {
    C,
    CPP,
    JS,
    TS,
    BASH,
    JAVA,
    HASKEL,
};

enum class Paradigm {
    FUNCTIONAL,
    OBJECT,
    META,
};

class Language: public domain::core::Value<Language> {
public:
	explicit Language(Name name);
	auto operator==(Language const& right) const -> bool override;
	auto operator!=(Language const& right) const -> bool override;
	[[nodiscard]]
    auto get_name() const -> Name;
    [[nodiscard]]
    virtual auto has_paradigm(Paradigm paradigm) const -> bool = 0;
private:
    Name const _name;
};

template<
    Name N,
    Paradigm const ... P
>
class SupportedLanguage:  public Language {
public:
	SupportedLanguage(): Language(N) {};
    [[nodiscard]]
    auto has_paradigm(Paradigm paradigm) const -> bool override {
        return ((paradigm == P) || ...);
    }
private:
};

using C = SupportedLanguage<Name::C, Paradigm::FUNCTIONAL, Paradigm::OBJECT>;
using Cpp = SupportedLanguage<Name::CPP, Paradigm::FUNCTIONAL, Paradigm::OBJECT>;
using Js = SupportedLanguage<Name::JS, Paradigm::FUNCTIONAL, Paradigm::OBJECT>;
using Java = SupportedLanguage<Name::JS, Paradigm::OBJECT>;

} // namespace domain::language
