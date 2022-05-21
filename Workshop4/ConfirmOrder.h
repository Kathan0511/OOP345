



#ifndef SDDS_CONFIRM_H
#define SDDS_CONFIRM_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include "Toy.h"

namespace sdds
{
	class Toy;
	class ConfirmOrder
	{
		const Toy** theToys{ nullptr };
		size_t m_count{ 0 };

	public:
		ConfirmOrder();
		ConfirmOrder(const ConfirmOrder& obj);
		ConfirmOrder& operator=(const ConfirmOrder& obj);
		ConfirmOrder(ConfirmOrder&& obj);
		ConfirmOrder& operator=(ConfirmOrder&& obj);
		~ConfirmOrder();
		ConfirmOrder& operator+=(const Toy& toy);
		ConfirmOrder& operator-=(const Toy& toy);


		friend std::ostream& operator <<(std::ostream& os, const ConfirmOrder& obj);


	};
}
#endif
