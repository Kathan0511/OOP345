

#include "Processor.h"
sdds::Processor::Processor(CentralUnit<Processor>* host, std::string brand, std::string code, int power) :
    m_host{ host }, m_brand{ brand }, m_code{ code }, m_power{ power }, m_current{ nullptr } {}

void sdds::Processor::run() {
    if (m_host == nullptr || m_current == nullptr) {
        return;
    }

    try {
        (*m_current)(m_power);

        if (!m_current->is_active()) {
            delete m_current;
            m_current = nullptr;
        }
    }
    catch (std::underflow_error& error) {
        m_host->log << "Processed over quota for ";
        m_current->display(m_host->log);
        delete m_current;
        m_current = nullptr;
    }
}

sdds::Processor::operator bool() const {
    return m_current != nullptr;
} sdds::Processor& sdds::Processor::operator+=(Job*& job) {
    if (m_current != nullptr) {
        throw std::string("Job already assigned");
    }
    m_current = job;
    return *this;
} sdds::Job* sdds::Processor::get_current_job() const {
    return m_current;
} sdds::Processor::~Processor() {
    delete m_current;
}

void sdds::Processor::on_complete(void (sdds::CentralUnit<sdds::Processor>::* callback)(CentralUnit<Processor>&, Processor*)) {
    this->callback = callback;
} void sdds::Processor::on_error(std::function<void(Processor*)> error) {
    this->error = error;
}

void sdds::Processor::operator()() {
    if (m_host == nullptr || m_current == nullptr) {
        return;
    }

    try {
        (*m_current)(m_power);

        if (!m_current->is_active()) {
            if (callback != nullptr) {
                (m_host->*callback)(*m_host, this);
            }

            delete m_current;
            m_current = nullptr;
        }
    }
    catch (std::underflow_error& err) {
        if (error != nullptr) {
            error(this);
        }

        delete m_current;
        m_current = nullptr;
    }
}
std::ostream& sdds::operator<<(std::ostream& os, const Processor& p) {
    os << "(" << p.m_power << ") " << p.m_brand << " " << p.m_code;

    if (p.m_current != nullptr) {
        os << " processing ";
        p.m_current->display(os);
    }

    return os;
}
void sdds::Processor::complete_job() {
    m_host->log << "[COMPLETE] ";
    m_current->display(m_host->log);

    delete m_current;
    m_current = nullptr;

    m_host->log << " using " << *this << std::endl;
}
