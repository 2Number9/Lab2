#pragma once
#include <string>
#include <vector>

#define SAMPLES_IN_SECOND 44100 //������� ������

typedef struct {
	char ChunkId[4];  //�������� ������� RIFF-������� � ASCII-���������, �������� ������� RIFF-�������
	int ChunkIdSize;   //������ ���������� RIFF-�������, ������� � ���� ������� (������ ����� - 8)
	char Format[4];	   //�������� ������� Wave
	char SubChunk1Id[4]; //�������� ������� fmt
	int SubChunk1Size;	//���������� ������ ����������, ������� � ���� �������
	short int AudioFormat; //����� ������ (��� PCM == 1), �������� != 1 ���������� ������ ������
	short int NumChannels; //���������� �������: ���� == 1, ������ == 2
	int SampleRate;		//������� �������������
	int ByteRate;	//���������� ����, ���������� �� ������� ���������������
	short int BlockAlign; //���������� ���� ��� ������ ������, ������� ��� ������
	short int BitsPerSample; //���������� ��� � ������: ������� (�������� ��������): 8, 16 ��� � �.�.
	char SubChunk2Id[4]; //�������� ������� Data
	int SubChunk2Size; //���������� ���� � ������� ������
} Waw_header;

class WawParser {
public:
	WawParser(std::string);
	std::vector<short int> Parse();
	Waw_header* Header;
private:
	std::string FileName;
};