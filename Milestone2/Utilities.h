 



#define _CRT_SECURE_NO_WARNINGS
#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>

namespace sdds
{
    class Utilities
    {

    private:       
        static char m_delimiter;
        size_t m_widthField = 1;

    public:
        
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
        void setWidthField(size_t);
        size_t getFieldWidth();

    };
}
#endif  
