#include <map>
#include <string>
#include <memory>
#include "Converters.h"

typedef std::map<std::string, std::unique_ptr<Converters::BaseConverter>(*) (std::vector<std::string>)> std_map;

template<typename T>
std::unique_ptr<Converters::BaseConverter> create(std::vector<std::string> args) {
	return std::make_unique <T>(args);
}

class Factory {
public:
	Factory() = default; //мы указываем коспилятору самостоятельно генерировать конструктор по умолчанию для класса Factory
	template<typename T>			//вызов static метода не связан с конкретным объектом класса, он вызывается для класса
	static bool RegisterConverter(std::string name); //static функция, не зависит от определенного объекта, работает с переменной static поле
	static std::unique_ptr<Converters::BaseConverter> CreateConverter(std::string name, std::vector<std::string> args); //static функция, по сути обычная функция, работает с полем static converter_map, которое общее для всего класса
private:
	static std_map converter_map; //static поле класса, хранит состояние всего класса, не зависит от конкретного
};								  //объекта класса

template<typename T>
bool Factory::RegisterConverter(std::string name) {
	auto cvt = converter_map.find(name);
	if (cvt != converter_map.end()) {
		return false;
	}
	converter_map.insert(std::make_pair( name, &create <T>));
	return true;
}

