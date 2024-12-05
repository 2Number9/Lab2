#include "Converters.h"
#include "WawParser.h"
#include <string>
#include <iostream>

Converters::MuteConverter::MuteConverter(std::vector<std::string> args) {
	start = stoi(args[0]);
	end = stoi(args[1]);
}

void Converters::MuteConverter::convert(SamplesProduct* input1, std::vector<SamplesProduct> input2) { 
	for (int i = start * SAMPLES_IN_SECOND; i < std::min(end * SAMPLES_IN_SECOND, static_cast<int> (input1->size())); i++) {
		(*input1)[i] = 0;
	}
}

Converters::MixConverter::MixConverter(std::vector<std::string> args) {
	index = stoi(args[0]);
	time = stoi(args[1]);
}

void Converters::MixConverter::convert(SamplesProduct* input1, std::vector<SamplesProduct> input2) {
	for (int i = time * SAMPLES_IN_SECOND; i < std::min(input2[index-2].size(), input1->size()); i++) {
		(*input1)[i] = ((*input1)[i] + (input2)[index-2][i]) / 2;
	}
}

Converters::AntiMixConverter::AntiMixConverter(std::vector<std::string> args) {
	index = stoi(args[0]);
	start = (stoi(args[1]));
	end = (stoi(args[2]));
}

void Converters::AntiMixConverter::convert(SamplesProduct* input1, std::vector<SamplesProduct> input2) {
	for (int i = start * SAMPLES_IN_SECOND; i < std::min(end * SAMPLES_IN_SECOND, static_cast<int> (input1->size())); i++) {
		(*input1)[i] = ((*input1)[i] - ((input2)[index-2][i] / 2)) * 2;
	}
}