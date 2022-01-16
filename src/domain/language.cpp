
#include "language.hpp"

namespace domain::language {

Language::Language(Name name): _name(name) {};

auto Language::operator==(Language const& right) const -> bool {
	return (_name == right.get_name());
};

auto Language::operator!=(Language const& right) const -> bool {
	return !(*this == right);
};


auto Language::get_name() const -> Name {
	return _name;
}
} // namespace domain::language
