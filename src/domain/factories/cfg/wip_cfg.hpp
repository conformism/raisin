#pragma once

#include "domain/factories/cfg/wip_block.hpp"
#include "domain/factories/cfg/wip_scope.hpp"
#include "domain/cfg/cfg.hpp"

namespace cfg {

//******************************************************************************
class WipCfg : public Cfg {
public:
	WipCfg(clang::ASTContext& _context, clang::Stmt const* _stmt);
};

} // namespace cfg
