#include "SoundProcessor.h"
#include "WawParser.h"
#include "ConfigParser.h"
#include <string>
#include "WawWrite.h"
#include "Factory.h"
#include <iostream>

SoundProcessor::SoundProcessor(int argc, char** argv) : argc(argc), argv(argv) {} //

void SoundProcessor::RegisterConverters() {
	Factory::RegisterConverter<Converters::MixConverter>("mix");
	Factory::RegisterConverter<Converters::MuteConverter>("mute");
	Factory::RegisterConverter<Converters::AntiMixConverter>("anti_mix");
}

void SoundProcessor::run() {
	if (argc < 5) {
		throw std::runtime_error("Wrong amount of arguments");
	}

	std::vector<std::string>* input_names;
	input_names = new std::vector<std::string>;
	(*input_names).resize(argc - 2);
	for (int i = 1; i < argc - 2; i++) {
		(*input_names)[i] = argv[i];
	}

	WawParser waw_parser((*input_names)[1]);
	std::vector<int16_t>* waw_parsed;
	waw_parsed = waw_parser.Parse();
	std::cout << "Mcarbe" << std::endl;
	ConfigParser config_parser(argv[argc - 2]);
	std::vector<Config_arguments>* config_parsed;
	config_parsed = config_parser.Parse();
	std::cout << "slaves" << std::endl;
	std::cout << (*config_parsed).size() <<  std::endl;
	/*for (int i = 0; i < (*config_parsed).size(); i++) {
		std::cout << "converter_name == " << (std::get<0>((*config_parsed)[i])) << std::endl;
		std::cout << "config_parsed[i] == " << (*(std::get<1>((*config_parsed)[i])))[0] << " ";
		for (int index = 0; index < (*(std::get<1>((*config_parsed)[i]))).size(); index++)
			std::cout << "config_parsed[i] == " << (*(std::get<1>((*config_parsed)[i])))[index] << " ";
		std::cout << std::endl;
	}*/
	std::vector<std::vector<int16_t>*>* other_input_parsed;
	other_input_parsed = new std::vector<std::vector<int16_t>*>;
	(*other_input_parsed).resize(argc - 3);
	for (int i = 2; i < argc - 2; i++) {
		WawParser other_parser((*input_names)[i]);
		(*other_input_parsed)[i - 2] = other_parser.Parse();
	}

	RegisterConverters();


	for (int i = 0; i < (*config_parsed).size(); i++) {
		std::string converter_name;
		std::vector<std::string>* args;
		converter_name = std::get<0>((*config_parsed)[i]);
		args = std::get<1>((*config_parsed)[i]);
		auto converter = Factory::CreateConverter(converter_name, args);
		converter->convert(waw_parsed, other_input_parsed);
	}
	WawWrite waw_writer(argv[argc - 1], *waw_parser.Header);
	waw_writer.Write(waw_parsed);
}