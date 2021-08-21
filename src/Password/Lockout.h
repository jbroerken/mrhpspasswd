/**
 *  Lockout.h
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
