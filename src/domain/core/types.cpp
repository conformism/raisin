#include "types.hpp"

namespace domain::core {

auto create_uuid() -> Uuid {
	std::stringstream string_stream;
	for (auto i = 0; i < UUID_LENGTH; i++) {
		std::random_device random_dev;
		std::mt19937 gen(random_dev());
		constexpr uint left_limit_int_distrib = 0;
		constexpr uint right_limit_int_distrib = 255;
		std::uniform_int_distribution<> distrib(left_limit_int_distrib, right_limit_int_distrib);
		const auto random_char = distrib(gen);
		std::stringstream hexstream;
		hexstream << std::hex << random_char;
		auto hex = hexstream.str();
		string_stream << (hex.length() < 2 ? '0' + hex : hex);
	}
	return string_stream.str();
}

Entity::Entity(Uuid uuid) : _uuid(std::move(uuid)){};

auto Entity::get_uuid() const -> Uuid {
	return _uuid;
}

}  // namespace domain::core
