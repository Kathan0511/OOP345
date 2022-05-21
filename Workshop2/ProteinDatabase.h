 



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
