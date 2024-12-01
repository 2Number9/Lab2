#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "WawParser.h"

class WawWrite {
public:
	WawWrite(std::string FileName, Waw_header Header);
	void Write(std::vector<short int> Samples);
private:
	Waw_header Header;
	std::string FileName;
};
