//==============================================
//Name: Kathan Patel           
//Student ID: 148609191       
//Email: kjpatel30@myseneca.ca            
//Section: NEE        
//Date: 14/03/2022               
//==============================================

//I have done mostly all the coding by myselfand took some help for understanding some scopes from
//my personal tutor only copied the code that my professor provided to complete my workshopsand assignments.  
// (can provide tutor details upon request.)


#include <iostream>
#include <fstream>
#include "Filesystem.h"

namespace sdds
{


    size_t Filesystem::CountResources(const char* SrcFile) {
        std::ifstream Ifstm;
        Ifstm.open(SrcFile);
        std::string RawfileData;
        size_t count = 0;
        if (Ifstm.fail()) {
            throw std::invalid_argument("File cannot be opened.");
        }
        else { 
            do {
                std::getline(Ifstm, RawfileData);
                count++;
            } while (Ifstm.good());
        }
        return count;
        Ifstm.clear();
        Ifstm.close();
        return count;
    }

    Filesystem::Filesystem(const char* SrcFile, const std::string& rootName) {
        if (SrcFile != nullptr && SrcFile[0] != '\0') {
            std::ifstream Ifstm;
            Ifstm.open(SrcFile);
            if (Ifstm.fail()) {
                throw std::invalid_argument("File cannot be opened.");
            }
            else {
                m_root = new Directory(rootName);
                m_current = m_root;
                size_t count;
                count = CountResources(SrcFile);
                std::string RawfileData;
                std::string Folders_file;
                std::string Files;
                std::string blankWhitespaces(" ");

                for (size_t i = 0; i < count; i++) {
                    std::getline(Ifstm, RawfileData);
                    bool done = false;
                    done = RawfileData.find_first_of("/") != std::string::npos ? false : true;

                    while (!done) {
                        Folders_file = RawfileData.substr(0, RawfileData.find_first_of("/") + 1);

                        Folders_file = Folders_file.substr(Folders_file.find_first_not_of(" "));
                        Folders_file.erase(Folders_file.find_last_not_of(blankWhitespaces) + 1);  
                        RawfileData = RawfileData.substr(RawfileData.find_first_of("/") + 1);  
                        done = RawfileData.find_first_of("/") != std::string::npos ? false : true;
                        if (!Folders_file.empty() && m_current->find(Folders_file) == nullptr) {
                            *m_current += new Directory(Folders_file);
                        }
                        m_current = static_cast<Directory*>(m_current->find(Folders_file));

                    }

                    done = RawfileData.find_first_of("|") != std::string::npos ? false : true;
                    if (!done) {
                        Files = RawfileData.substr(0, RawfileData.find_first_of("|") - 1);
                        Files = Files.substr(Files.find_first_not_of(" ")); 
                        Files.erase(Files.find_last_not_of(blankWhitespaces) + 1);  
                        RawfileData = RawfileData.substr(RawfileData.find_first_of("|") + 1);  
                        RawfileData = RawfileData.substr(RawfileData.find_first_not_of(" ")); 
                        RawfileData.erase(RawfileData.find_last_not_of(blankWhitespaces) + 1);  
                        if (!Files.empty() && m_current->find(Files) == nullptr) {
                            *m_current += new File(Files, RawfileData);
                        }
                    }
                    m_current = m_root;
                }
            }
            Ifstm.clear();
            Ifstm.close();
        }
    }

    Filesystem::Filesystem(Filesystem&& src) {}

    Filesystem& Filesystem::operator=(Filesystem&& src) {
        if (this != &src) {
            delete m_root;
            m_root = src.m_root;
            src.m_root = nullptr;
            delete m_current;
            m_current = src.m_current;
            src.m_current = nullptr;
        }
        return *this;
    }

    Filesystem::~Filesystem() {
        delete m_root;}

    Filesystem& Filesystem::operator+=(Resource* ResourceAdd) {
        *m_current += ResourceAdd;
        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& redirectNewDir) {
        if (redirectNewDir.empty()) {
            m_current = m_root;
        }
        else {
            if (m_current->find(redirectNewDir) != nullptr) {
                m_current = static_cast<Directory*>(m_current->find(redirectNewDir));
            }
            else {
                throw std::invalid_argument("Cannot change directory! DIR_NAME not found!");
            }
        }
        return m_current;
    } Directory* Filesystem::get_current_directory() const {
        return m_current;
    }


}