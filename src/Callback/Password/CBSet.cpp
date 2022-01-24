/**
 *  CBSet.cpp
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

// External
#include <libmrhpsb/MRH_PSBLogger.h>

// Project
#include "./CBSet.h"
#include "../../Password/PasswordFile.h"
#include "../../Password/Encryption.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

CBSet::CBSet() noexcept
{}

CBSet::~CBSet() noexcept
{}

//*************************************************************************************
// Callback
//*************************************************************************************

void CBSet::Callback(const MRH_Event* p_Event, MRH_Uint32 u32_GroupID) noexcept
{
    // Update password
    MRH_EvD_P_Set_U c_RequestData;
    MRH_EvD_P_Set_S c_ResultData;
    c_ResultData.u8_Result = MRH_EVD_BASE_RESULT_FAILED;
    
    if (MRH_EVD_ReadEvent(&c_RequestData, p_Event->u32_Type, p_Event) < 0)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::INFO, "Failed to read request event!",
                                       "CBSet.cpp", __LINE__);
    }
    else if (CanAccess() == true)
    {
        try
        {
            std::string s_Hash = Encryption::Encrypt(c_RequestData.p_String);
            
            PasswordFile::Singleton().Write(s_Hash);
            Encryption::Clear(s_Hash);
            
            c_ResultData.u8_Result = MRH_EVD_BASE_RESULT_SUCCESS;
        }
        catch (Exception& e)
        {
            MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::INFO, e.what(),
                                           "CBSet.cpp", __LINE__);
        }
    }
    
    MRH_Event* p_Result = MRH_EVD_CreateSetEvent(MRH_EVENT_PASSWORD_SET_S, &c_ResultData);
    
    if (p_Result == NULL)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, "Failed to create response event!",
                                       "CBSet.cpp", __LINE__);
        return;
    }
    
    p_Result->u32_GroupID = u32_GroupID;
    
    try
    {
        MRH_EventStorage::Singleton().Add(p_Result);
    }
    catch (MRH_PSBException& e)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, e.what(),
                                       "CBSet.cpp", __LINE__);
    }
}
