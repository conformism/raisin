namespace infra::services {

template<class Result>
class IService {
public:
	auto run() -> Result;
};

}  // namespace infra::services
