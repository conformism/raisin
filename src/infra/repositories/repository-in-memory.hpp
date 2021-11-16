#pragma once

#include "domain/cfg/cfg.hpp"
#include "domain/core/result.hpp"
#include "domain/core/types.hpp"
#include "domain/irepository.hpp"
#include "domain/program.hpp"
#include <memory>

namespace infra::repository {

template<class Cfg, class CfgParserService>
class RespositoryInMemory : public domain::IRespository<domain::Program> {
public:
	using Cfgs = typename domain::IRespository<Cfg>::Cfgs;
	explicit RespositoryInMemory(CfgParserService* cfg_parser_service)
		: _cfg_parser_service(cfg_parser_service){};

	auto write(domain::Program program) -> void override {
		_program = std::make_unique<domain::Program>(program);
	}

	[[nodiscard]] auto read() -> domain::Program* override {
		return _program.get();
	}

	// NOLINTNEXTLINE(misc-unused-parameters)
	[[nodiscard]] auto read_cfg_by_id(domain::core::Uuid uuid) -> domain::
		Result<domain::Program*, Failures::INVALID_UUID, Failures::NO_RESOURCES> override {
		return domain::core::result::
			success<domain::Program*, Failures::INVALID_UUID, Failures::NO_RESOURCES>(
				_program.get());
	}

private:
	std::unique_ptr<domain::Program> _program =
		std::make_unique<domain::Program>(domain::Program());
	CfgParserService* _cfg_parser_service;
};
}  // namespace infra::repository
