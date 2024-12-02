#include "ConfigParser.h"
#include <iostream>
#include <vector>
#include "WawParser.h"
#include "Converters.h"
#include "WawWrite.h"


int main(int argc, char** argv) {
	std::cout << static_cast<std::string> (argv[1]) << std::endl;
	//ConfigParser config(static_cast<std::string> (argv[1]));

	//typedef std::tuple<std::string, std::vector<std::string>> data;
	//std::vector<data> parsed_config;

	//parsed_config = config.Parse();

	std::cout << "argc == " << argc << std::endl;
	ConfigParser config_parser(argv[argc-2]); //предпоследний элемент
	std::vector<Config_arguments> config_parsed;
	config_parsed = config_parser.Parse();
	std::cout << " Jopix " << std::endl;
	WawParser waw_parser(argv[1]);
	SamplesProduct waw_parsed;
	std::cout << "waw_parsed.size() == " << waw_parsed.size() << std::endl;
	waw_parsed = waw_parser.Parse();
	std::cout << "waw_parsed.size() == " << waw_parsed.size() << std::endl;

	//for (int i = 0; i < config_parsed.size(); i++) {
	/*if (std::get<0>(config_parsed[0]) == "mute") {
		Converters::MuteConverter muted_samples(std::get<1>(config_parsed[0]));
		muted_samples.convert(&waw_parsed);
	}
	//}*/
	std::cout << "waw_parsed.size() == " << waw_parsed.size() << std::endl;
	int cnt = 0;
	for (int i = 0; i < waw_parsed.size(); i++) {
		if (waw_parsed[i] == 0)
			cnt++;
			//std::cout << "waw_parsed[" << i << "] == " << waw_parsed[i] << std::endl;
	}
	std::cout << "cnt == " << cnt << std::endl;
	std::cout << "config_parsed.size() == " << config_parsed.size() << std::endl;
	
	for (int i = 0; i < config_parsed.size(); i++) {
		if (std::get<0>(config_parsed[i]) == "mute") {
			Converters::MuteConverter Muted(std::get<1>(config_parsed[i]));
			Muted.convert(&waw_parsed);
		}
		else if (std::get<0>(config_parsed[i]) == "mix") {
			std::cout << "MIXUEM YOPTA" << std::endl;
			std::cout << "parsed(dst): " << std::endl;
			for (int i = 0; i < 1500; i++) {
				std::cout << "waw_parsed[" << i << "] == " << waw_parsed[i] << std::endl;
			}
			std::string other_input = (std::get<1>(config_parsed[i]))[0];
			std::cout << "other_input == " << other_input << std::endl;
			other_input.erase(0, 1);
			std::cout << "other_input == " << other_input << std::endl;
			other_input = argv[(stoi(other_input))];
			std::cout << "other_input == " << other_input << std::endl;
			std::get<1>(config_parsed[i])[0] = other_input;
			std::cout << "std::get<1>(config_parsed[i])[0] == " << (std::get<1>(config_parsed[i])[0]) << std::endl;
			Converters::MixConverter Mixed(std::get<1>(config_parsed[i]));
			std::cout << "Opa" << std::endl;
			Mixed.convert(&waw_parsed);
		}
	}
	std::cout << "parsed(mixed):" << std::endl;
	for (int i = 0; i < 1500; i++) {
		std::cout << "waw_parsed[" << i << "] == " << waw_parsed[i] << std::endl;
	}
	std::cout << "waw_parser.Header->SampleRate == " << waw_parser.Header->SampleRate << std::endl;
	
	//for (int i = 0; i < 10000; i++) {
		//std::cout << "waw_parsed[" << i << "] == " << waw_parsed[i] << std::endl;
	//}
	//for (int i = 0; i < 10000; i++) {
		//std::cout << "waw_parsed[" << i << "] == " << waw_parsed[i] << std::endl;
	//}

	WawWrite Writer(static_cast<std::string> (argv[argc-1]), *waw_parser.Header);
	Writer.Write(waw_parsed);

	return 0;
}