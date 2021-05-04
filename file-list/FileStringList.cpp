#include "FileStringList.h"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>

FileStringList::FileStringList(std::string m_file_name)
    : m_file_name(m_file_name)
{
    if (!std::filesystem::exists(m_file_name))
    {
        m_file.open(m_file_name, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
        Header h;
        m_file.write(reinterpret_cast<char *>(&h), sizeof(h));
    }
    else
        m_file.open(m_file_name, std::ios::binary | std::ios::in | std::ios::out);
}

bool FileStringList::insert(const std::string &s, uint32_t pos)
{
    m_file.seekp(0, std::ios_base::beg);

    uint32_t w_offset = INVALID_OFFSET; // for writing
    uint32_t previous = m_file.tellg();
    // read the header
    Header h;
    m_file.read(reinterpret_cast<char *>(&h), sizeof(h));

    // is the list empty ?
    if (h.first_record == INVALID_OFFSET)
    {
        h.first_record = m_file.tellg(); // take the pos of the first line
        m_file.write(reinterpret_cast<char *>(&w_offset),
                     sizeof(w_offset)); // add the string
        m_file.write(s.c_str(), s.size() + 1);
        m_file.seekp(0, std::ios_base::beg); // rewrite the offset
        m_file.write(reinterpret_cast<char *>(&h.first_record), sizeof(h.first_record));
        return true;
    }

    uint32_t new_record = allocate_memory(h.removed_record, s.size());
    current_string = s;
    // if space is bigger, than the string size, append addition
    if (space_size > s.size())
        current_string.append(space_size - s.size(), SYMBOL);

    // ** insert to the pos **
    // go to the first line
    m_file.seekg(h.first_record, std::ios_base::beg);
    uint32_t counter = 0;
    uint32_t current_pos = h.first_record;
    // look for pos in the list
    while (current_pos != INVALID_OFFSET)
    {
        ++counter;
        if (pos == counter)
        {
            m_file.seekp(new_record, std::ios_base::beg); // new --> current
            m_file.write(reinterpret_cast<char *>(&current_pos), sizeof(current_pos));
            m_file.write(current_string.c_str(), current_string.size() + 1); // write the data
            m_file.seekp(previous, std::ios_base::beg);                      // previous --> new
            m_file.write(reinterpret_cast<char *>(&new_record), sizeof(new_record));
            return true;
        }
        previous = current_pos;
        m_file.read(reinterpret_cast<char *>(&current_pos), sizeof(current_pos));
        m_file.seekg(current_pos, std::ios_base::beg);
    }

    // if pos is bigger, than the list size, append to the end
    m_file.seekg(previous, std::ios_base::beg);
    m_file.write(reinterpret_cast<char *>(&new_record), sizeof(new_record));
    m_file.seekp(new_record, std::ios_base::beg); // write the data
    m_file.write(reinterpret_cast<char *>(&w_offset), sizeof(w_offset));
    m_file.write(current_string.c_str(), s.size() + 1);

    return true;
}

uint32_t FileStringList::allocate_memory(uint32_t removed_record, uint32_t str_size)
{
    uint32_t new_record = removed_record;
    bool replace_record = false;
    uint32_t r_offset; // for reading

    // check for removed lines
    while (new_record != INVALID_OFFSET)
    {
        m_file.seekp(new_record, std::ios_base::beg); // go to removed line
        m_file.read(reinterpret_cast<char *>(&r_offset), sizeof(r_offset));
        getline(m_file, current_string, '\0');
        // check if the string fits
        space_size = current_string.size();

        if (str_size <= space_size)
        {
            // reset header
            removed_record = r_offset;
            m_file.seekp(sizeof(uint32_t), std::ios_base::beg);
            m_file.write(reinterpret_cast<char *>(&removed_record), sizeof(removed_record));
            replace_record = true;
            break;
        }
        new_record = r_offset;
    }
    // if there are no removed lines, allocate memory in the eof
    if (!replace_record)
    {
        m_file.seekp(0, std::ios_base::end); // go to eof
        new_record = m_file.tellp();
        space_size = 0;
    }
    return new_record;
}

bool FileStringList::remove(uint32_t pos)
{
    m_file.seekp(0, std::ios_base::beg);

    auto previous = m_file.tellg();
    // read the header
    Header h;
    m_file.read(reinterpret_cast<char *>(&h), sizeof(h));
    // check if list is empty
    if (h.first_record == INVALID_OFFSET)
        return false;

    uint32_t w_offset = INVALID_OFFSET; // for writing
    uint32_t r_offset;                  // for reading

    // if the list is not empty, go to the first line
    uint32_t current_pos = h.first_record;
    m_file.seekg(current_pos, std::ios_base::beg);
    uint32_t counter = 0;
    // look for pos in the list
    while (current_pos != INVALID_OFFSET)
    {
        ++counter;
        m_file.read(reinterpret_cast<char *>(&r_offset), sizeof(r_offset));

        if (pos == counter)
        {
            getline(m_file, current_string, '\0');
            m_file.seekp(current_pos, std::ios_base::beg);
            m_file.write(reinterpret_cast<char *>(&w_offset),
                         sizeof(w_offset)); // reset offset to invalid

            m_file.seekp(previous, std::ios_base::beg); // previous --> next
            m_file.write(reinterpret_cast<char *>(&r_offset), sizeof(r_offset));
            // reset header
            r_offset = h.removed_record;
            h.removed_record = sizeof(h.first_record);

            while (r_offset != INVALID_OFFSET)
            {
                m_file.seekg(r_offset, std::ios_base::beg);
                h.removed_record = r_offset;
                m_file.read(reinterpret_cast<char *>(&r_offset), sizeof(r_offset));
            }

            m_file.seekp(h.removed_record, std::ios_base::beg);
            m_file.write(reinterpret_cast<char *>(&current_pos), sizeof(current_pos));
            return true;
        }
        previous = current_pos; // go to the next element
        current_pos = r_offset;
        m_file.seekg(current_pos, std::ios_base::beg);
    }
    // if pos is not found, return false
    return false;
}

std::string &FileStringList::string(uint32_t pos)
{
    m_file.seekp(0, std::ios_base::beg);
    // read the header
    Header h;
    m_file.read(reinterpret_cast<char *>(&h), sizeof(h));
    // check if the list is empty
    if (h.first_record == INVALID_OFFSET)
        return current_string;

    // if the file is not empty, go to the first line
    uint32_t counter = 0;
    uint32_t current_pos = h.first_record;
    // look for pos in the list
    while (current_pos != INVALID_OFFSET)
    {
        m_file.seekg(current_pos, std::ios_base::beg);
        m_file.read(reinterpret_cast<char *>(&current_pos), sizeof(current_pos));
        getline(m_file, current_string, '\0');
        ++counter;
        if (pos == counter)
        { // discard addition, if exists
            current_string.resize(current_string.find_last_not_of(SYMBOL, std::string::npos) + 1);
            return current_string;
        }
    }
    // if pos is not found, return an empty string
    return current_string;
}
