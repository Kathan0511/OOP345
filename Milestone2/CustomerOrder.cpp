 



#include <iomanip>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "Utilities.h"
#include "CustomerOrder.h"
#include "Station.h"


using namespace std;

namespace sdds

{

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder() {}
    CustomerOrder::CustomerOrder(const std::string& src)

    {
        Utilities Utility;
        size_t next_pos = 0;
        bool more = false;

        if (src.empty())
        {
            m_name = "";
            m_product = "";
            m_cntItem = 0;
            m_lstItem = nullptr;
        }
        else
        {
            m_name = Utility.extractToken(src, next_pos, more);
            if (more) {
                m_product = Utility.extractToken(src, next_pos, more);
            }
            std::string strItems = src.substr(next_pos, src.length() - next_pos);
            m_cntItem = (std::count(strItems.begin(), strItems.end(), Utility.getDelimiter())) + 1;
            m_lstItem = new Item * [m_cntItem];
            for (size_t k = 0u; k < m_cntItem && more; k++)
                m_lstItem[k] = new Item(Utility.extractToken(src, next_pos, more));
            if (m_widthField < Utility.getFieldWidth())
                m_widthField = Utility.getFieldWidth();
        }
    }


    bool CustomerOrder::isOrderFilled() const
    {
        bool Cleared = true;
        for (unsigned int m = 0; m < m_cntItem; m++)
        {
            if (!m_lstItem[m]->m_isFilled)
                Cleared = false;
        }
        return Cleared;
    }


    bool CustomerOrder::isItemFilled(const std::string& Itname) const
    {
        for (unsigned int l = 0; l < m_cntItem; l++)
        {
            if (m_lstItem[l]->m_itemName == Itname)
                return m_lstItem[l]->m_isFilled;
        }
        return true;
    }

    CustomerOrder::~CustomerOrder()
    {
        for (auto m = 0u; m < m_cntItem; ++m)
            delete m_lstItem[m];
        delete[] m_lstItem;
    }


    CustomerOrder::CustomerOrder(CustomerOrder&)
    {
        throw "ERROR:  Copy is not allowed!";
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& cpy) noexcept
    {
        *this = std::move(cpy);
    }


    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cpy) noexcept
    {
        if (this != &cpy)
        {
            for (auto m = 0u; m < m_cntItem; ++m)
                delete m_lstItem[m];
            delete[] m_lstItem;
            m_name = cpy.m_name;
            m_product = cpy.m_product;
            m_cntItem = cpy.m_cntItem;
            m_lstItem = cpy.m_lstItem;
            cpy.m_cntItem = 0;
            cpy.m_lstItem = nullptr;
        }
        return *this;
    }
    

    void CustomerOrder::fillItem(Station& st, std::ostream& os)
    {
        for (unsigned int k = 0; k < m_cntItem; k++)
        {
            if (m_lstItem[k]->m_itemName == st.getItemName())
            {
                if (st.getQuantity() > 0)
                {
                    m_lstItem[k]->m_serialNumber = st.getNextSerialNumber();
                    m_lstItem[k]->m_isFilled = true;
                    st.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[k]->m_itemName << "]" << std::endl;
                }
                else
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[k]->m_itemName << "]" << std::endl;
                }
            }
        }
    }


    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << m_product << std::endl;
        for (unsigned int m = 0; m < m_cntItem; m++)
        {
            os << "[" << setw(6) << setfill('0') << right << m_lstItem[m]->m_serialNumber << "] "
                << setfill(' ') << setw(m_widthField) << left << m_lstItem[m]->m_itemName << "   - ";
            if (m_lstItem[m]->m_isFilled) {
                os << "FILLED" << std::endl;
            }
            else
            {
                os << "TO BE FILLED" << std::endl;
            }
        }
    }
}
