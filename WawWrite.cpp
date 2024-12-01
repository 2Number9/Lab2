#include "WawWrite.h"
#include <iostream>

WawWrite::WawWrite(std::string FileName, Waw_header Header) : FileName(FileName), Header(Header) {}

void WawWrite::Write(std::vector<short int> Samples) {
	std::ofstream File(FileName, std::ios::binary);
	Header.SubChunk2Size = Samples.size() * 2;
	//Header.ChunkId[0] = 'R'; 	Header.ChunkId[1] = 'I'; 	Header.ChunkId[2] = 'F'; 	Header.ChunkId[0] = 'F';
	Header.SubChunk2Id[0] = 'd'; Header.SubChunk2Id[1] = 'a'; Header.SubChunk2Id[2] = 't'; Header.SubChunk2Id[3] = 'a';
	std::cout << "sizeof(Header) == " << sizeof(Header) << std::endl;
	File.write((char*) (&Header), sizeof(Header));
	File.write((char*) Samples.data(), Samples.size());
}