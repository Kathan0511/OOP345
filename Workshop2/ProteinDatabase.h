//==============================================
//Name: Kathan Patel           
//Student ID: 148609191       
//Email: kjpatel30@myseneca.ca            
//Section: NEE        
//Date: 30/01/2022               
//==============================================


//I have done mostly all the coding by myselfand took some help for understanding some scopes from
//my personal tutor only copied the code that my professor provided to complete my workshopsand assignments.  
// (can provide tutor details upon request.)



#include <iostream>

#ifndef SDDS_PROTEINDATABASE_H_
#define SDDS_PROTEINDATABASE_H_

namespace sdds
{
	class ProteinDatabase
	{
	public:

		std::string* CountRecord = nullptr;
		long unsigned int arrLength = 0;
		long unsigned int Index = 0;

		ProteinDatabase();
		~ProteinDatabase();
		ProteinDatabase(char* File_name);
		size_t size();
		std::string operator[](size_t);

		ProteinDatabase(const ProteinDatabase& src);
		ProteinDatabase(ProteinDatabase&& src);

		ProteinDatabase& operator=(const ProteinDatabase&);
		ProteinDatabase& operator=(ProteinDatabase&&);
	private:

	};

}
#endif