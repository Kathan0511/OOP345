


#ifndef SDDS_CENTRAL_UNIT_H
#define SDDS_CENTRAL_UNIT_H
#include <string>
#include <iostream>
#include <exception>
#include <fstream>
#include <utility>
#include "Job.h"

namespace sdds
{
    template<typename T>
    class CentralUnit
    {
        std::string m_type;
        T** m_items;
        static const int MAX_JOBS = 4;
        Job* m_jobs[MAX_JOBS];
        size_t m_size;
        size_t m_count;
        size_t m_max;



    public:
        std::ostream& log = std::cout;
        CentralUnit(std::string, std::string);
        CentralUnit(const CentralUnit&);
        CentralUnit(CentralUnit&&);
        CentralUnit& operator=(const CentralUnit&) = delete;
        CentralUnit& operator=(CentralUnit&&);
        CentralUnit& operator+=(std::string);
        ~CentralUnit();
        void run();
        bool has_jobs() const;
        size_t get_available_units() const;
        std::string readLine(std::string, unsigned int&);
        void complete_job(CentralUnit&, T*);
        void operator+=(T*);
        T* operator[](std::string) const;
        void display() const;
    };
};

template<typename T>
std::string sdds::CentralUnit<T>::readLine(std::string nextline, unsigned int& pos) {
    char cur = nextline[pos];
    std::string input = "";


    while (pos < nextline.length()) {
        if (cur != ' ') {
            if (cur == '|') {
                break;
            }
            else {
                input += cur;
            }
        }
        cur = nextline[++pos];
    }
    pos++;
    return input;
}

template<typename T>
sdds::CentralUnit<T>::CentralUnit(std::string type, std::string filename) :
    m_type{ type }, m_items{ nullptr }, m_size{ 0 }, m_count{ 0 } {

    unsigned int index = 0, capacity = 0;
    std::string unitType, unitName;
    std::ifstream ifile(filename);
    std::string nextline;

    if (ifile.is_open()) {
        while (ifile) {
            std::getline(ifile, nextline);

            if (ifile) {
                index++;
            }
        }

        m_items = new T * [index];
        m_size = index;
        m_max = index;
        ifile.clear();
        ifile.seekg(0, std::ios::beg);
        index = 0;

        while (ifile) {
            std::getline(ifile, nextline);

            if (!ifile) {
                break;
            }

            unsigned int pos = 0;
            unitType = readLine(nextline, pos);
            unitName = readLine(nextline, pos);

            try {
                capacity = std::stoi(readLine(nextline, pos));
            }
            catch (std::invalid_argument& error) {
                capacity = 1;
            }

            T* t = new T(this, unitType, unitName, capacity);
            t->on_complete(&sdds::CentralUnit<T>::complete_job);
            t->on_error([this](T* unit) {
                this->log << "Failed to complete job " << unit->get_current_job()->name() << std::endl;
                this->log << (get_available_units() + 1) << " units available." << std::endl;
                });

            m_items[index] = t;
            index++;
        }
    }
    else {
        throw std::invalid_argument("File cannot be opened.");
    }

}

template<typename T>
sdds::CentralUnit<T>::CentralUnit(sdds::CentralUnit<T>&& unit) {
    *this = unit;
}

template<typename T>
sdds::CentralUnit<T>::CentralUnit(const sdds::CentralUnit<T>& unit) {
    throw std::string("Cannot create a new instance from a copy");
}

template<typename T>
sdds::CentralUnit<T>& sdds::CentralUnit<T>::operator=(sdds::CentralUnit<T>&& unit) {
    if (this == &unit) {
        return *this;
    }

    std::swap(m_type, unit.m_type);
    std::swap(m_items, unit.m_items);
    std::swap(m_jobs, unit.m_jobs);
    std::swap(m_size, unit.m_size);
    std::swap(m_max, unit.m_max);
    std::swap(m_count, unit.m_count);
    return *this;
}

template<typename T>
sdds::CentralUnit<T>& sdds::CentralUnit<T>::operator+=(std::string job) {
    if (m_count >= MAX_JOBS) {
        throw std::string("Job queue full!");
    }

    m_jobs[m_count++] = new Job(job);
    return *this;
}

template<typename T>
void sdds::CentralUnit<T>::run() {
    for (size_t i = 0; i < m_size; i++) {
        if (!(*m_items[i]) && m_count > 0) {
            (*m_items[i]) += m_jobs[m_count - 1];
            m_jobs[--m_count] = nullptr;
        }

        (*m_items[i])();
    }
}

template<typename T>
bool sdds::CentralUnit<T>::has_jobs() const {
    size_t job_count = 0;

    for (size_t i = 0; i < m_size; i++) {
        if (*m_items[i]) {
            job_count++;
        }
    }

    return job_count + m_count;
}

template<typename T>
size_t sdds::CentralUnit<T>::get_available_units() const {
    size_t available_count = 0;

    for (size_t i = 0; i < m_size; i++) {
        if (!(*m_items[i])) {
            available_count++;
        }
    }
    return available_count;
}

template<typename T>
sdds::CentralUnit<T>::~CentralUnit() {
    for (size_t i = 0; i < m_size; i++) {
        delete m_items[i];
    }

    delete[] m_items;

    for (size_t i = 0; i < m_count; i++) {
        delete m_jobs[i];
    }
}

template<typename T>
void sdds::CentralUnit<T>::complete_job(CentralUnit<T>& unit, T* t) {
    for (size_t i = 0; i < m_size; i++) {
        if (unit.m_items[i] == t) {
            unit.m_items[i]->complete_job();
            log << get_available_units() << " units available." << std::endl;
        }
    }
}

template<typename T>
void sdds::CentralUnit<T>::display() const {
    log << "Central " << m_type << " Unit list" << std::endl;

    for (size_t i = 0; i < m_size; i++) {
        log << "[" << std::setfill('0') << std::setw(4) << (i + 1) << "] " << (*m_items[i]) << std::endl;
    }
}

template<typename T>
void sdds::CentralUnit<T>::operator+=(T* t) {
    if (!(*t)) {
        if (m_size == m_max) {
            m_max *= 2;
            T** temp = m_items;
            m_items = new T * [m_max];

            for (size_t i = 0; i < m_size; i++) {
                m_items[i] = temp[i];
            }
            delete[] temp;
        }

        t->on_complete(&sdds::CentralUnit<T>::complete_job);
        t->on_error([this](T* unit) {
            this->log << "Failed to complete job " << unit->get_current_job()->name() << std::endl;
            this->log << (get_available_units() + 1) << " units available." << std::endl;
            });
        m_items[m_size++] = t;
    }
    else {
        throw std::string("Unit is not available");
    }
}

template<typename T>
T* sdds::CentralUnit<T>::operator[](std::string JobTitle) const {
    for (size_t i = 0; i < m_size; i++) {
        if (*m_items[i] && m_items[i]->get_current_job()->name() == JobTitle) {
            return m_items[i];
        }
    }
    throw std::out_of_range("Job is not being handled by a unit.");
}

#endif