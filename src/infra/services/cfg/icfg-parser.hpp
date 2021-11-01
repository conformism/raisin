#include "infra/services/iservice.hpp"

namespace infra::services::cfg {

template<class Cfgs>
class ICfgParser : IService<Cfgs> {
public:
	auto run() -> Cfgs;
};

}  // namespace infra::services::cfg
