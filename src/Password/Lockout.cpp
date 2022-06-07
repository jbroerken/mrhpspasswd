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
#include <libmrhpsb/MRH_PSBLogger.h>

// Project
#include "./Lockout.h"

// Pre-defined
#define PASSWORD_ACCESS_RESET_S 300
#define PASSWORD_ACCESS_LIMIT 10


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

std::mutex Lockout::c_Mutex;
time_t Lockout::us_LastAccessS = 0;
int Lockout::i_FailedCount = 0;

Lockout::Lockout() noexcept
{}

Lockout::~Lockout() noexcept
{}

//*************************************************************************************
// Access
//*************************************************************************************

bool Lockout::CanAccess() noexcept
{
    try
    {
        std::lock_guard<std::mutex> c_Guard(c_Mutex);
        
        // Can access?
        if (i_FailedCount < PASSWORD_ACCESS_LIMIT)
        {
            return true;
        }
        
        // Expired block?
        if (us_LastAccessS + PASSWORD_ACCESS_RESET_S >= time(NULL))
        {
            MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::INFO, "Password lockout reset.",
                                           "Lockout.cpp", __LINE__);
            i_FailedCount = 0;
            return true;
        }
    }
    catch (...)
    {}
    
    return false;
}

void Lockout::AccessResult(bool b_Result) noexcept
{
    try
    {
        std::lock_guard<std::mutex> c_Guard(c_Mutex);
        
        // Success?
        if (b_Result == true)
        {
            i_FailedCount = 0;
            return;
        }
        
        // Start blocking?
        if (i_FailedCount < PASSWORD_ACCESS_LIMIT)
        {
            ++i_FailedCount;
        }
        
        if (i_FailedCount == PASSWORD_ACCESS_LIMIT)
        {
            MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::INFO, "Password check failed to often, lockout.",
                                           "Lockout.cpp", __LINE__);
            us_LastAccessS = time(NULL);
        }
    }
    catch (...)
    {
        // At least attempt
        i_FailedCount = PASSWORD_ACCESS_LIMIT;
        us_LastAccessS = time(NULL);
    }
    
}
