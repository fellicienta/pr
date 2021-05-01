#include "FileStringList.h"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>

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
    uint32_t w_offset = INVALID_OFFSET; // for writing
    Read r;                             // for reading
    char c[s.size() + 1];
    strcpy(c, s.c_str());

    uint32_t previous = m_file.tellg();
    // read the header
    Header h;
    m_file.read(reinterpret_cast<char *>(&h), sizeof(h));

    // is the list empty ?
    if (h.first_line == INVALID_OFFSET)
    {
        h.first_line = m_file.tellg(); // take the pos of the first line
        m_file.write(reinterpret_cast<char *>(&w_offset), sizeof(w_offset)); // add the string
        m_file.write(reinterpret_cast<char *>(&c), sizeof(c));

        m_file.seekp(0, std::ios_base::beg); // rewrite the offset
        m_file.write(reinterpret_cast<char *>(&h.first_line), sizeof(h.first_line));
        m_file.close();
        return true;
    }

    uint32_t new_line = h.removed_line;
    // check for removed lines
    bool flag = false;
    while (new_line != INVALID_OFFSET)
    {
        m_file.seekp(new_line, std::ios_base::beg); // go to removed line
        m_file.read(reinterpret_cast<char *>(&r.offset), sizeof(r.offset));
        getline(m_file, r.str, '\0');
        // check if the string fits
        uint32_t size = strlen(r.str.c_str()) - 1;

        if (strlen(c) < size)
        {
            char empty[size];
            memset(empty, '\0', size);

            m_file.seekp(new_line, std::ios_base::beg); // go to removed line
            m_file.write(reinterpret_cast<char *>(&w_offset),
                         sizeof(w_offset)); // write the data
            auto current = m_file.tellp();
            m_file.write(reinterpret_cast<char *>(&empty), sizeof(empty));
            m_file.seekp(current, std::ios_base::beg);
            m_file.write(reinterpret_cast<char *>(&c), sizeof(c));
            // reset header
            h.removed_line = r.offset;
            m_file.seekp(sizeof(h.first_line), std::ios_base::beg);
            m_file.write(reinterpret_cast<char *>(&h.removed_line), sizeof(h.removed_line));
            flag = true;
            break;
        }
        new_line = r.offset;
    }
    // if there are no removed lines, write data to the new space
    if (!flag)
    {
        m_file.seekp(0, std::ios_base::end); // go to eof
        new_line = m_file.tellp();
        m_file.write(reinterpret_cast<char *>(&w_offset), sizeof(w_offset)); // write the data
        m_file.write(reinterpret_cast<char *>(&c), sizeof(c));
    }

    // ** insert to the pos **
    // go to the first line
    m_file.seekg(h.first_line, std::ios_base::beg);
    uint32_t counter = 0;
    r.offset = h.first_line;
    // look for pos in the list
    while (r.offset != INVALID_OFFSET)
    {
        ++counter;
        if (pos == counter)
        {
            m_file.seekp(new_line, std::ios_base::beg); // new --> current
            m_file.write(reinterpret_cast<char *>(&r.offset), sizeof(r.offset));
            m_file.seekp(previous, std::ios_base::beg); // previous --> new
            m_file.write(reinterpret_cast<char *>(&new_line), sizeof(new_line));
            m_file.close();
            return true;
        }
        previous = r.offset;
        m_file.read(reinterpret_cast<char *>(&r.offset), sizeof(r.offset));
        m_file.seekg(r.offset, std::ios_base::beg);
    }
    // if pos is bigger than the list size, append to the end
    m_file.seekg(previous, std::ios_base::beg);
    m_file.write(reinterpret_cast<char *>(&new_line), sizeof(new_line));

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
    m_file.read(reinterpret_cast<char *>(&h), sizeof(h));
    // check if list is empty
    if (h.first_line == INVALID_OFFSET)
    {
        m_file.close();
        return false;
    }

    uint32_t w_offset = INVALID_OFFSET; // for writing
    Read r;                             // for reading

    // if the list is not empty, go to the first line
    uint32_t current = h.first_line;
    m_file.seekg(current, std::ios_base::beg);
    uint32_t counter = 0;
    // look for pos in the list
    while (current != INVALID_OFFSET)
    {
        ++counter;
        m_file.read(reinterpret_cast<char *>(&r.offset), sizeof(r.offset));
        getline(m_file, r.str, '\0');

        if (pos == counter)
        {
            uint32_t size = r.str.size() + 1;
            char c[size];
            memset(c, 0xFF, size);
            c[size] = '\0';
            m_file.seekp(current, std::ios_base::beg); // previous --> next
            m_file.write(reinterpret_cast<char *>(&w_offset), sizeof(w_offset)); // clear the line
            m_file.write(reinterpret_cast<char *>(&c), sizeof(c));
            m_file.seekp(previous, std::ios_base::beg); // previous --> next
            m_file.write(reinterpret_cast<char *>(&r.offset), sizeof(r.offset));
            // reset header
            uint32_t write_pos = sizeof(h.first_line);
            r.offset = h.removed_line;

            while (r.offset != INVALID_OFFSET)
            {
                m_file.seekg(r.offset, std::ios_base::beg);
                write_pos = r.offset;
                m_file.read(reinterpret_cast<char *>(&r.offset), sizeof(r.offset));
            }

            m_file.seekp(write_pos, std::ios_base::beg);
            m_file.write(reinterpret_cast<char *>(&current), sizeof(current));
            m_file.close();
            return true;
        }
        previous = current; // go to next element
        current = r.offset;
        m_file.seekg(current, std::ios_base::beg);
    }
    // if pos is not found, return false
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
    m_file.read(reinterpret_cast<char *>(&h), sizeof(h));
    // check if the list is empty
    if (h.first_line == INVALID_OFFSET)
    {
        m_file.close();
        return *s;
    }
    Read r;
    // if the file is not empty, go to the first line
    uint32_t counter = 0;
    r.offset = h.first_line;
    // look for pos in the list
    while (r.offset != INVALID_OFFSET)
    {
        m_file.seekg(r.offset, std::ios_base::beg);
        m_file.read(reinterpret_cast<char *>(&r.offset), sizeof(r.offset));
        getline(m_file, r.str, '\0');
        ++counter;
        if (pos == counter)
        {
            *s = r.str;
            m_file.close();
            return *s;
        }
    }
    // if pos is not found, return an empty string
    m_file.close();
    return *s;
}
