#include "ConfigParser.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

ConfigParser::ConfigParser(std::string argument) : FileName(argument) {
	//std::cout << this->FileName << std::endl;
}

std::vector<Config_arguments> ConfigParser::Parse() {
	
	std::ifstream File(FileName);
	//std::cout << FileName << std::endl;
	if (!File.is_open())
		throw std::runtime_error("Enable to open Config File");

	
	std::vector<Config_arguments> parsed_config;
	std::string line;
	while (std::getline(File, line)) {
		std::istringstream arg(line); //для него мы подключили <sstream>
		std::string element;
		std::vector<std::string> args;
		//std::cout << "aboba" << std::endl;
		char flag = 1;
		while (flag && std::getline(arg, element, ' ')) { //arg становится входным потоком, ' ' - разделителем
			if (element[0] == char(35))
				flag = 0;
			else {
				std::cout << element << " ";
				args.push_back(element);
			}
		}
		//std::cout << std::endl;
		//if (args.empty())
			//throw std::runtime_error("Empty config line");
		if (!flag)
			std::cout << "Nasrali" << std::endl;
		else {
			std::string converter_name = args[0];
			args.erase(args.begin());
			Config_arguments tuple(converter_name, args);
			parsed_config.push_back(tuple);
			std::string x = std::get<0>(tuple);
			//std::cout << "x[0] == " << x << std::endl;
			//std::cout << "tuple[0] == " << std::get<0>(tuple) << std::endl;
			//std::cout << "tuple[1] == " << std::get<1>(tuple)[0] << std::endl;
			//std::cout << "tuple[2] == " << std::get<1>(tuple)[1] << std::endl;
		}
	}
	return parsed_config;
}
