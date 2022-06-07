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
#include <cstdlib>

// External
#include <libmrhpsb.h>
#include <sodium.h>

// Project
#include "./Callback/Service/CBAvail.h"
#include "./Callback/Service/CBCustomCommand.h"
#include "./Callback/Password/CBCheck.h"
#include "./Callback/Password/CBSet.h"
#include "./Revision.h"

// Pre-defined
#ifndef MRH_PASSWORD_SERVICE_THREAD_COUNT
    #define MRH_PASSWORD_SERVICE_THREAD_COUNT 1
#endif


//*************************************************************************************
// Exit
//*************************************************************************************

static int Exit(libmrhpsb* p_Context, const char* p_Exception, int i_Result)
{
    if (p_Context != NULL)
    {
        delete p_Context;
    }
    
    if (p_Exception != NULL)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, p_Exception,
                                       "Main.cpp", __LINE__);
    }
    
    return i_Result;
}

//*************************************************************************************
// Main
//*************************************************************************************

int main(int argc, const char* argv[])
{
    // Setup service base
    MRH_PSBLogger& c_Logger = MRH_PSBLogger::Singleton();
    libmrhpsb* p_Context;
    
    try
    {
        p_Context = new libmrhpsb("mrhpspasswd",
                                  argc,
                                  argv,
                                  MRH_PASSWORD_SERVICE_THREAD_COUNT);
    }
    catch (MRH_PSBException& e)
    {
        return Exit(NULL, e.what(), EXIT_FAILURE);
    }
    catch (std::exception& e)
    {
        return Exit(NULL, e.what(), EXIT_FAILURE);
    }
    
    // Setup service specific data
    c_Logger.Log(MRH_PSBLogger::INFO, "Initializing mrhpspasswd (" + std::string(VERSION_NUMBER) + ")...",
                 "Main.cpp", __LINE__);
    
    // NOTE: All sodium functions will be thread safe, see
    //       https://libsodium.gitbook.io/doc/usage
    if (sodium_init() < 0)
    {
        return Exit(p_Context, "Failed to initialize encryption library!", EXIT_FAILURE);
    }
    
    try
    {
        std::shared_ptr<MRH_Callback> p_CBAvail(new CBAvail());
        std::shared_ptr<MRH_Callback> p_CBCustomCommand(new CBCustomCommand());
        std::shared_ptr<MRH_Callback> p_CBCheck(new CBCheck());
        std::shared_ptr<MRH_Callback> p_CBSet(new CBSet());
        
        p_Context->AddCallback(p_CBAvail, MRH_EVENT_PASSWORD_AVAIL_U);
        p_Context->AddCallback(p_CBCustomCommand, MRH_EVENT_PASSWORD_CUSTOM_COMMAND_U);
        p_Context->AddCallback(p_CBCheck, MRH_EVENT_PASSWORD_CHECK_U);
        p_Context->AddCallback(p_CBSet, MRH_EVENT_PASSWORD_SET_U);
    }
    catch (MRH_PSBException& e)
    {
        return Exit(p_Context, e.what(), EXIT_FAILURE);
    }
    catch (std::exception& e)
    {
        return Exit(p_Context, e.what(), EXIT_FAILURE);
    }
    
    c_Logger.Log(MRH_PSBLogger::INFO, "Successfully intialized mrhpspasswd service!",
                 "Main.cpp", __LINE__);
    
    // Update service until termination
    p_Context->Update();
    
    // Exit
    c_Logger.Log(MRH_PSBLogger::INFO, "Terminating service.",
                 "Main.cpp", __LINE__);
    delete p_Context;
    return EXIT_SUCCESS;
}
