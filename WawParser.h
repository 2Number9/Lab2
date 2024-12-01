#pragma once
#include <string>
#include <vector>

#define SAMPLES_IN_SECOND 44100 //условие задачи

typedef struct {
	char ChunkId[4];  //Содержит символы RIFF-цепочки в ASCII-кодировке, является началом RIFF-цепочки
	int ChunkIdSize;   //Размер оставшейся RIFF-цепочки, начиная с этой позиции (размер файла - 8)
	char Format[4];	   //Содержит символы Wave
	char SubChunk1Id[4]; //Содержит символы fmt
	int SubChunk1Size;	//Оставшийся размер подцепочки, начиная с этой позиции
	short int AudioFormat; //Аудио формат (для PCM == 1), значения != 1 обозначают формат сжатия
	short int NumChannels; //Количество каналов: Моно == 1, Стерео == 2
	int SampleRate;		//Частота дискретезации
	int ByteRate;	//Количество байт, переданных за секунду воспроизведения
	short int BlockAlign; //Количество байт для одного сэмпла, включая все каналы
	short int BitsPerSample; //Количество бит в сэмпле: Глубина (Точность звучания): 8, 16 бит и т.д.
	char SubChunk2Id[4]; //Содержит символы Data
	int SubChunk2Size; //Количество байт в области данных
} Waw_header;

class WawParser {
public:
	WawParser(std::string);
	std::vector<short int> Parse();
	Waw_header* Header;
private:
	std::string FileName;
};