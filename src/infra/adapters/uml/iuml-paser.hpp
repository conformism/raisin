namespace infra::adapters::cfg {

template<class Cfgs>
class ICfgPaser {
public:
	auto run() -> Cfgs;
	auto is_changed() -> Cfgs;
};

}  // namespace infra::adapters::cfg
