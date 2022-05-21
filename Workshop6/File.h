

#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <iostream>
#include "Resource.h"
#include "Flags.h"
namespace sdds
{
    class File : public Resource
    {
        std::string m_contents;
    public:
        File() {};
        File(const std::string& Files_Name, const std::string& theContent = "");
        void update_parent_path(const std::string&);
        std::string name() const;
        int count() const;
        std::string path() const;
        size_t size() const;
        NodeType type() const;
    };

}

#endif