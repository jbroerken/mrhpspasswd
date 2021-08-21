/**
 *  Encryption.cpp
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

// External
#include <sodium.h>

// Project
#include "./Encryption.h"


//*************************************************************************************
// Clear
//*************************************************************************************

void Encryption::Clear(std::string& s_String) noexcept
{
    sodium_memzero(&(s_String[0]), s_String.size());
}

//*************************************************************************************
// Compare
//*************************************************************************************

bool Encryption::Compare(std::string& s_Hash, std::string const& s_String) noexcept
{
    bool b_Result = true;
    
    if (crypto_pwhash_str_verify(s_Hash.c_str(), s_String.c_str(), s_String.size()) < 0)
    {
        b_Result = false;
    }
    
    sodium_memzero(&(s_Hash[0]), s_Hash.size());
    
    return b_Result;
}

//*************************************************************************************
// Encrypt
//*************************************************************************************

std::string Encryption::Encrypt(std::string const& s_String)
{
    std::string s_Hash(crypto_pwhash_STRBYTES, '\0');
    
    if (crypto_pwhash_str(&(s_Hash[0]), s_String.c_str(), s_String.size(), crypto_pwhash_OPSLIMIT_MIN, crypto_pwhash_MEMLIMIT_MIN) < 0)
    {
        throw Exception("Failed to encrypt string!");
    }
    
    return s_Hash;
}

std::string Encryption::Encrypt(std::string& s_String)
{
    std::string s_Hash(crypto_pwhash_STRBYTES, '\0');
    
    if (crypto_pwhash_str(&(s_Hash[0]), s_String.c_str(), s_String.size(), crypto_pwhash_OPSLIMIT_MIN, crypto_pwhash_MEMLIMIT_MIN) < 0)
    {
        sodium_memzero(&(s_String[0]), s_String.size());
        throw Exception("Failed to encrypt string!");
    }
    
    sodium_memzero(&(s_String[0]), s_String.size());
    return s_Hash;
}

//*************************************************************************************
// Getters
//*************************************************************************************

size_t Encryption::GetStringBytes() noexcept
{
    return crypto_pwhash_STRBYTES;
}
