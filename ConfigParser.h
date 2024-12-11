#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>

typedef std::tuple<std::string, std::vector<std::string>*> Config_arguments; //tuple 
																			//
																			//
class ConfigParser {
public:
	ConfigParser(std::string name);
	std::vector<Config_arguments>* Parse();
private:
	std::string FileName;
};