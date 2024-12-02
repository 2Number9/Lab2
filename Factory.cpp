#include "Factory.h"
#include <iostream>
#include <utility>

std_map Factory::converter_map;

std::unique_ptr<Converters::BaseConverter> Factory::CreateConverter(std::string name, std::vector<std::string> args) {
	std::cout << "name == " << name << std::endl;
	auto cvt = converter_map.find(name);
	if (cvt == converter_map.end()) {
		std::cout << "Hueta" << std::endl;
		return nullptr;
	}
	return cvt->second(std::move(args));
}