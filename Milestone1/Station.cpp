 


#define _CRT_SECURE_NO_WARNINGS
#include "Station.h"
#include "Utilities.h"
#include <iomanip>

size_t sdds::Station::m_widthField = 0;
int sdds::Station::id_generator = 0;

sdds::Station::Station(const std::string& str) :id(++id_generator)

{
    Utilities Utility;
    size_t m_New = 0;
    bool more = false;
    std::string data[4];

    for (size_t i = 0; i < 3; i++)
        data[i] = Utility.extractToken(str, m_New, more);
    m_widthField = std::max(m_widthField, Utility.getFieldWidth());
    data[3] = Utility.extractToken(str, m_New, more);

    this->StatName = data[0];
    this-> nextItem_number = (size_t)std::stoi(data[1]);
    this->StatStock = (size_t)std::stoi(data[2]);
    this->StatDesc = data[3];

}

void sdds::Station::display(std::ostream& os, bool state) const

{

    os << std::setw(3) << std::setfill('0') << id << " | ";
    os << std::setw(m_widthField + 1) << std::setfill(' ') << std::left << StatName << " | " << std::right;
    os << std::setw(6) << std::setfill('0') <<  nextItem_number << " | " << std::setfill(' ');

    if (state)
    {
        os << std::setw(4) << StatStock << " | ";
        os << StatDesc;
    }

    os << std::endl;
}

const std::string& sdds::Station::getItemName() const
{
    return this->StatName;
}


size_t sdds::Station::getNextSerialNumber()
{
    return  nextItem_number++;
}


size_t sdds::Station::getQuantity() const
{
    return this->StatStock;
}


void sdds::Station::updateQuantity()
{
    if (StatStock != 0)
        StatStock--;
}
