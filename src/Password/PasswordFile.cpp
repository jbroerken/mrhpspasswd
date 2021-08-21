/**
 *  PasswordFile.cpp
 *
 *  This file is part of the MRH project.
 *  See the AUTHORS file for Copyright information.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// C / C++
#include <unistd.h>
#include <cstdio>

// External

// Project
#include "./PasswordFile.h"
#include "./Encryption.h"

// Pre-defined
#ifndef MRH_PASSWORD_FILE_PATH
    #define MRH_PASSWORD_FILE_PATH "/etc/mrhpservice/Password.conf"
#endif


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

PasswordFile::PasswordFile() noexcept
{}

PasswordFile::~PasswordFile() noexcept
{}

//*************************************************************************************
// Singleton
//*************************************************************************************

PasswordFile& PasswordFile::Singleton() noexcept
{
    static PasswordFile s_PasswordFile;
    return s_PasswordFile;
}

//*************************************************************************************
// Read
//*************************************************************************************

std::string PasswordFile::Read()
{
    // Define
    std::FILE* p_File;
    size_t us_Filesize;
    std::string s_Hash;
    
    // Open file
    std::lock_guard<std::mutex> s_Guard(s_Mutex);
    
    if ((p_File = fopen(MRH_PASSWORD_FILE_PATH, "rb")) == NULL)
    {
        throw Exception("Failed to open password file!");
    }
    
    // Get file size
    fseek(p_File, 0, SEEK_END);
    
    if ((us_Filesize = ftell(p_File)) == 0 || us_Filesize > Encryption::GetStringBytes())
    {
        fclose(p_File);
        throw Exception("Invalid password file size!");
    }
    
    fseek(p_File, 0, SEEK_SET);
    
    // Read password
    s_Hash.reserve(us_Filesize);
    
    if (s_Hash.size() != us_Filesize || fread(&(s_Hash[0]), sizeof(char), us_Filesize, p_File) != us_Filesize)
    {
        fclose(p_File);
        throw Exception("Could not read password hash!");
    }
    
    fclose(p_File);
    return s_Hash;
}

//*************************************************************************************
// Write
//*************************************************************************************

void PasswordFile::Write(std::string const& s_Hash)
{
    // Write file
    std::lock_guard<std::mutex> s_Guard(s_Mutex);
    
    FILE* p_File = fopen(MRH_PASSWORD_FILE_PATH, "wb");
    
    if (p_File == NULL)
    {
        throw Exception("Could not open password file!");
    }
    else if (fwrite(&(s_Hash[0]), sizeof(char), s_Hash.size(), p_File) != s_Hash.size())
    {
        fclose(p_File);
        throw Exception("Failed to write hashed password!");
    }
    
    fclose(p_File);
}

//*************************************************************************************
// Getters
//*************************************************************************************

bool PasswordFile::GetExists() noexcept
{
    return access(MRH_PASSWORD_FILE_PATH, F_OK) == 0 ? true : false;
}
