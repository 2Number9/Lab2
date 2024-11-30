#include "ConfigParser.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
	std::cout << static_cast<std::string> (argv[1]) << std::endl;
	ConfigParser config(static_cast<std::string> (argv[1]));

	typedef std::tuple<std::string, std::vector<std::string>> data;
	std::vector<data> parsed_config;

	parsed_config = config.Parse();


	return 0;
}