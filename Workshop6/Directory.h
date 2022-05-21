#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H
#include <iostream>
#include <vector>
#include "Resource.h"

namespace sdds
{
    class Directory : public Resource
    {
        std::vector<Resource*> m_contents;
        Resource* recusiveFind(Resource* IN, const std::string& FindResources);

    public:
        Directory() {};
        Directory(const std::string& FolderfileName);
        Directory(const Directory&) = delete;
        Directory(Directory&&) = delete;
        Directory& operator=(const Directory&) = delete;
        Directory& operator=(Directory&&) = delete;
        virtual ~Directory();

        void update_parent_path(const std::string&);

        std::string name() const;
        int count() const;
        std::string path() const;
        size_t size() const;
        NodeType type() const;


        Directory& operator+=(Resource*);
        Resource* find(const std::string&, const std::vector<OpFlags>& RECUSIVE = {});
        void remove(const std::string&, const std::vector<OpFlags>& RECUSIVE = {});
        void display(std::ostream&, const std::vector<FormatFlags>& FORMAT = {}) const;
    };

}

#endif