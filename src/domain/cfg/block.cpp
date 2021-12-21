#include "domain/core/types.hpp"
#include <string>
#include <utility>

#include "./block.hpp"

using namespace std;

namespace domain::cfg {

Block::Block(Kind kind)
: _kind(kind)
, _scope(nullptr)
{}

auto Block::is_entry() const -> bool {
	return _precedents.empty();
}

auto Block::is_exit() const -> bool {
	return _successors.empty();
}

auto Block::get_text() const -> std::string const* {
	return &_text;
}

/*
auto Block::set_text(std::string text)
-> result::Result<std::string, Failures::CANT_HAVE_ZERO_LENGTH, Failures::ALREADY_SETTED>
{
	auto const size_result = guard::is_non_zero_length(text);
	if(size_result.is_failure()) {
		return size_result.set_failures<Failures::CANT_HAVE_ZERO_LENGTH, Failures::ALREADY_SETTED>().value();
	}

	if(text == _text) {
		return result::failure<
			std::string,
			Failures::ALREADY_SETTED,
			Failures::CANT_HAVE_ZERO_LENGTH,
			Failures::ALREADY_SETTED>();
	}

	_text = text;
	return result::success<
		std::string,
		Failures::CANT_HAVE_ZERO_LENGTH,
		Failures::ALREADY_SETTED>(text);

}
*/

auto Block::get_successors() const -> Aggregator<Block> const* {
	return &_successors;
}

auto Block::get_precedents() const -> Aggregator<Block> const* {
	return &_precedents;
}
}  // namespace domain::cfg
