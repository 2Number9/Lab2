#include "Converters.h"
#include "WawParser.h"
#include <string>
#include <iostream>

Converters::MuteConverter::MuteConverter(std::vector<std::string> args) {
	start = stoi(args[0]);
	std::cout << "start == " << start << std::endl;
	end = stoi(args[1]);
	std::cout << "end == " << end << std::endl;
}

void Converters::MuteConverter::convert(SamplesProduct* input) { //input->size() - ��� ���������� ��������� � ������� (�������)
	for (int i = start * SAMPLES_IN_SECOND; i < std::min(end * SAMPLES_IN_SECOND, static_cast<int> (input->size())); i++) {
		(*input)[i] = 0;
	}
}

Converters::MixConverter::MixConverter(std::vector<std::string> args) {
	FileName = args[1];
	time = stoi(args[2]);
}

void Converters::MixConverter::convert(SamplesProduct* input) {
	WawParser parser(FileName);
	SamplesProduct parsed;
	parsed = parser.Parse();
	for (int i = time * SAMPLES_IN_SECOND; i < std::min(parsed.size(), input->size()); i++) {
		(*input)[i] = ((*input)[i] + parsed[i]) / 2;
	}
}