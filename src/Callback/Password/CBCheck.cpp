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
#include <unistd.h>

// External
#include <libmrhpsb/MRH_PSBLogger.h>

// Project
#include "./CBCheck.h"
#include "../../Password/PasswordFile.h"
#include "../../Password/Encryption.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

CBCheck::CBCheck() noexcept
{}

CBCheck::~CBCheck() noexcept
{}

//*************************************************************************************
// Callback
//*************************************************************************************

void CBCheck::Callback(const MRH_Event* p_Event, MRH_Uint32 u32_GroupID) noexcept
{
    // Compare password
    MRH_EvD_P_Check_U c_RequestData;
    MRH_EvD_P_Check_S c_ResultData;
    c_ResultData.u8_Result = MRH_EVD_BASE_RESULT_FAILED;
    
    if (MRH_EVD_ReadEvent(&c_RequestData, p_Event->u32_Type, p_Event) < 0)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::INFO, "Failed to read request event!",
                                       "CBCheck.cpp", __LINE__);
    }
    else
    {
        if (CanAccess() == true)
        {
            try
            {
                std::string s_Hash(PasswordFile::Singleton().Read());
                std::string s_String(c_RequestData.p_String);
                
                if (Encryption::Compare(s_Hash, s_String))
                {
                    MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::INFO, "Password check failed!",
                                                   "CBCheck.cpp", __LINE__);
                }
                else
                {
                    c_ResultData.u8_Result = MRH_EVD_BASE_RESULT_SUCCESS;
                }
                
                Encryption::Clear(s_String);
            }
            catch (Exception& e)
            {
                MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::INFO, e.what(),
                                               "CBCheck.cpp", __LINE__);
            }
        }
        
        AccessResult((c_ResultData.u8_Result == MRH_EVD_BASE_RESULT_SUCCESS ? true : false));
    }
    
    MRH_Event* p_Result = MRH_EVD_CreateSetEvent(MRH_EVENT_PASSWORD_CHECK_S, &c_ResultData);
    
    if (p_Result == NULL)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, "Failed to create response event!",
                                       "CBCheck.cpp", __LINE__);
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
                                       "CBCheck.cpp", __LINE__);
    }
}
