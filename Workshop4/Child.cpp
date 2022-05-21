



#include "Child.h"

using namespace std;

namespace sdds
{
	Child::Child()
	{
		delete[] theToys;
		theToys = nullptr;
	}
	Child::Child(std::string Toy_Name, int age, const Toy* toys[], size_t count)
		:Child_Name(Toy_Name), Child_Age(age)
	{
		for (auto i = 0u; i < m_count; ++i)
			delete theToys[i];

		delete[] theToys;
		m_count = count;
		theToys = new  const Toy * [count];

		for (size_t i = 0; i < count; i++)
		{

			theToys[i] = new Toy(*(toys[i]));
		}

	}
	Child::Child(const Child& obj)
	{
		*this = obj;
	}
	Child& Child::operator=(const Child& obj)
	{
		if (this != &obj)
		{
			for (auto i = 0u; i < m_count; ++i)
			delete theToys[i];
			delete[] theToys;
			m_count = obj.m_count;
			Child_Age = obj.Child_Age;
			Child_Name = obj.Child_Name;
			theToys = new  const Toy * [m_count];
			for (size_t i = 0; i < m_count; i++)
			{
				theToys[i] = new Toy(*(obj.theToys[i]));

			}
		}
		return *this;
	}

	Child::Child(Child&& obj)
	{
		*this = std::move(obj);
	}

	Child& Child::operator=(Child&& obj)
	{
		if (this != &obj)
		{

			delete[] theToys;
			m_count = obj.m_count;
			Child_Age = obj.Child_Age;
			Child_Name = obj.Child_Name;
			theToys = obj.theToys;
			obj.theToys = nullptr;
			obj.Child_Age = 0;
			obj.Child_Name = "";
			obj.m_count = 0;
		}
		return *this;
	}

	Child::~Child()
	{
		for (auto i = 0u; i < m_count; ++i)
		delete theToys[i];

		delete[] theToys;
		theToys = nullptr;

	}

	size_t Child::size() const
	{
		return this->m_count;
	}

	std::ostream& operator<<(std::ostream& os, const Child& obj)
	{
		static size_t CALL_CNT = 1;
		os << "--------------------------" << endl;
		if (obj.theToys == nullptr) {
			os << "Child " << CALL_CNT << ": " << " " << "0 years old:" << endl;
			os << "--------------------------" << endl;
			os << "This child has no toys!" << endl;
		}
		else {
			os << "Child " << CALL_CNT << ": " << obj.Child_Name << " " << obj.Child_Age << " years old:" << endl;
			os << "--------------------------" << endl;
			for (size_t i = 0; i < obj.m_count; i++)
			{
				os << *(obj.theToys[i]);
			}
		}
		CALL_CNT++;
		os << "--------------------------" << endl;

		return os;
	}
}