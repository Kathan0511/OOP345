



#include "Toy.h"

using namespace std;

namespace sdds
{
	sdds::Toy::Toy(){}
    void sdds::Toy::update(int numItems)
	{
		count = numItems;
	}

	sdds::Toy::Toy(const std::string& toy)
	{
		OrderId = std::stoi(toy);

		int First = toy.find(':');
		std::string Name = toy.substr(First + 1);
		First = 0;
		while (First == 0)
		{
			First = Name.find(' ');
			if (First == 0)
			{
				Name.erase(0, 1);
			}
		}

		int Second = 0;
		int flag = 1;
		while (flag)
		{

			Second = Name.find(':');
			First = Name.find(' ', Second - 1);
			if (First == Second - 1)
			{
				Name.erase(Second - 1, 1);
			}
			else
				flag = 0;
		}
		First = Name.find(':');
		Toy_Name = Name.substr(0, First);
		Name = Name.substr(First + 1);
		count = stoi(Name);
		First = Name.find(':');
		Name = Name.substr(First + 1);
		Toy_Price = stod(Name);
	}

	Toy::Toy(const Toy& obj)
	{
		*this = obj;
	}

	Toy& Toy::operator=(const Toy& obj)
	{
		OrderId = obj.OrderId;
		Toy_Name = obj.Toy_Name;
		count = obj.count;
		Toy_Price = obj.Toy_Price;
		itemHST = obj.itemHST;
		return *this;
	}

	Toy::~Toy(){}
	std::ostream& operator <<(std::ostream& os, const sdds::Toy& obj)
	{
		
		os << "Toy ";
		os.setf(std::ios::fixed, std::ios::floatfield);
		os.setf(ios::left);
		os.width(7);
		os.fill(' ');
		os << obj.OrderId;
		os << ":";
		os.unsetf(ios::left);

		os.setf(ios::right);
		os.width(18);
		os << obj.Toy_Name;
		os.width(3);
		os << obj.count;
		os << " items";
		os.width(8);
		os.precision(2);
		os << obj.Toy_Price;

		os << "/item  subtotal:";
		os.width(7);
		os << setprecision(2) << (obj.count * obj.Toy_Price);
		double sub = (obj.count * obj.Toy_Price);
		os << " tax:";
		os.width(6);
		os << setprecision(2) << ((obj.count * obj.Toy_Price) * 0.13);
		double tax = ((obj.count * obj.Toy_Price) * 0.13);
		os << " total:";
		os.width(7);
		os << setprecision(2) << (sub + tax);
		os.unsetf(ios::right);
		os << endl;

		return os;
	}
}