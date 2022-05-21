 


#ifndef SDDS_FOODORDER_H__
#define SDDS_FOODORDER_H__
#include <iostream>
#include <cstring>

namespace sdds
{
	class FoodOrder
	{
		char CxName[10];

		std::string OrderDesc;
		
		double Total_Price;
		
		bool theSpecialPrice;

	public:
		FoodOrder();
		std::istream& read(std::istream& istr);
		void display();
	};
}
#endif 
