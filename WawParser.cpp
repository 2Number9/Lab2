#include "WawParser.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <filesystem>
//#include <istream>


WawParser::WawParser(std::string argument) : FileName(argument) {}

std::vector<int16_t>* WawParser::Parse() {
	std::ifstream File(FileName, std::ios::binary);
	if (!(File.is_open())) {
		throw std::runtime_error("Error with opening Waw File");
	}
	Header = new (Waw_header);
	File.read(reinterpret_cast<char*> (Header), sizeof(Waw_header));
	int DataSize;
	DataSize = Header->SubChunk2Size;
	//while (true) {
		//if (sizeof(*Header) + File.tellg() + DataSize == 
		std::unique_ptr <char[]> Junk(new char[DataSize]);
		File.read(reinterpret_cast<char*> (Junk.get()), Header->SubChunk2Size + 4);
	//}
	File.read(reinterpret_cast<char*> (&DataSize), sizeof(DataSize));

	std::vector<int16_t>* data = new std::vector<int16_t>; //
	(*data).resize(DataSize);
	File.read(reinterpret_cast<char*> ((*data).data()), DataSize);

	return data;
}