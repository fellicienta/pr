#pragma once
#include "StringList.h"

#include <fstream>
#include <string>

const uint32_t INVALID_OFFSET = std::numeric_limits<uint32_t>::max();
const char SYMBOL = 0x17;

struct Header
{
    uint32_t first_record = INVALID_OFFSET;
    uint32_t removed_record = INVALID_OFFSET;
};

class FileStringList : public StringList
{
public:
    FileStringList(std::string m_file_name);
    bool insert(const std::string &s, uint32_t pos) override;
    bool remove(uint32_t pos) override;
    std::string &string(uint32_t pos) override;
    uint32_t allocate_memory(uint32_t removed_record, uint32_t str_size);

private:
    std::string m_file_name;
    std::fstream m_file;

    std::string current_string;
    uint32_t space_size;
};
