



#ifndef SDDS_PROCESSOR_H
#define SDDS_PROCESSOR_H

#include <functional>
#include <string>

#include "CentralUnit.h"
#include "Job.h"

namespace sdds
{
    class Processor
    {
        CentralUnit<Processor>* m_host;
        std::string m_brand;
        std::string m_code;
        int m_power;
        Job* m_current = nullptr;
        void (sdds::CentralUnit<sdds::Processor>::* callback)(CentralUnit<Processor>&, Processor*) = nullptr;
        std::function<void(Processor*)> error = nullptr;

    public:
        Processor(CentralUnit<Processor>* host, std::string brand, std::string code, int power);
        void run();
        explicit operator bool() const;
        Processor& operator+=(Job*& job);
        Job* get_current_job() const;
        ~Processor();
        void on_complete(void (sdds::CentralUnit<sdds::Processor>::* callback)(CentralUnit<Processor>&, Processor*));
        void on_error(std::function<void(Processor*)> error);
        void operator()();
        Job* free();
        friend std::ostream& operator<<(std::ostream&, const Processor&);
        void complete_job();
    };
    std::ostream& operator<<(std::ostream&, const Processor&);
};

#endif  