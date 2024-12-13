#pragma once
#include <vector>
#include <string>

typedef std::vector<int16_t> SamplesProduct;

namespace Converters {
	class BaseConverter {
	public:
		virtual SamplesProduct convert(const SamplesProduct &input1, const std::vector<SamplesProduct> &input2) = 0;
	};

	class MuteConverter : public BaseConverter {

	public:
		explicit MuteConverter(const std::vector<std::string> &args);
		SamplesProduct convert(const SamplesProduct &input1, const std::vector<SamplesProduct>& input2) override;

	private:
		int start, end;
	};


	class MixConverter : public BaseConverter {
	public:
		explicit MixConverter(const std::vector<std::string> &args);
		SamplesProduct convert(const SamplesProduct& input1, const std::vector<SamplesProduct>& input2) override; //
	private:
		int index;
		int time;				//
	};

	class AntiMixConverter : public BaseConverter {
	public:
		explicit AntiMixConverter(const std::vector<std::string> &args);
		SamplesProduct convert(const SamplesProduct& input1, const std::vector<SamplesProduct>& input2) override;
	private:
		int index;
		int start;
		int end;
	};
}