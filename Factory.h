#include <map>
#include <string>
#include <memory>
#include "Converters.h"

typedef std::map<std::string, std::unique_ptr<Converters::BaseConverter>(*) (std::vector<std::string>*)> std_map;

template<typename T>
std::unique_ptr<Converters::BaseConverter> create(std::vector<std::string>* args) {
	return std::make_unique <T>(args);
}

class Factory {
public:
	Factory() = default;
	template<typename T>
	static bool RegisterConverter(std::string name);
	static std::unique_ptr<Converters::BaseConverter> CreateConverter(std::string name, std::vector<std::string>* args);
private:
	static std_map converter_map;
};

template<typename T>
bool Factory::RegisterConverter(std::string name) {
	auto cvt = converter_map.find(name);
	if (cvt != converter_map.end()) {
		return false;
	}
	converter_map.insert(std::make_pair(name, &create <T>));
	return true;
}