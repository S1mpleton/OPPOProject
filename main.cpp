#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>


struct date {
	date() {
		year = -1;
		mounth = -1;
		day = -1;
	}

	date(const std::string& date_str) {
		splitting_date(date_str, year, mounth, day);
	}

	int year;
	int mounth;
	int day;

public:
	void static splitting_date(const std::string& date_str, int& year, int& mounth, int& day) {

		std::string str_year(date_str);
		std::string str_mounth(date_str);
		std::string str_day(date_str);

		auto firstPoint = date_str.find_first_of('.');
		auto secondPoint = date_str.find_last_of('.');

		str_year.erase(str_year.begin() + firstPoint, str_year.end());

		str_mounth.erase(str_mounth.begin() + secondPoint, str_mounth.end());
		str_mounth.erase(str_mounth.begin(), str_mounth.begin() + (++firstPoint));

		str_day.erase(str_day.begin(), str_day.begin() + (++secondPoint));

		year = std::stoi(str_year);
		mounth = std::stoi(str_mounth);
		day = std::stoi(str_day);
	}

	bool operator==(const date& date) {
		return (year == date.year and mounth == date.mounth and day == date.day);
	}

	bool operator>(const date& date) {

		if (year < date.year) {
			return true;
		}
		else if (year == date.year) {
			if (mounth < date.mounth) {
				return true;
			}
			else if (mounth == date.mounth) {
				if (day < date.day) {
					return true;
				}
			}
		}
		return false;
	}

	bool operator<(const date& date) {
		return !(*this > date) and !(*this == date);
	}

	bool operator<=(const date& date) {
		return !(*this > date);
	}

	bool operator>=(const date& date) {
		return (*this > date) or (*this == date);
	}

	bool operator!=(const date& date) {
		return !(*this == date);
	}


};

struct product {
	date date;
	std::string name;
	int count = 0;
};

std::ostream& operator << (std::ostream& os, const date& date)
{
	std::string out_str;
	out_str.append(std::to_string(date.year));
	out_str.append(":");
	if (date.mounth < 10) {
		out_str.append("0");
	}
	out_str.append(std::to_string(date.mounth));
	out_str.append(":");
	if (date.day < 10) {
		out_str.append("0");
	}
	out_str.append(std::to_string(date.day));

	return os << out_str;
}

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

		data.push_back({ date(extract_date(str)), extract_name(str), extract_count(str) });
	}
}

void print_data(std::vector<product>& data) {
	for (int i = 0; i < data.size(); ++i) {
		std::cout << data.at(i);
	}
}


void sort_for_date(std::vector<product>& data) {

	for (std::size_t i = 1; i < data.size(); ++i) {
		product x = data[i];
		size_t j = i;
		while (j > 0 && data[j - 1].date > x.date) {
			data[j] = data[j - 1];
			--j;
		}
		data[j] = x;
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
	sort_for_date(data_product);
	std::cout << '\n';
	print_data(data_product);

	return 0;
}
