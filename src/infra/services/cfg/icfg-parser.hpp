namespace infra::services::cfg {

template<class Cfgs>
class ICfgPaser {
public:
	auto run() -> Cfgs;
	auto is_changed() -> Cfgs;
};

}  // namespace infra::services::cfg
