#include "WawParser.h"
#include <fstream>
#include <iostream>
#include <memory>


WawParser::WawParser(std::string argument) : FileName(argument) {}

std::vector<short int> WawParser::Parse() {
	std::ifstream File(FileName, std::ios::binary);
	if (!(File.is_open())) {
		throw std::runtime_error("Error with opening Waw File");
	}
	Header = new (Waw_header);
	File.read(reinterpret_cast<char*> (Header), sizeof(Waw_header));

	std::unique_ptr <char[]> Junk (new char[Header->SubChunk2Size+4]);
	File.read(reinterpret_cast<char*> (Junk.get()), Header->SubChunk2Size + 4);
	int DataSize;
	File.read(reinterpret_cast<char*> (&DataSize), sizeof(DataSize));
	std::vector<short int> data; //почему считываем DataSize элементов
	data.resize(DataSize);
	File.read(reinterpret_cast<char*> (data.data()), DataSize);
	
	return data;
}