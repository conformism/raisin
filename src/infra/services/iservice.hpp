namespace infra::services {

template<typename Result>
class IService {
public:
	virtual auto run() -> Result = 0;
};

}  // namespace infra::services
