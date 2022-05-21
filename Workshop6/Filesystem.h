


#ifndef SDDS_FILE_SYSTEM_H
#define SDDS_FILE_SYSTEM_H

#include "Resource.h"
#include "Flags.h"
#include "File.h"
#include "Directory.h"

namespace sdds
{
    class Filesystem
    {
        Directory* m_root{};
        Directory* m_current{};

        size_t CountResources(const char* SrcFile);

    public:
        Filesystem() {};

        Filesystem(const char* SrcFile, const std::string& rootName = "");
        Filesystem(const Filesystem& src) = delete;
        Filesystem(Filesystem&& src);
        Filesystem& operator=(const Filesystem& src) = delete;
        Filesystem& operator=(Filesystem&& src);
        ~Filesystem();

        Filesystem& operator+=(Resource*);
        Directory* change_directory(const std::string& redirectNewDir = "");
        Directory* get_current_directory() const;


    };
}
#endif