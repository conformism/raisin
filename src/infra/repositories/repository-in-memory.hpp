#pragma once

#include "domain/cfg/cfg.hpp"
#include "domain/core/result.hpp"
#include "domain/core/types.hpp"
#include "domain/irepository.hpp"
#include "domain/program.hpp"

#include <memory>

namespace infra::repository {

class RespositoryInMemory : public domain::IRespository<domain::Program> {
public:
	auto write(domain::Program program) -> void override {
		_program = std::move(program);
	}

	[[nodiscard]] auto read() -> domain::Program* override {
		return &_program;
	}

private:
	domain::Program _program = domain::Program();
};
}  // namespace infra::repository
