#include "Factory.h"
#include <iostream>
#include <utility>

std_map Factory::converter_map;

std::unique_ptr<Converters::BaseConverter> Factory::CreateConverter(std::string name, std::vector<std::string> args) {
	auto cvt = converter_map.find(name);
	if (cvt == converter_map.end()) {
		return nullptr;
	} //find возвращает итератр
	return cvt->second(std::move(args)); //второй элемент map
}