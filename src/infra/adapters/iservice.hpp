namespace infra::adapters {

template<typename Result>
class IAdapter {
public:
	virtual auto run() -> Result = 0;
};

}  // namespace infra::adapters
