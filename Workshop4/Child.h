


 
#ifndef SDDS_CHILD_H
#define SDDS_CHILD_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include "Toy.h"

namespace sdds
{
	class Toy;
	class Child
	{
		const Toy** theToys{ nullptr };
		std::string Child_Name{};
		int Child_Age{ 0 };

	public:

		size_t m_count{ 0 };
		Child();
		Child(std::string Toy_Name, int age, const Toy* toys[], size_t count);
		Child(Child&& obj);
		Child& operator=(Child&& obj);
		Child(const Child& obj);
		Child& operator=(const Child& obj);
		~Child();
		size_t size() const;
		friend std::ostream& operator <<(std::ostream& os, const Child& obj);
	};
}
#endif
