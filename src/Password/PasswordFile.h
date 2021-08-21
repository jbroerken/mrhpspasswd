/**
 *  PasswordFile.h
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

#ifndef PasswordFile_h
#define PasswordFile_h

// C / C++
#include <ctime>
#include <mutex>
#include <string>

// External

// Project
#include "../Exception.h"


class PasswordFile
{
public:

    //*************************************************************************************
    // Singleton
    //*************************************************************************************

    /**
     *  Get the class instance.
     *
     *  \return The class instance.
     */

    static PasswordFile& Singleton() noexcept;
    
    //*************************************************************************************
    // Read
    //*************************************************************************************
    
    /**
     *  Read the encrypted password string from file. This function is thread safe.
     *
     *  \return The read password string.
     */
    
    std::string Read();
    
    //*************************************************************************************
    // Write
    //*************************************************************************************
    
    /**
     *  Write the encrypted password string to file. This function is thread safe.
     *
     *  \param s_Hash The password string to write.
     */
    
    void Write(std::string const& s_Hash);
    
    //*************************************************************************************
    // Getters
    //*************************************************************************************

    /**
     *  Check if the password file exists. This function is thread safe.
     *
     *  \return true if the file exists, false if not.
     */
    
    bool GetExists() noexcept;
    
private:

    //*************************************************************************************
    // Constructor / Destructor
    //*************************************************************************************

    /**
     *  Default constructor.
     */

    PasswordFile() noexcept;

    /**
     *  Default destructor.
     */

    ~PasswordFile() noexcept;
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    std::mutex s_Mutex;
    
protected:
};

#endif /* Password_h */
