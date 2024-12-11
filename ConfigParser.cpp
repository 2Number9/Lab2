#include "ConfigParser.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

ConfigParser::ConfigParser(std::string name) : FileName(name) {
}

std::vector<Config_arguments>* ConfigParser::Parse() {

	std::ifstream File(FileName);
	if (!File.is_open())
		throw std::runtime_error("Enable to open Config File");


	std::vector<Config_arguments>* parsed_config;
	parsed_config = new std::vector<Config_arguments>;
	std::string line = "";
	while (std::getline(File, line)) {
		std::istringstream arg(line);
		std::string element;
		std::vector<std::string>* args;
		args = new std::vector<std::string>;
		char flag = 0;
		while (std::getline(arg, element, ' ')) { //arg 
			if (element[0] == '#') {//char (35) == #
				//std::cout << "gay" << std::endl;
				flag = 1;
				break;
			}
			else {
				(*args).push_back(element);
				//std::cout << element << std::endl;
			}
		}
		if (!flag) {
			std::string converter_name = (*args)[0];
			//std::cout << "convert_name == " << converter_name << std::endl;
			(*args).erase((*args).begin());
			if (((*args)[0])[0] == '$') {
				(*args)[0].erase(0, 1);
			}
			std::cout << "args[0] == " << (*args)[0] << std::endl;
			Config_arguments tupix = make_tuple(converter_name, args);
			std::cout << "converter_name == " << std::get<0>(tupix) << std::endl;
			(*parsed_config).push_back(tupix);

		}
	}
	std::cout << "parsed_config[3][0] == " << std::get<0>((*parsed_config)[3]) << std::endl;
	std::cout << "spizdili.size() == " << (*parsed_config).size() << std::endl;
	return parsed_config;
}