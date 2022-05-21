



#include "ConfirmOrder.h"

using namespace std;

namespace sdds
{
	ConfirmOrder::ConfirmOrder()
	{
		delete[] theToys;
		theToys = nullptr;
	}
	ConfirmOrder::ConfirmOrder(const ConfirmOrder& obj)
	{
		*this = obj;
	}
	ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& obj)
	{
		if (this != &obj)
		{
			m_count = obj.m_count;
			delete theToys;
			theToys = new const Toy * [obj.m_count];
			for (size_t i = 0; i < m_count; i++)
			{
				theToys[i] = obj.theToys[i];
			}

		}
		return *this;
	}
	ConfirmOrder::ConfirmOrder(ConfirmOrder&& obj)
	{
		*this = std::move(obj);
	}
	ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& obj)
	{
		if (this != &obj)
		{
			m_count = obj.m_count;
			delete[] theToys;
			theToys = obj.theToys;

			obj.theToys = nullptr;
			obj.m_count = 0;

		}

		return *this;
	}
	ConfirmOrder::~ConfirmOrder()
	{
		delete[] theToys;
	}
	ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy)
	{

		bool isLocated = false;
		for (size_t i = 0; i < m_count && !isLocated; i++)
		{
			if (theToys[i] == &toy)
			{
				isLocated = true;

			}
		}

		if (!isLocated)
		{
			const Toy** actingTemp = nullptr;
			actingTemp = new const Toy * [m_count + 1];
			for (size_t i = 0; i < m_count; i++)
			{
				actingTemp[i] = theToys[i];

			}
			actingTemp[m_count] = &toy;
			m_count++;
			delete[] theToys;
			theToys = actingTemp;
		}
		return *this;
	}

	ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy)
	{
		bool isLocated = false;
		size_t i = 0;
		for (; i < m_count && !isLocated; i++)
		{
			if (theToys[i] == &toy)
			{
				isLocated = true;

			}
		}
		if (isLocated) {
			for (; i < m_count; ++i)
				theToys[i - 1] = theToys[i];  
			if (m_count > 0) {
				theToys[m_count - 1] = nullptr;  
				m_count--;
			}
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const ConfirmOrder& obj)
	{

		os << "--------------------------" << endl;
		os << "Confirmations to Send" << endl;
		os << "--------------------------" << endl;
		if (obj.theToys == nullptr) {

			os << "There are no confirmations to send!" << endl;
		}
		else {

			for (size_t i = 0; i < obj.m_count; i++)
			{
				os << *(obj.theToys[i]);
			}
		}

		os << "--------------------------" << endl;
		return os;
	}
}