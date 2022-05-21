 


#ifndef SDDS_ELEMENT_H
#define SDDS_ELEMENT_H

#include <iomanip>
#include <string>
#include <fstream>

extern const int FWC;
extern const int FWD;
extern const int FWP;

namespace sdds
{

	struct Description
	{
		unsigned prod_code;
		std::string desc;
		bool load(std::ifstream& f) {
			f >> prod_code >> desc;
			return f.good();
		}

		void display(std::ostream& os) const {
			os << std::setw(FWC) << prod_code
				<< std::setw(FWD) << desc
				<< std::endl;
		}
	};

	struct Price
	{
		unsigned prod_code;
		double price;
		bool load(std::ifstream& f) {
			f >> prod_code >> price;
			return f.good();
		}

		void display(std::ostream& os) const {
			os << std::setw(FWC) << prod_code << std::setw(FWP)
				<< price << std::endl;
		}
	};

	struct Product
	{
		std::string m_desc{};
		double Price{};
		int Pro_ID{};
		static size_t idGenerator;
		static bool Trace;

		Product() {
			Pro_ID = ++Product::idGenerator;
			if (Product::Trace)
				std::cout << "    DC [" << Pro_ID << "]" << std::endl;
		}


		Product(const Product& other) {
			this->m_desc = other.m_desc;
			this->Price = other.Price;
			Pro_ID = ++Product::idGenerator;
			if (Product::Trace)
				std::cout << "    CC [" << Pro_ID
				<< "] from [" << other.Pro_ID << "]"
				<< std::endl;
		}

		Product(const std::string& str, double Prot) {
			this->m_desc = str;
			this->Price = Prot;
			Pro_ID = ++Product::idGenerator;
			if (Product::Trace)
				std::cout << "     C [" << Pro_ID << "]" << std::endl;
		}

		~Product() {
			if (Product::Trace)
				std::cout << "    ~D [" << Pro_ID << "]" << std::endl;
		}		
		void validate() {
			std::string message = "*** Negative prices are invalid ***";
			if (Price < 0) {
				throw message;
			}
		}
		void display(std::ostream& os) const {
			os << std::setw(FWD) << m_desc
				<< std::setw(FWP) << Price
				<< std::endl;
		}
	};
}
#endif