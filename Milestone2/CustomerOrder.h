 



#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Station.h"


namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber = 0;
		bool m_isFilled = false;
		Item(const std::string& src) : m_itemName(src)
		{};
	};

	class CustomerOrder
	{

		std::string m_name;
		std::string m_product;
		unsigned int m_cntItem{ 0 };
		Item** m_lstItem{ nullptr };
		static size_t m_widthField;

	public:

		CustomerOrder();
		CustomerOrder(const std::string&);
		CustomerOrder& operator=(CustomerOrder&) = delete;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;
		void display(std::ostream& os) const;
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder(CustomerOrder&);
		bool isItemFilled(const std::string&) const;

		~CustomerOrder();		 
		bool isOrderFilled() const;
		void fillItem(Station&, std::ostream& os);
		 
	};
}
#endif