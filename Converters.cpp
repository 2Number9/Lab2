#include "Converters.h"
#include "WawParser.h"
#include <string>
#include <iostream>

Converters::MuteConverter::MuteConverter(std::vector<std::string> args) {
	start = stoi(args[0]);
	end = stoi(args[1]);
}

void Converters::MuteConverter::convert(SamplesProduct* input) { 
	for (int i = start * SAMPLES_IN_SECOND; i < std::min(end * SAMPLES_IN_SECOND, static_cast<int> (input->size())); i++) {
		(*input)[i] = 0;
	}
}

Converters::MixConverter::MixConverter(std::vector<std::string> args) {
	FileName = (args[0]);
	time = stoi(args[1]);
}

void Converters::MixConverter::convert(SamplesProduct* input) {
	WawParser parser(FileName);
	SamplesProduct parsed;
	parsed = parser.Parse();
	for (int i = time * SAMPLES_IN_SECOND; i < std::min(parsed.size(), input->size()); i++) {
		(*input)[i] = ((*input)[i] + parsed[i]) / 2;
	}
}

Converters::AntiMixConverter::AntiMixConverter(std::vector<std::string> args) {
	FileName = args[0];
	start = (stoi(args[1]));
	end = (stoi(args[2]));
}

void Converters::AntiMixConverter::convert(SamplesProduct* input) {
	WawParser waw_parser(FileName);
	SamplesProduct waw_parsed = waw_parser.Parse();
	for (int i = start * SAMPLES_IN_SECOND; i < std::min(end * SAMPLES_IN_SECOND, static_cast<int> (input->size())); i++) {
		(*input)[i] = ((*input)[i] - (waw_parsed[i] / 2)) * 2;
	}
}