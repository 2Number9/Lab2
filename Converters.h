#pragma once
#include <vector>
#include <string>

typedef std::vector<short int> SamplesProduct;

namespace Converters { //����� ������������ ������ � �������� ������������ ���, ����� ������
	class BaseConverter {
	public:
		virtual void convert(SamplesProduct* input) = 0; //������ ����������� ������� �������� ������
	};													 //�� ����� ����������, ����������� ��������������
														 //�� ���� ����������� �������
	class MuteConverter : public BaseConverter {

	public:
		explicit MuteConverter(std::vector<std::string> args); //������ � ConfigParser..
		void convert(SamplesProduct* input) override; //override ������, ��� �� �������������� �������
													  //�������� ������
	private:
		int start, end;								  //������ �� ���� �������� � ��������
	};


	class MixConverter : public BaseConverter {
	public:
		explicit MixConverter(std::vector<std::string> args);
		void convert(SamplesProduct* input) override; //override �������������� ������� �������� ������
	private:
		std::string FileName;	//��� ������ ����
		int time;				//� � ������ ������� ������ ����������� ����������

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