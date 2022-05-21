 


#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

size_t sdds::Station::m_widthField = 0;
int sdds::Station::id_generator = 0;

sdds::Station::Station(const string& record) {
    Utilities Utlty;
    size_t next_pos = 0;
    bool more = true;

    StationID = ++id_generator;
    StationName = Utlty.extractToken(record, next_pos, more);
    NxtSerialNo = stoi(Utlty.extractToken(record, next_pos, more));
    NumOfStock = stoi(Utlty.extractToken(record, next_pos, more));
    m_widthField = m_widthField > Utlty.getFieldWidth() ? m_widthField : Utlty.getFieldWidth();
    StationDesc = Utlty.extractToken(record, next_pos, more);
}

const string& sdds::Station::getItemName() const {
    return StationName;
}
size_t sdds::Station::getNextSerialNumber() {
    return NxtSerialNo++;
}
size_t sdds::Station::getQuantity() const {
    return NumOfStock;
}
void sdds::Station::updateQuantity() {
    if (NumOfStock > 0) {
        NumOfStock--;
    }
}

void sdds::Station::display(ostream& os, bool full) const {
    os << std::right;
    os << setw(3) << setfill('0') << StationID << " | ";
    os << left << setfill(' ') << setw(m_widthField + 1) << StationName << " | ";
    os << right << setw(6) << setfill('0') << NxtSerialNo << " | ";

    if (full) {
        os << setfill(' ');
        os << right;
        os << setw(4) << NumOfStock << " | " << StationDesc;
    }

    os << endl;
}

