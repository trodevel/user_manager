/*

String Helper. Provides to_string() function.

Copyright (C) 2017 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 12061 $ $Date:: 2019-09-27 #$ $Author: serge $

#ifndef USER_MANAGER_STR_HELPER_H
#define USER_MANAGER_STR_HELPER_H

#include <string>
#include <sstream>              // std::ostringstream

#include "user.h"

namespace user_manager
{

class StrHelper
{
public:
    static const std::string & to_string( status_e l );
    static const std::string & to_string( gender_e l );
    static std::string to_string( User::field_e l );

    static std::ostream & write( std::ostream & os, const User & l );

    template<class T>
    static std::string to_string( const T & l )
    {
        std::ostringstream os;

        write( os, l );

        return os.str();
    }

};

} // namespace user_manager

#endif // USER_MANAGER_STR_HELPER_H
