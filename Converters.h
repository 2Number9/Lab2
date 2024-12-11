#pragma once
#include <vector>
#include <string>

typedef std::vector<int16_t> SamplesProduct;

namespace Converters {
	class BaseConverter {
	public:
		virtual void convert(SamplesProduct* input1, std::vector<SamplesProduct*>* input2) = 0;
	};

	class MuteConverter : public BaseConverter {

	public:
		explicit MuteConverter(std::vector<std::string>* args);
		void convert(SamplesProduct* input1, std::vector<SamplesProduct*>* input2) override;

	private:
		int start, end;
	};


	class MixConverter : public BaseConverter {
	public:
		explicit MixConverter(std::vector<std::string>* args);
		void convert(SamplesProduct* input1, std::vector<SamplesProduct*>* input2) override; //
	private:
		int index;
		int time;				//
	};

	class AntiMixConverter : public BaseConverter {
	public:
		explicit AntiMixConverter(std::vector<std::string>* args);
		void convert(SamplesProduct* input1, std::vector<SamplesProduct*>* input2) override;
	private:
		int index;
		int start;
		int end;
	};
}