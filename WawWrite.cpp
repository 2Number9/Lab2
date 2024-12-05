#include "WawWrite.h"
#include <iostream>

WawWrite::WawWrite(std::string FileName, Waw_header Header) : FileName(FileName), Header(Header) {}

void WawWrite::Write(std::vector<short int> Samples) {
	std::ofstream File(FileName, std::ios::binary);
	Header.SubChunk2Size = Samples.size() * 2;
	Header.SubChunk2Id[0] = 'd'; Header.SubChunk2Id[1] = 'a'; Header.SubChunk2Id[2] = 't'; Header.SubChunk2Id[3] = 'a';
	File.write(reinterpret_cast<char*> (&Header), sizeof(Header));
	File.write(reinterpret_cast<char*> (Samples.data()), Samples.size());
}