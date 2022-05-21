 



#define _CRT_SECURE_NO_WARNINGS
#ifndef STATION_H
#define STATION_H
#include <iostream>
#include <string>

namespace sdds
{
    class Station
    {

    private:
        const int id;
        std::string StatName;
        std::string StatDesc;
        size_t nextItem_number;
        size_t StatStock;
        static int id_generator;

    public:
        void display(std::ostream& os, bool full) const;
        static size_t m_widthField;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        Station(const std::string&);
        const std::string& getItemName() const;
        void updateQuantity();
         
    };
}
#endif  
