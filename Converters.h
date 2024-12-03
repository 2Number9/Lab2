#pragma once
#include <vector>
#include <string>

typedef std::vector<short int> SamplesProduct;

namespace Converters { //имена используются только в пределах пространства имён, очень удобно
	class BaseConverter {
	public:
		virtual void convert(SamplesProduct* input) = 0; //чистая виртуальная функция базового класса
	};													 //не имеет реализации, обязательно переопределена
														 //во всех производных классах
	class MuteConverter : public BaseConverter {

	public:
		explicit MuteConverter(std::vector<std::string> args); //данные с ConfigParser..
		void convert(SamplesProduct* input) override; //override значит, что мы переопределили функцию
													  //базового класса
	private:
		int start, end;								  //откуда до куда работаем с сэмплами
	};


	class MixConverter : public BaseConverter {
	public:
		explicit MixConverter(std::vector<std::string> args);
		void convert(SamplesProduct* input) override; //override переопределяет функцию базового класса
	private:
		std::string FileName;	//нам подают файл
		int time;				//и с какого момента должно происходить смешивание

	};

	class AntiMixConverter : public BaseConverter {
	public:
		explicit AntiMixConverter(std::vector<std::string> args);
		void convert(SamplesProduct* input) override;
	private:
		std::string FileName;
		int start;
		int end;
	};
}