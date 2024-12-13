#include <map>
#include <string>
#include <memory>
#include "Converters.h"

class Factory {
public:
	Factory() = default;
	static std::unique_ptr<Converters::BaseConverter> CreateConverter(std::string name, const std::vector<std::string>& args);
};
