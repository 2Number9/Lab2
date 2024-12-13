#include "Factory.h"
#include <iostream>
#include <utility>

std::unique_ptr<Converters::BaseConverter> Factory::CreateConverter(std::string name, const std::vector<std::string> &args) {
	
	if (name == "mix") {
		auto cvt = std::make_unique<Converters::MixConverter>(std::move(args));
		return cvt;
	}
	else //const ссылки
		if (name == "mute") {
			auto cvt = std::make_unique<Converters::MuteConverter>(std::move(args));
			return cvt;
		}
		else {
			if (name == "anti_mix") {
				auto cvt = std::make_unique<Converters::AntiMixConverter>(std::move(args));
				return cvt;
			}
			else {
				auto cvt = nullptr;
				return cvt;
			}
		}

}

