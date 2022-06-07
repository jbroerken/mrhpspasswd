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
