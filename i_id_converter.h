/*

User manager - ID converter.

Copyright (C) 2019 Sergey Kolevatov

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

// $Revision: 12004 $ $Date:: 2019-09-16 #$ $Author: serge $

#ifndef LIB_USER_MANAGER__ID_CONVERTER_H
#define LIB_USER_MANAGER__ID_CONVERTER_H

#include "types.h"      // user_id_t

#include <string>

namespace user_manager
{

class IIdConverter
{
public:

    virtual ~IIdConverter() {}

    virtual user_id_t convert_login_to_user_id( const std::string & login, bool is_case_sensitive = true ) const = 0;
};

} // namespace user_manager

#endif // LIB_USER_MANAGER__ID_CONVERTER_H
