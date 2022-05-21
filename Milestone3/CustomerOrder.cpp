 


#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <utility>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
using namespace sdds;
size_t CustomerOrder::m_widthField = 0;
CustomerOrder::CustomerOrder() :
    m_name{},
    m_product{},
    m_cntItem{},
    m_lstItem{ nullptr } {}

CustomerOrder::CustomerOrder(const string& input) 
{
    Utilities utility;
    size_t pos = 0;
    bool more = true;
    m_name = utility.extractToken(input, pos, more);
    m_product = utility.extractToken(input, pos, more);
    string ItemsAvailable = "";
    size_t Counts = 0;
    do 
    {
        string Sln = utility.extractToken(input, pos, more);
        if (ItemsAvailable.length() > 0) {
            ItemsAvailable += Utilities::getDelimiter();
        }
        ItemsAvailable += Sln;
        Counts++;
    } while (more);
    m_lstItem = new Item * [Counts];
    m_cntItem = Counts;
    pos = 0; Counts = 0; more = true;
    do {
        string Sln = utility.extractToken(ItemsAvailable, pos, more);
        m_lstItem[Counts++] = new Item(Sln);
    } while (more);
    if (m_widthField < utility.getFieldWidth()) {
        m_widthField = utility.getFieldWidth();
    }
}

CustomerOrder::CustomerOrder(const CustomerOrder& order) {
    throw string("Copy constructor cannot be called");
}
CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept :
    m_name{}, 
    m_product{}, 
    m_cntItem{}, 
    m_lstItem{ nullptr } 
{
    *this = move(order);
}
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept 
{
    if (this == &order) {
        return *this;
    }
    swap(m_name, order.m_name);
    swap(m_product, order.m_product);
    swap(m_cntItem, order.m_cntItem);
    swap(m_lstItem, order.m_lstItem);
    return *this;
}

CustomerOrder::~CustomerOrder() {
    for (size_t i = 0; i < m_cntItem; i++) {
        delete m_lstItem[i];
    }
    delete[] m_lstItem;
}
bool CustomerOrder::isOrderFilled() const {
    size_t Counts = 0;
    for (size_t i = 0; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_isFilled) {
            Counts++;
        }
    }
    return Counts == m_cntItem;
}
bool CustomerOrder::isItemFilled(const string& itemName) const {
    size_t ItemCounts = 0;
    size_t FilledCounts = 0;
    for (size_t i = 0; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_itemName == itemName) {
            ItemCounts++;

            if (m_lstItem[i]->m_isFilled) {
                FilledCounts++;
            }
        }
    }
    return ItemCounts == FilledCounts;
}

void CustomerOrder::fillItem(Station& station, ostream& os) {
    for (size_t i = 0; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_isFilled == false && m_lstItem[i]->m_itemName == station.getItemName()) {
            if (station.getQuantity() > 0) {
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                station.updateQuantity();
                os << setw(11) << right;
                os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                break;
            }
            else {

                os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;

            }
        }
    }


}

void CustomerOrder::display(ostream& os) const {
    os << m_name << " - " << m_product << endl;

    for (size_t i = 0; i < m_cntItem; i++) {
        os << std::right;
        os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
        os << setfill(' ') << left;
        os << setw(m_widthField + 2) << m_lstItem[i]->m_itemName << " - ";
        os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
        os << endl;
    }
}
