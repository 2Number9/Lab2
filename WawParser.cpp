#include "WawParser.h"
#include <fstream>
#include <iostream>


WawParser::WawParser(std::string argument) : FileName(argument) {

}

std::vector<short int> WawParser::Parse() {
	std::ifstream File(FileName);
	std::cout << FileName << std::endl;
	std::cout << "FileName.size() == " << FileName.length() << std::endl;
	std::cout << "File.is_open == " << File.is_open() << std::endl;
	if (!(File.is_open())) {
		std::cout << "Dolbaeb" << std::endl;
		throw std::runtime_error("Error with opening Waw File");

	}
	Header = new (Waw_header);
	File.read((char*) Header, sizeof(Waw_header)); //BLYA PROSTO PRAVILNO UKAZAT' PUT' CHEREZ ..
	std::cout << "Information in Header: ";
	std::cout << "ChunkId: " << (int) Header->ChunkId[0] << " " << (int) Header->ChunkId[1] << std::endl;
	//std::cout << "ChunkIdSize: " << Header->ChunkIdSize << std::endl;
	//std::cout << "Format: " << Header->Format << std::endl;

	std::cout << "Information in Header: "; std::cout << static_cast<short int> (Header->AudioFormat) << " " << Header->BitsPerSample << " " << Header->SubChunk2Size << std::endl;
	
	char* Samples = (char*) malloc (Header->SubChunk2Size);
	std::cout << "sizeof == " << sizeof(*Samples) << " " << sizeof(Samples) << std::endl;
	std::vector<short int> Data;
	Data.resize(Header->SubChunk2Size / 2);
	File.read((char*) &Data, Header->SubChunk2Size);
	std::cout << "Data[0] == " << *Data.begin() << std::endl;
	std::cout << "Data[1] == " << (int) Data[1] << std::endl;

	return Data;
}