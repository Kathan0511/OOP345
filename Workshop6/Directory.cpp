


#include <iostream>
#include <iomanip>
#include "Directory.h"
#include "File.h"


namespace sdds
{
    Directory::Directory(const std::string& FolderfileName) {
        Resource::m_name = FolderfileName;
    }

    void Directory::update_parent_path(const std::string& path) {
        Resource::m_parent_path = path;
        for (auto i = m_contents.begin(); i != m_contents.end(); i++) {
            (*i)->update_parent_path(Resource::m_parent_path + name());
        }
    }

    std::string Directory::name() const {
        return Resource::m_name;
    }
    int Directory::count() const {
        return m_contents.size();
    }
    std::string Directory::path() const {
        return Resource::m_parent_path + Resource::m_name;
    }
    size_t Directory::size() const {
        size_t directorySIZE = 0u;
        for (auto i = m_contents.begin(); i != m_contents.end(); i++) {
            directorySIZE += (*i)->size();
        }
        return directorySIZE;
    }

    NodeType Directory::type() const {
        return NodeType::DIR;
    }
    Directory::~Directory() {
        for (auto i = m_contents.begin(); i != m_contents.end(); i++) {
            delete (*i);
        }
    }


    Directory& Directory::operator+=(Resource* NewResrc) {
        bool ExResrc = false;
        for (auto i = m_contents.begin(); i != m_contents.end(); i++) {
            if ((*i)->name().compare(NewResrc->name()) == 0) {
                ExResrc = true;
                throw ("");
            }
        }
        if (!ExResrc) {
            m_contents.push_back(NewResrc);
            m_contents.back()->update_parent_path(m_parent_path + name());
        }
        return *this;
    }

    Resource* Directory::recusiveFind(Resource* IN, const std::string& resource) {
        static Resource* ResrcFound = nullptr;
        Directory* Convert = (Directory*)IN;
        for (auto i = Convert->m_contents.begin(); !ResrcFound && i != Convert->m_contents.end(); i++) {
            if (!((*i)->type() == NodeType::DIR)) {
                auto a = (*i)->name().compare(resource);
                if (a == 0) {
                    ResrcFound = (*i);
                }
            }
            else {
                recusiveFind((*i), resource);
            }
        }
        return ResrcFound;
    }

    Resource* Directory::find(const std::string& resource, const std::vector<OpFlags>& RECUSIVE) {
        Resource* ResrcLoc = nullptr;
        if (!RECUSIVE.empty()) {
            ResrcLoc = recusiveFind(this, resource);
        }
        else {
            for (auto i = m_contents.begin(); i != m_contents.end(); i++) {
                if ((*i)->name().compare(resource) == 0) {
                    ResrcLoc = (*i);
                }
            }
        }
        return ResrcLoc;
    }

    void Directory::remove(const std::string& resource, const std::vector<OpFlags>& RECUSIVE) {
        bool isExisted = false;
        for (auto i = m_contents.begin(); i != m_contents.end(); i++) {
            if ((*i)->name().compare(resource) == 0) {
                if ((*i)->type() == NodeType::DIR && RECUSIVE.empty()) {
                    throw std::invalid_argument("NAME is a directory. Pass the recursive flag to delete directories.");
                }
                else {
                    isExisted = true;
                    delete (*i);
                    i = m_contents.erase(i);
                }
            }
        }
        if (!isExisted) {
            throw std::string("NAME does not exist in DIRECTORY_NAME");
        }

    }
    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& format) const {
        os << "Total size: " << std::setw(2) << size() << " bytes" << std::endl;
        for (auto i = m_contents.begin(); i != m_contents.end(); i++) {
            std::string type = (*i)->type() == NodeType::FILE ? "F | " : "D | ";
            os << type << std::setw(15) << std::left << (*i)->name() << " |";
            if (!format.empty()) {
                os << " " << std::right << std::setw(2);
                if ((*i)->count() >= 0) {
                    os << (*i)->count();
                }
                else {
                    os << "  ";
                }
                os << " | " << std::setw(2) << std::right << std::setw(4) << (*i)->size() << " bytes | ";
            }
            os << std::endl;
        }
    }
}