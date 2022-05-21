//==============================================
//Name: Kathan Patel           
//Student ID: 148609191       
//Email: kjpatel30@myseneca.ca            
//Section: NEE        
//Date: 27/03/2022               
//==============================================

//I have done mostly all the coding by myselfand took some help for understanding some scopes from
//my personal tutor only copied the code that my professor provided to complete my workshopsand assignments.  
// (can provide tutor details upon request.)



#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <algorithm>
#include "Utilities.h"
#include <stdexcept>


char sdds::Utilities::m_delimiter;

void sdds::Utilities::setWidthField(size_t newDimension)
{

    this->m_widthField = newDimension;

}

size_t sdds::Utilities::getFieldWidth()
{

    return this->m_widthField;

}


std::string sdds::Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{

    if (next_pos >= str.size())
    {
        more = false;
        return "";
    }

    char m_delimiter = this->getDelimiter();

    if (str[next_pos] == m_delimiter)
    {
        more = false;
        throw std::invalid_argument("Position is not valid");
    }


    std::string adjust;
    while (next_pos < str.size() && str[next_pos] != m_delimiter)
        adjust.push_back(str[next_pos++]);

    while (adjust.size() && adjust.back() == ' ')
        adjust.pop_back();

    while (adjust.size() && adjust.front() == ' ')
        adjust.erase(adjust.begin());

    next_pos++;

    if (next_pos >= str.size())
        more = false;
    else
        more = true;
    if (m_widthField < adjust.size())
        m_widthField = adjust.size();
    return adjust;

}

void sdds::Utilities::setDelimiter(char newDelimiter)
{

    m_delimiter = newDelimiter;

}

char sdds::Utilities::getDelimiter()
{

    return m_delimiter;

}