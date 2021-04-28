#pragma once
#include "StringList.h"

#include <fstream>
#include <string>

#define INVALID -1
#define SIZE 32

struct List
{
    long offset = INVALID;
    char str[SIZE] = "\0";
};

struct Header
{
    long first_line = INVALID;
    long removed_line = INVALID;
};

class FileStringList : public StringList
{
public:
    FileStringList(std::string m_file_name);
    bool insert(const std::string &s, uint32_t pos) override;
    bool remove(uint32_t pos) override;
    std::string &string(uint32_t pos) override;

private:
    std::string m_file_name;
    std::fstream m_file;
};
