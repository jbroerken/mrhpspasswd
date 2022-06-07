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

#ifndef Lockout_h
#define Lockout_h

// C / C++
#include <ctime>
#include <mutex>

// External

// Project


class Lockout
{
public:
    
    //*************************************************************************************
    // Destructor
    //*************************************************************************************
    
    /**
     *  Default destructor.
     */
    
    ~Lockout() noexcept;

private:
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    // Compare limit
    static std::mutex c_Mutex;
    static time_t us_LastAccessS;
    static int i_FailedCount;
    
protected:
    
    //*************************************************************************************
    // Constructor / Destructor
    //*************************************************************************************
    
    /**
     *  Default constructor.
     */
    
    Lockout() noexcept;
    
    //*************************************************************************************
    // Access
    //*************************************************************************************
    
    /**
     *  Check if the password can be accessed.
     *
     *  \return true if allowed, false if not.
     */
    
    bool CanAccess() noexcept;
    
    /**
     *  Update access with the access result.
     *
     *  \param b_Result The access result.
     */
    
    void AccessResult(bool b_Result) noexcept;
};

#endif /* Lockout_h */
