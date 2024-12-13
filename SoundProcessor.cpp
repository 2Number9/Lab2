#include "SoundProcessor.h"
#include "WawParser.h"
#include "ConfigParser.h"
#include <string>
#include "WawWrite.h"
#include "Factory.h"
#include <iostream>

SoundProcessor::SoundProcessor(int argc, char** argv) : argc(argc), argv(argv) {} //


void SoundProcessor::run() {
	
	if (argc < 5) {
		throw std::runtime_error("Wrong amount of arguments");
	}

	std::vector<std::string> input_names;
	input_names.resize(argc - 2);
	for (int i = 1; i < argc - 2; i++) {
		input_names[i] = argv[i];
	}

	WawParser waw_parser(input_names[1]);
	std::vector<int16_t> waw_parsed;
	waw_parsed = waw_parser.Parse();
	
	ConfigParser config_parser(argv[argc - 2]);
	std::vector<Config_arguments> config_parsed;
	config_parsed = config_parser.Parse();
	
	std::vector<std::vector<int16_t>> other_input_parsed;
	other_input_parsed.resize(argc - 3);
	for (int i = 2; i < argc - 2; i++) {
		WawParser other_parser(input_names[i]);
		other_input_parsed[i - 2] = other_parser.Parse();
	}

	SamplesProduct Returning_value = waw_parsed;
	const std::vector<SamplesProduct> &Other_values = other_input_parsed;
	
		for (int i = 0; i < config_parsed.size(); i++) {
		const SamplesProduct &Iteration_value = Returning_value;
		std::string converter_name;
		const std::vector<std::string> &args = std::get<1>(config_parsed[i]);
		converter_name = std::get<0>(config_parsed[i]);
		
		auto converter = Factory::CreateConverter(converter_name, args);
		Returning_value = converter->convert(Iteration_value, Other_values);
	}

	WawWrite waw_writer(argv[argc - 1], *waw_parser.Header);
	waw_writer.Write(Returning_value);
}