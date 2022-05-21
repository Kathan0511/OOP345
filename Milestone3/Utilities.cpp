 



#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Utilities.h"

char sdds::Utilities::m_delimiter = '|';
void sdds::Utilities::setFieldWidth(size_t newWidth) {
    m_widthField = newWidth;
}
size_t sdds::Utilities::getFieldWidth() const {
    return m_widthField;
}
string sdds::Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {

    if (str[next_pos] == m_delimiter || next_pos >= str.length()) {
        more = false;
        throw invalid_argument("Invalid next_pos arguement");
    }

    string tkn = "";
    string BlankWhite = "";

    while (next_pos < (size_t)str.length()) {
        if (str[next_pos] != ' ') {
            if (str[next_pos] == '\n' || str[next_pos] == '\r') {
                break;
            }
            else if (str[next_pos] == m_delimiter) {
                if (m_widthField < tkn.length()) {
                    m_widthField = tkn.length();
                }
                more = true;
                next_pos++;
                return tkn;
            }
            else {
                if (tkn.length() > 0) {
                    tkn += BlankWhite + str[next_pos];
                    BlankWhite = "";
                }
                else {
                    tkn += str[next_pos];
                    BlankWhite = "";
                }

                if (next_pos == (size_t)str.length() - 1) {
                    if (m_widthField < tkn.length()) {
                        m_widthField = tkn.length();
                    }
                    more = false;
                    next_pos++;
                    return tkn;
                }
            }
        }
        else {
            BlankWhite += ' ';
        }
        next_pos++;
    }

    more = false;
    return tkn;
}
