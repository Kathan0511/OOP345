



#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include "Pair.h"
#include <string>


namespace sdds
{

    template<class T, size_t Capacity>

    class Collection
    {
    protected:
        T array[Capacity];
        size_t ElementNum{ 0 };
        T ObjDummy{};

    public:
        Collection() {}

        virtual ~Collection() {}

        size_t size()
        {
            return ElementNum;
        }

        void display(std::ostream& ostr = std::cout)const {
            ostr << "----------------------" << std::endl;
            ostr << "|" << " Collection Content " << "|" << std::endl;
            ostr << "----------------------" << std::endl;
            for (size_t i = 0; i < ElementNum; i++) {
                ostr << array[i] << std::endl;
            }
            ostr << "----------------------" << std::endl;
        }

        virtual bool add(const T& item) {
            bool res = false;
            if (ElementNum < Capacity) {
                array[ElementNum] = item;
                ElementNum++;
                res = true;
            }
            return res;
        }

        T& operator[](int index) {
            if (index >= 0 && (unsigned)index < ElementNum) {
                return array[index];
            }
            return ObjDummy;
        }

    };

    template<> Collection<Pair, 100>::Collection() {
        Pair a("No Key", "No Value");
        ObjDummy = a;

    };

}
#endif 