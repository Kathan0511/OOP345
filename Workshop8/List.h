 


#ifndef SDDS_LIST_H
#define SDDS_LIST_H


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds
{
	template <typename T>
	class List
	{
		std::vector<T> pri_lists;
	public:
		List() { }
		List(const char* fn) {
			std::ifstream file(fn);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(fn) + std::string(" ***");
			while (file) {
				T eup;
				if (eup.load(file))
					pri_lists.push_back(T(eup));
			}
		}
		size_t size() const {
			return pri_lists.size();
		}
		const T& operator[](size_t i) const {
			return pri_lists[i];
		}

		
		void operator+=(const std::unique_ptr<T>& Prot) {
			pri_lists.push_back(*Prot);
		}
		void operator+=(const T* Prot) {
			pri_lists.push_back(*Prot);
		}
		void display(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& eup : pri_lists)
				eup.display(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const List<T>& l) {
		l.display(os);
		return os;
	}
}
#endif