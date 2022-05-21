


#include "Pair.h"

using namespace std;


namespace sdds
{

    bool Pair::haveSameKey(const Pair& L, const Pair& M) {
        bool res = false;
        if (L.m_key == M.m_key) {
            res = true;
        }
        return res;
    }

    std::ostream& Pair::display(std::ostream& ostr) const {
        ostr.width(20);
        ostr.setf(ios::right);
        ostr << getKey();
        ostr.setf(ios::left);
        ostr << ": " << getValue();
        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr, const Pair& L) {
        return L.display(ostr);
    }
}