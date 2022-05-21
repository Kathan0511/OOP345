//==============================================
//Name: Kathan Patel           
//Student ID: 148609191       
//Email: kjpatel30@myseneca.ca            
//Section: NEE        
//Date: 23/01/2022               
//==============================================


//I have done mostly all the coding by myselfand took some help for understanding some scopes from
//my personal tutor only copied the code that my professor provided to complete my workshopsand assignments.  
// (can provide tutor details upon request.)


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