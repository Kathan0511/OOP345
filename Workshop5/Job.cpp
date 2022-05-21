


#include <iomanip>
#include <exception>
#include "Job.h"

sdds::Job::Job() : JobTitle{ "" }, 
WorkUnits{ 0 },
remaining{ 0 }, 
flagisActive{ false } 

{

}

sdds::Job::Job(std::string JobTitle) : JobTitle{ JobTitle } {
    WorkUnits = JobTitle.length() % 10 + 1;
    remaining = WorkUnits;
    flagisActive = true;
}

bool sdds::Job::is_active() const {
    return flagisActive;
}

bool sdds::Job::is_complete() const {
    return remaining == 0;
}

std::string sdds::Job::name() const {
    return JobTitle;
}

void sdds::Job::display(std::ostream& output) const {
    output << "`" << JobTitle << "` ";
    output << "[" << std::setfill('0') << std::setw(2) << remaining << "/";
    output << std::setfill('0') << std::setw(2) << WorkUnits << " remaining]";
}

std::ostream& sdds::operator<<(std::ostream& output, Job& job) {
    job.display(output);
    return output;
}

void sdds::Job::operator()(unsigned int WorkUnits) {
    if (WorkUnits > remaining) {
        remaining = 0;
        flagisActive = false;
        throw std::underflow_error("The handled work [" + std::to_string(WorkUnits) + "], is more than the remaining work [" + std::to_string(remaining) + "].");
    }
    else {
        remaining -= WorkUnits;

        if (remaining == 0) {
            flagisActive = false;
        }
    }
}