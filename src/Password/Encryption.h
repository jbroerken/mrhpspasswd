/**
 *  Encryption.h
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

#ifndef Encryption_h
#define Encryption_h

// C / C++
#include <string>

// External

// Project
#include "../Exception.h"


namespace Encryption
{
    //*************************************************************************************
    // Clear
    //*************************************************************************************
    
    /**
     *  Clear a string. This function is thread safe.
     */
    
    void Clear(std::string& s_String) noexcept;

    //*************************************************************************************
    // Compare
    //*************************************************************************************
    
    /**
     *  Compare a password hash with a given string. This function is thread safe.
     *
     *  \param s_Hash The password hash. The hash will be cleared.
     *  \param s_String The string to compare with.
     */
    
    bool Compare(std::string& s_Hash, std::string const& s_String) noexcept;

    //*************************************************************************************
    // Compare
    //*************************************************************************************

    /**
     *  Encrypt a given string. This function is thread safe.
     *
     *  \param s_String The string to encrypt.
     *
     *  \return The encrypted string.
     */

    std::string Encrypt(std::string const& s_String);
    
    /**
     *  Encrypt a given string and clear the string source. This function is thread safe.
     *
     *  \param s_String The string to encrypt. The string will be cleared.
     *
     *  \return The encrypted string.
     */
    
    std::string Encrypt(std::string& s_String);
    
    //*************************************************************************************
    // Getters
    //*************************************************************************************
    
    /**
     *  Get the amount of bytes for a encrpytion string. This function is thread safe.
     *
     *  \return The string byte amount.
     */
    
    size_t GetStringBytes() noexcept;
};

#endif /* Encryption_h */
