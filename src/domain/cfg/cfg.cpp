#include "./cfg.hpp"
#include "../core/guard.hpp"
#include <cstddef>
#include <memory>
#include <utility>

namespace domain::cfg {

auto Cfg::get_block_by_id(Uuid uuid) const
	-> result::Result<Block*, Failures::INVALID_UUID, Failures::NOT_INSIDE> {
	return _blocks.at(uuid);
}
auto Cfg::get_scope_by_id(Uuid uuid) const
	-> result::Result<Statement*, Failures::INVALID_UUID, Failures::NOT_INSIDE> {
	return _statements.at(uuid);
}

}  // namespace domain::cfg
