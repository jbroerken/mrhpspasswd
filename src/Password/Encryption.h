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
