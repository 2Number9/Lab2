#include "WawParser.h"
#include <fstream>
#include <iostream>


WawParser::WawParser(std::string argument) : FileName(argument) {}

std::vector<short int> WawParser::Parse() {
	std::ifstream File(FileName, std::ios::binary);
	if (!(File.is_open())) {
		throw std::runtime_error("Error with opening Waw File");
	}
	Header = new (Waw_header);
	File.read((char*) Header, sizeof(Waw_header));

	char* Junk = (char*)malloc(Header->SubChunk2Size + 4);
	File.read(Junk, sizeof(char) * (Header->SubChunk2Size + 4));

	int DataSize;
	File.read(reinterpret_cast<char*> (&DataSize), sizeof(DataSize));
	std::vector<short int> data; //почему считываем DataSize элементов
	data.resize(DataSize);
	File.read((char*) data.data(), DataSize);
	
	free(Junk);
	return data;
}