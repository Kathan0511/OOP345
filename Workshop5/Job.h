


#ifndef SDDS_JOB_H
#define SDDS_JOB_H
#include <string>
#include <iostream>
#include <iomanip>

namespace sdds
{
    class Job
    {
        std::string JobTitle;
        unsigned int WorkUnits;
        unsigned int remaining;
        bool flagisActive;
    public:
        Job();
        Job(std::string);
        bool is_complete() const;
        bool is_active() const;
        std::string name() const;
        void display(std::ostream&) const;
        void operator()(unsigned int);
    };
    std::ostream& operator<<(std::ostream&, Job&);
};

#endif