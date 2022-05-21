


#include <iostream>
#include "File.h"

namespace sdds
{
    File::File(const std::string& Files_Name, const std::string& theContent)
    {
        Resource::m_name = Files_Name;
        m_contents = theContent;
    }
    void File::update_parent_path(const std::string& path) {
        Resource::m_parent_path = path;
    }
    std::string File::name() const {
        return Resource::m_name;
    }
    int File::count() const {
        return -1;
    }
    std::string File::path() const {
        return Resource::m_parent_path + Resource::m_name;
    }
    size_t File::size() const {
        return m_contents.size();
    }
    NodeType File::type() const {
        return NodeType::FILE;
    }

}