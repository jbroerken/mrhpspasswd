/**
 *  Copyright (C) 2021 - 2022 The MRH Project Authors.
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
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
