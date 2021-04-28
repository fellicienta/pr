#include "FileStringList.h"

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

FileStringList::FileStringList(std::string m_file_name)
    : m_file_name(m_file_name)
    , m_file(m_file_name, std::ios::binary | std::ios::in | std::ios::out)
{
    if (!std::filesystem::exists(m_file_name))
    {
        m_file.open(m_file_name, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
        Header h;
        m_file.write(reinterpret_cast<char *>(&h), sizeof(h));
    }
    m_file.close();
}

bool FileStringList::insert(const std::string &s, uint32_t pos)
{
    m_file.open(m_file_name, std::ios::binary | std::ios::in | std::ios::out);

    if (!m_file.is_open())
        return false;

    // put string to the struct
    List w; // for writing
    List r; // for reading
    strcpy(w.str, s.c_str());

    long previous = m_file.tellg();
    // read the header
    Header h;
    m_file.read((char *)&h, sizeof(h));

    // is the list empty ?
    if (h.first_line == INVALID)
    {
        h.first_line = m_file.tellg();       // take the pos of the first line
        m_file.write((char *)&w, sizeof(w)); // add the string
        m_file.seekp(0, std::ios_base::beg); // rewrite the offset
        m_file.write((char *)&h.first_line, sizeof(h.first_line));
        m_file.close();
        return true;
    }

    long new_line;
    if (h.removed_line != INVALID) // if removed line exists
    {
        m_file.seekp(h.removed_line, std::ios_base::beg); // go to removed line
        new_line = m_file.tellp();
        m_file.write((char *)&w, sizeof(w)); // write the data
        // reset header
        h.removed_line = INVALID;
        m_file.seekp(sizeof(h.first_line), std::ios_base::beg);
        m_file.write((char *)&h.removed_line, sizeof(h.removed_line));
    }
    else
    {
        m_file.seekp(0, std::ios_base::end); // go to eof
        new_line = m_file.tellp();
        m_file.write((char *)&w, sizeof(w)); // write the data
    }

    // ** insert to the pos **
    // if the list is not empty, go to the first line
    long current = h.first_line;
    m_file.seekg(h.first_line, std::ios_base::beg);
    // read the first line
    uint32_t counter = 0;
    r.offset = h.first_line;
    // read lines till the end of the list
    while (r.offset != INVALID)
    {
        ++counter;
        if (pos == counter)
        {
            m_file.seekp(new_line, std::ios_base::beg); // new --> current
            m_file.write((char *)&r.offset, sizeof(r.offset));
            m_file.seekp(previous, std::ios_base::beg); // previous --> new
            m_file.write((char *)&new_line, sizeof(r.offset));
            m_file.close();
            return true;
        }
        previous = current;
        m_file.seekg(r.offset, std::ios_base::beg);
        current = m_file.tellg();
        m_file.read((char *)&r, sizeof(r));
    }
    m_file.seekg(current, std::ios_base::beg);
    m_file.write((char *)&new_line, sizeof(r.offset));

    m_file.close();
    return true;
}

bool FileStringList::remove(uint32_t pos)
{
    m_file.open(m_file_name, std::ios::binary | std::ios::out | std::ios::in);

    if (!m_file.is_open())
        return false;

    auto previous = m_file.tellg();
    // read the header
    Header h;
    m_file.read((char *)&h, sizeof(h));
    // check if list is empty
    if (h.first_line == INVALID)
    {
        m_file.close();
        return false;
    }

    List w; // for writing
    List r; // for reading

    // if the list is not empty, go to the first line
    long current = h.first_line;
    m_file.seekg(current, std::ios_base::beg);
    uint32_t counter = 0;
    // r.offset = h.first_line;
    // read lines till the end of the list
    while (current != INVALID)
    {
        ++counter;
        m_file.read((char *)&r, sizeof(r));
        // long next = r.offset;

        if (pos == counter)
        {
            m_file.seekp(current, std::ios_base::beg);  // previous --> next
            m_file.write((char *)&w, sizeof(w));        // clear the line
            m_file.seekp(previous, std::ios_base::beg); // previous --> next
            m_file.write((char *)&r.offset, sizeof(r.offset));
            // reset header
            h.removed_line = current;
            m_file.seekp(sizeof(h.first_line), std::ios_base::beg);
            m_file.write((char *)&h.removed_line, sizeof(h.removed_line));
            m_file.close();
            return true;
        }
        previous = current; // go to next element
        current = r.offset;
        m_file.seekg(current, std::ios_base::beg);
    }

    m_file.close();
    return false;
}

std::string &FileStringList::string(uint32_t pos)
{
    std::string *s = new std::string();
    m_file.open(m_file_name, std::ios::binary | std::ios::in);

    if (!m_file.is_open())
        return *s;

    // read the header
    Header h;
    m_file.read((char *)&h, sizeof(h));
    // check if the list is empty
    if (h.first_line == INVALID)
    {
        m_file.close();
        return *s;
    }
    List r;

    // if the file is not empty, go to the first line
    m_file.seekg(h.first_line, std::ios_base::beg);
    // read the first line
    m_file.read((char *)&r, sizeof(r));
    uint32_t counter = 1;

    // read lines till the end of the list
    while (r.offset != INVALID)
    {
        m_file.seekg(r.offset, std::ios_base::beg);
        m_file.read((char *)&r, sizeof(r));
        ++counter;
        if (pos == counter)
        {
            *s = r.str;
            m_file.close();
            return *s;
        }
    }

    m_file.close();
    return *s;
}
