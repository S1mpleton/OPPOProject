#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>


struct product {
	std::string date;
	std::string name;
	int count = 0;
};

std::ostream& operator << (std::ostream& os, const product& data)
{
	return os << "Name: " << data.name << " | " << "Date: " << data.date << " | " << "Count: " << data.count << '\n';
}

std::string extract_date(const std::string& str_data) {

	std::regex regular1(R"(\b(\d{4})\.(\d{2})\.(\d{2})\b)");
	std::cmatch result;
	std::smatch match;

	if (std::regex_search(str_data, match, regular1)) {
		return match[0].str();
	}
	else {
		return std::string();
	}

}

std::string extract_name(const std::string& str_data) {

	std::regex regular_name(R"("[A-Za-zР-пр-џ]+")");
	std::cmatch result;
	std::smatch match;

	if (std::regex_search(str_data, match, regular_name)) {
		std::string str = match[0].str();
		str.erase(remove(str.begin(), str.end(), '"'), str.end());
		return str;
	}
	else {
		return std::string();
	}
}

int extract_count(const std::string& str_data) {

	std::regex regular_count(R"(^\d+\s|\s\d+\s|\s\d+$)");
	std::cmatch result;
	std::smatch match;

	if (std::regex_search(str_data, match, regular_count)) {
		std::string str = match[0].str();
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		return std::stoi(str);
	}
	else {
		return  -1;
	}
}


void load_data(std::vector<product>& data, std::ifstream& ist) {

	while (!ist.eof()) {

		std::string str;
		std::getline(ist, str);

		data.push_back({ extract_date(str), extract_name(str), extract_count(str) });
	}
}

void print_data(std::vector<product>& data) {
	for (int i = 0; i < data.size(); ++i) {
		std::cout << data.at(i);
	}
}


int main()
{
	std::setlocale(LC_ALL, "ru_RU.UTF-8");
	std::vector<product> data_product;

	std::ifstream ist;

	ist.open("practic_1_data.txt");
	load_data(data_product, ist);
	ist.close();

	print_data(data_product);

	return 0;
}
