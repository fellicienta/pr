#pragma once
#include "StringList.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
    bool is_uniq(uint32_t pos);
    void deleted_pos(uint32_t offset);
};

FileStringList::FileStringList(std::string m_file_name)
    : m_file_name(m_file_name)
    , m_file(m_file_name, std::ios::binary | std::ios::in | std::ios::out)
{
    if (!m_file)
    {
        m_file.open(m_file_name, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);

        std::string header;
        uint32_t size = 80;
        header.assign(std::to_string(size + 1));
        header.append(size - header.size(), ' ');
        m_file << header << std::endl;
    }
    m_file.close();
}

bool FileStringList::insert(const std::string &s, uint32_t pos)
{
    // check if pos already exists
    if (!is_uniq(pos))
        return false;

    m_file.open(m_file_name, std::ios::binary | std::ios::out | std::ios::in);

    if (!m_file.is_open())
        return false;

    uint32_t input;
    m_file >> input; // skip the first line pffset
    auto h_pos_write = m_file.tellg();
    std::string line;
    getline(m_file, line);               // get header line
    uint32_t h_end_pos = m_file.tellg(); // get header end pos
    std::stringstream ss(line);
    std::vector<int> v;

    while (ss >> input) // put values to the vector, if exist
    {
        v.push_back(input);
    }

    // if no deleted lines are found, insert string to the end
    if (v.empty())
    {
        m_file.seekg(0, std::ios_base::end);
        auto current_pos = m_file.tellp();
        m_file << current_pos << "  " << pos << " " << s << std::endl;
        auto next_pos = m_file.tellp();
        m_file.seekg(current_pos, std::ios_base::beg);
        m_file << next_pos;
        m_file.close();
        return true;
    }

    std::string add_str("  ");
    add_str.append(std::to_string(pos));
    add_str.append(" ");
    add_str.append(s);

    for (auto it = v.begin(); it < v.end(); ++it)
    {
        // check the available space
        m_file.seekg(*it, std::ios_base::beg);
        uint32_t line_offset;
        m_file >> line_offset;
        auto write_pos = m_file.tellg();
        getline(m_file, line);

        // if space is enough, write down the string
        if (add_str.size() <= line.size())
        {
            m_file.seekp(write_pos, std::ios_base::beg);
            m_file << add_str;
            v.erase(it);
            // put values in the header
            m_file.seekp(h_pos_write, std::ios_base::beg);

            for (auto value : v)
                m_file << ' ' << value;

            while (m_file.tellp() < (h_end_pos - 1))
                m_file << ' ';

            m_file.close();
            return true;
        }
    }
    // if not enough space, append
    m_file.seekg(0, std::ios_base::end);
    auto current_pos = m_file.tellp();
    m_file << current_pos << "  " << pos << " " << s << std::endl;

    auto next_pos = m_file.tellp();
    m_file.seekg(current_pos, std::ios_base::beg);
    m_file << next_pos;
    m_file.close();
    return true;
}
bool FileStringList::remove(uint32_t pos)
{
    m_file.open(m_file_name, std::ios::binary | std::ios::out | std::ios::in);

    if (!m_file.is_open())
        return false;

    // skip the header
    std::string received;
    getline(m_file, received);

    uint32_t offset;
    uint32_t position;
    auto current_line_offset = m_file.tellg();
    while (m_file >> offset)
    {
        // read the line and check if it's not blank
        auto current_pos = m_file.tellp();
        getline(m_file, received);
        // if blank, go the the next line
        if (std::all_of(received.begin(), received.end(), [](char c) { return std::isspace(c); }))
            continue;

        // if not blank, check the pos matching
        m_file.seekg(current_pos, std::ios_base::beg);
        m_file >> position;
        getline(m_file, received);

        // if pos is found, delete the line
        if (position == pos)
        {
            m_file.seekg(current_pos, std::ios_base::beg);
            getline(m_file, received);
            received.assign(received.size(), ' ');

            m_file.seekg(current_pos, std::ios_base::beg);
            m_file << received;
            m_file.close();

            // put the offset to the header
            deleted_pos(current_line_offset);
            return true;
        }
    contin:;
        current_line_offset = m_file.tellg();
    }

    m_file.close();
    return false;
}
std::string &FileStringList::string(uint32_t pos)
{
    m_file.open(m_file_name, std::ios::binary | std::ios::in);
    std::string *received = new std::string;

    if (!m_file.is_open())
        return *received;

    // skip the header
    std::string line;
    getline(m_file, line);
    uint32_t offset;
    uint32_t position;

    while (m_file >> offset)
    {
        // read the line and check if it's not blank
        auto current_pos = m_file.tellp();
        getline(m_file, line);
        // if blank, go the the next line
        if (std::all_of(line.begin(), line.end(), [](char c) { return std::isspace(c); }))
            continue;

        // if not blank, check the pos matching
        m_file.seekg(current_pos, std::ios_base::beg);
        m_file >> position;
        m_file.seekp(1, std::ios_base::cur); // need to skip the ' '
        getline(m_file, *received);

        if (position == pos)
        {
            m_file.close();
            return *received;
        }
    contin:;
    }

    m_file.close();
    std::string *empty = new std::string();
    return *empty;
}

bool FileStringList::is_uniq(uint32_t pos)
{
    m_file.open(m_file_name, std::ios::binary | std::ios::in);

    if (!m_file.is_open())
        return false;

    // skip the header
    std::string line;
    getline(m_file, line);
    uint32_t offset;
    uint32_t position;

    while (m_file >> offset)
    {
        // read the line and check if it's not blank
        auto current_pos = m_file.tellp();
        getline(m_file, line);
        // if blank, go the the next line
        if (std::all_of(line.begin(), line.end(), [](char c) { return std::isspace(c); }))
            continue;
        // check if pos already exist
        m_file.seekg(current_pos, std::ios_base::beg);
        m_file >> position;

        if (position == pos)
        {
            m_file.close();
            return false;
        }
        getline(m_file, line);
    contin:;
    }

    m_file.close();
    return true;
}

void FileStringList::deleted_pos(uint32_t offset)
{
    m_file.open(m_file_name, std::ios::binary | std::ios::out | std::ios::in);
    // get end pos of the header
    std::string header;
    getline(m_file, header);
    auto header_end_pos = m_file.tellg();

    // skip the first line offset
    m_file.seekg(0, std::ios_base::beg);
    uint32_t input;
    m_file >> input;
    auto write_pos = m_file.tellg();

    // get and sort all pos of deleted lines
    std::vector<uint32_t> v(0);
    v.push_back(offset);
    m_file >> input;

    while (m_file.tellg() < header_end_pos)
    {
        v.push_back(input);
        m_file >> input;
    }
    std::sort(v.begin(), v.end());

    // put values in the header
    m_file.seekg(write_pos, std::ios_base::beg);

    for (auto value : v)
        m_file << ' ' << value;

    m_file.close();
}
