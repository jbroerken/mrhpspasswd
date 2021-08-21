/**
 *  Lockout.cpp
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
