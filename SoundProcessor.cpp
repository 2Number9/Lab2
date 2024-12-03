#include "SoundProcessor.h"
#include "WawParser.h"
#include "ConfigParser.h"
#include <string>
#include "WawWrite.h"
#include "Factory.h"
#include <iostream>

SoundProcessor::SoundProcessor(int argc, char** argv) : argc(argc), argv(argv) {} //список инициализации членов конструктора

void SoundProcessor::RegisterConverters() {
	Factory::RegisterConverter<Converters::MixConverter>("mix");
	Factory::RegisterConverter<Converters::MuteConverter>("mute");
	Factory::RegisterConverter<Converters::AntiMixConverter>("anti_mix");
}

void SoundProcessor::run() {
	if (argc < 5) {
		throw std::runtime_error("Wrong amount of arguments");
	}

	WawParser waw_parser(argv[1]);
	std::vector<short int> waw_parsed;
	waw_parsed = waw_parser.Parse();

	ConfigParser config_parser(argv[argc - 2]);
	std::vector<Config_arguments> config_parsed;
	config_parsed = config_parser.Parse();

	RegisterConverters();

	for (int i = 0; i < config_parsed.size(); i++) {
		std::string converter_name;
		std::vector<std::string> args;
		converter_name = std::get<0>(config_parsed[i]);
		args = std::get<1>(config_parsed[i]);
		if (converter_name != "mute") {
			std::string other_input;
			other_input = args[0];
			other_input.erase(0, 1);
			other_input = argv[(stoi(other_input))];
			args[0] = other_input;
		}
		auto converter = Factory::CreateConverter(converter_name, args);
		converter->convert(&waw_parsed); //класс unique_ptr перегружает операторы ->, *, их можно использовать, словно мы работаем с обычным указателем
	}	//обращение к полям класса конвертера, уже проинициализированного args, можно обращаться к методам через ->
	WawWrite waw_writer(static_cast<std::string> (argv[argc - 1]), *waw_parser.Header);
	waw_writer.Write(waw_parsed);
}

