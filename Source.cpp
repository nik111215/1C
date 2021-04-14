#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>

void Calculate_dif() {
	std::string new_name_file, old_name_file;
	std::cin >> new_name_file >> old_name_file;
	char buffer_old_file, buffer_new_file;
	const char* new_name = new_name_file.c_str();
	const char* old_name = old_name_file.c_str();
	FILE* new_file;
	FILE* old_file;
	FILE* difference_file;
	int k = 0;
	new_file = fopen(new_name, "rb");
	old_file = fopen(old_name, "rb");
	difference_file = fopen("difference_file", "wb");
	while (!feof(new_file) && !feof(old_file)) {
		buffer_new_file = fgetc(new_file);
		buffer_old_file = fgetc(old_file);
		if (buffer_new_file != buffer_old_file) {
			putc(buffer_new_file, difference_file);
			putc(':/:', difference_file);
			putc(k, difference_file);
			putc('://', difference_file);
		}
		++k;
	}
}


void Recover() {
	std::string old_name_file, difference_name_file;
	std::cin >> old_name_file >> difference_name_file;
	const char* difference_name = difference_name_file.c_str();
	const char* old_name = old_name_file.c_str();
	FILE* old_file;
	FILE* difference_file;
	FILE* new_file;

	std::string number = "";
	int k = 0;
	difference_file = fopen(difference_name, "rb");
	old_file = fopen(old_name, "rb");
	new_file = fopen("new_file", "wb");
	while (!feof(old_file)) {
		char symbol_old_file = fgetc(old_file);
		char symbol = fgetc(difference_file);
		fseek(difference_file, 3, SEEK_CUR);
		while (1) {
			symbol = fgetc(difference_file);
			if (isdigit(symbol)) {
				number += symbol;
			}
			else {
				break;
			}
		}
		int position = atoi(number.c_str());
		fseek(difference_file, 2, SEEK_CUR);
		if (k == position)  {
			putc(symbol, new_file);
		}
		else {
			putc(symbol_old_file, new_file);
		}

	}
}

int main() {

	std::string name_comand;
	std::cin >> name_comand;
	if (name_comand == "Рассчитать диф") {
		Calculate_dif();
	} 
	if (name_comand == "Recover") {
		Recover();
	}


	return 0;
}