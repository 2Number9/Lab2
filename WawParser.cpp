#include "WawParser.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <filesystem>
//#include <istream>


WawParser::WawParser(std::string argument) : FileName(argument) {}

std::vector<int16_t> WawParser::Parse() {
	std::ifstream File(FileName, std::ios::binary);
	if (!(File.is_open())) {
		throw std::runtime_error("Error with opening Waw File");
	}
	Header = new (Waw_header);
	File.read(reinterpret_cast<char*> (Header), sizeof(Waw_header));
	int DataSize;
	DataSize = Header->SubChunk2Size;

	while (true) {
		std::unique_ptr <char[]> Junk(new char[DataSize + 4]);
		File.read(reinterpret_cast<char*> (Junk.get()), DataSize + 4);
		File.read(reinterpret_cast<char*> (&DataSize), sizeof(DataSize));
		if (static_cast<int> (File.tellg()) + DataSize == (Header->ChunkIdSize + 8))
			break;
	}
	std::vector<int16_t> data;
	data.resize(DataSize);
	File.read(reinterpret_cast<char*> (data.data()), DataSize);
	return data;
}