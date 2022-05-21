 



#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include<string>
using namespace std;

#include "ProteinDatabase.h"

namespace sdds
{
	ProteinDatabase::ProteinDatabase() {}

	ProteinDatabase::ProteinDatabase(char* f_name)
	{
		arrLength = 0;
		CountRecord = nullptr;

		ifstream File_name(f_name);

		if (!File_name)
			return;

		string line, name;

		while (std::getline(File_name, line).good()) {
			if (line[0] == '>') {
				arrLength++;
			}
		}


		File_name.clear();
		File_name.seekg(ios::beg);

		CountRecord = new string[arrLength];
		line.clear();
		int i = -1;

		while (getline(File_name, line).good()) {
			if (line[0] == '>') {
				++i;
				name = line.substr(1);
			}
			else if (!name.empty()) {
				CountRecord[i] += line;
			}
		}


	}
	ProteinDatabase::ProteinDatabase(ProteinDatabase&& old) {
		*this = std::move(old);
	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& old) {
		*this = old;
	}

	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& src) {
		if (this != &src) {

			delete[] CountRecord;
			CountRecord = nullptr;

			CountRecord = src.CountRecord;
			src.CountRecord = nullptr;
			arrLength = src.arrLength;
			src.arrLength = 0;
		}
		return *this;
	}

	size_t ProteinDatabase::size() {
		return arrLength;
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& src) {
		if (this != &src) {
			delete[] CountRecord;
			arrLength = src.arrLength;

			CountRecord = new string[arrLength]{};

			for (long unsigned int i = 0; i < arrLength; i++) {
				CountRecord[i] = src.CountRecord[i];
			}
		}

		return *this;
	}

	std::string ProteinDatabase::operator[](size_t Index) {

		if (Index < arrLength) {

			return CountRecord[Index];
		}
		return "";
	}

	ProteinDatabase::~ProteinDatabase() {
		delete[] CountRecord;
	}
}
