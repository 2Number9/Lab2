#include "WawParser.h"
#include <fstream>
#include <iostream>


WawParser::WawParser(std::string argument) : FileName(argument) {

}

std::vector<short int> WawParser::Parse() {
	std::ifstream File(FileName, std::ios::binary);
	//File.seekg(0, std::ios::end);
	//std::cout << "File.size == " << File.tellg() << std::endl;
	//std::cout << FileName << std::endl;
	//std::cout << "FileName.size() == " << FileName.length() << std::endl;
	//std::cout << "File.is_open == " << File.is_open() << std::endl;
	if (!(File.is_open())) {
		std::cout << "Dolbaeb" << std::endl;
		throw std::runtime_error("Error with opening Waw File");
	}
	Header = new (Waw_header);
	File.read((char*) Header, sizeof(Waw_header)); //BLYA PROSTO PRAVILNO UKAZAT' PUT' CHEREZ ..
	//std::cout << "Information in Header: ";
	//std::cout << "ChunkId: " << (int) Header->ChunkId[0] << " " << (int) Header->ChunkId[1] << std::endl;
	//std::cout << "ChunkIdSize: " << Header->ChunkIdSize << std::endl;
	//std::cout << "Format: " << Header->Format << std::endl;

	std::cout << "Information in Header: "; std::cout <<  (Header->AudioFormat) << " " << Header->BitsPerSample << " " << Header->SubChunk2Size << std::endl;
	
	//char* Samples = (char*) malloc (Header->SubChunk2Size);
	
	char* Junk = (char*)malloc(Header->SubChunk2Size + 4);
	File.read(Junk, sizeof(char) * (Header->SubChunk2Size + 4));

	int DataSize;
	File.read(reinterpret_cast<char*> (&DataSize), sizeof(DataSize));
	std::cout << "DataSize == " << DataSize << std::endl;
	std::vector<short int> data;
	data.resize(DataSize);
	File.read((char*) data.data(), DataSize); //data.data() возвращает указатель на первый элемент внутреннего массива в векторе
	
	free(Junk);
	return data;


	//std::cout << "sizeof == " << sizeof(*Samples) << " " << sizeof(Samples) << std::endl;
	/*std::vector<short int> Data;
	Data.resize(Header->SubChunk2Size / 2);
	std::cout << "Data.size() == " << Data.size() << std::endl;
	/*for (int i = 0; i < Header->SubChunk2Size; i++) {
		File.read((char*)(&Data[(i/2) + (i % 2)]), 1);
		std::cout << "Sample[" << (i/2) + (i % 2) << "] == " << (int)Data[(i/2) + (i % 2)] << std::endl;
	}
	File.read((char*) (&Data), Header->SubChunk2Size);

	std::cout << "Data[0] == " << *Data.begin() << std::endl;
	//std::cout << "Data[0] == " << *Data.begin() << std::endl;
	//std::cout << "Data[1] == " << (int) Data[1] << std::endl;*/

	//std::cout << "Data[0]  == " << *Data.begin() << std::endl;

}