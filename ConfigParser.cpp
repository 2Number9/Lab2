#include "ConfigParser.h"
#include <string>
#include <vector>
#include <algorithm>

ConfigParser::ConfigParser(std::string argument) : FileName(argument) {
}

std::vector<Config_arguments> ConfigParser::Parse() {
	
	std::ifstream File(FileName);
	if (!File.is_open())
		throw std::runtime_error("Enable to open Config File");

	
	std::vector<Config_arguments> parsed_config;
	std::string line;
	while (std::getline(File, line)) {
		std::istringstream arg(line); 
		std::string element;
		std::vector<std::string> args;
		char flag = 0;
		while (std::getline(arg, element, ' ')) { //arg становится входным потоком, ' ' - разделителем
			if (element[0] == (char)35) //char (35) == #
				flag = 1;
			args.push_back(element);
		}
		if (!flag) {
			std::string converter_name = args[0];
			args.erase(args.begin());
			Config_arguments tuple(converter_name, args);
			parsed_config.push_back(tuple);
		}
	}
	return parsed_config;
}
