#pragma once
#include "StringList.h"

#include <fstream>
#include <string>

const uint32_t INVALID_OFFSET = std::numeric_limits<uint32_t>::max();

struct Read
{
    uint32_t offset = INVALID_OFFSET;
    std::string str;
};

struct Header
{
    uint32_t first_line = INVALID_OFFSET;
    uint32_t removed_line = INVALID_OFFSET;
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
