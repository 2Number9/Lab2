#pragma once
#include <vector>
#include <string>

typedef std::vector<short int> SamplesProduct;

namespace Converters { 
	class BaseConverter {
	public:
		virtual void convert(SamplesProduct* input1, std::vector<SamplesProduct> input2) = 0; 
	};													 

	class MuteConverter : public BaseConverter {

	public:
		explicit MuteConverter(std::vector<std::string> args);
		void convert(SamplesProduct* input1, std::vector<SamplesProduct> input2) override; 
													  
	private:
		int start, end;								  
	};


	class MixConverter : public BaseConverter {
	public:
		explicit MixConverter(std::vector<std::string> args);
		void convert(SamplesProduct* input1, std::vector<SamplesProduct> input2) override; //override переопредел€ет функцию базового класса
	private:
		int index;
		int time;				//и с какого момента должно происходить смешивание
	};

	class AntiMixConverter : public BaseConverter {
	public:
		explicit AntiMixConverter(std::vector<std::string> args);
		void convert(SamplesProduct* input1, std::vector<SamplesProduct> input2) override;
	private:
		int index;
		int start;
		int end;
	};
}