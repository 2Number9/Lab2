#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "WawParser.h"

class WawWrite {
public:
	WawWrite(std::string FileName, Waw_header Header);
	void Write(const std::vector<int16_t> &Samples);
private:
	Waw_header Header;
	std::string FileName;
};