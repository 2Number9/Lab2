#include "Converters.h"
#include "WawParser.h"
#include <string>
#include <iostream>

Converters::MuteConverter::MuteConverter(const std::vector<std::string>& args) {
	start = stoi(args[0]);
	end = stoi(args[1]);
}

SamplesProduct Converters::MuteConverter::convert(const SamplesProduct& input1, const std::vector<SamplesProduct>& input2) {
	SamplesProduct Returning_value = input1;
	for (int i = start * SAMPLES_IN_SECOND; i < std::min(end * SAMPLES_IN_SECOND, static_cast<int> (Returning_value.size())); i++) {
		(Returning_value)[i] = 0;
	}
	return Returning_value;
}

Converters::MixConverter::MixConverter(const std::vector<std::string>& args) {
	index = stoi(args[0]);
	time = stoi(args[1]);
}

SamplesProduct Converters::MixConverter::convert(const SamplesProduct& input1, const std::vector<SamplesProduct>& input2) {
	SamplesProduct Returning_value = input1;
	SamplesProduct Other_value = input2[index-2];
	for (int i = time * SAMPLES_IN_SECOND; i < std::min(Returning_value.size(), Other_value.size()); i++) {
		Returning_value[i] = (Returning_value[i] + Other_value[i]) / 2;
	}
	return Returning_value;
}

Converters::AntiMixConverter::AntiMixConverter(const std::vector<std::string>& args) {
	index = stoi(args[0]);
	start = (stoi(args[1]));
	end = (stoi(args[2]));
}

SamplesProduct Converters::AntiMixConverter::convert(const SamplesProduct& input1, const std::vector<SamplesProduct>& input2) {
	SamplesProduct Returning_value = input1;
	SamplesProduct Other_value = input2[index-2];
	for (int i = start * SAMPLES_IN_SECOND; i < std::min(end * SAMPLES_IN_SECOND, static_cast<int> (Returning_value.size())); i++) {
		Returning_value[i] = (Returning_value[i] - (Other_value[i] / 2)) * 2;
	}
	return Returning_value;
}