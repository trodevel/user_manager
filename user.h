/*

User.

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

// $Revision: 11596 $ $Date:: 2019-05-24 #$ $Author: serge $

#ifndef USER_MANAGER_USER_H
#define USER_MANAGER_USER_H

#include <map>              // std::map
#include "types.h"          // user_id_t
#include "value.h"          // Value

namespace user_manager
{

enum class status_e
{
    INACTIVE    = 0,
    ACTIVE      = 1,
    DELETED     = 2,
};

enum class gender_e
{
    UNDEF       = 0,
    MALE        = 1,
    FEMALE      = 2,
};

struct User
{
    friend class StrHelper;

    enum field_e
    {
        UNDEF   = 0,
        GENDER,
        TITLE,
        FIRST_NAME,
        LAST_NAME,
        COMPANY_NAME,
        EMAIL,
        PHONE,
        TIMEZONE,
        ZIP,
        COUNTRY,
        CITY,
        STREET,
        HOUSE_NUMBER,
        EAL,
        USER_DEFINED_FIELD_ID_BASE  = 1000,
    };

    typedef std::map<field_e,Value> MapIdToValue;

    user_id_t   user_id;
    group_id_t  group_id;
    status_e    status;
    std::string login;
    std::string password_hash;

    bool has_field( const field_e field_id ) const;
    bool get_field( const field_e field_id, Value * res ) const;
    bool add_field( const field_e field_id, const Value & value );
    bool delete_field( const field_e field_id );

private:

    MapIdToValue map_id_to_value_;
};

} // namespace user_manager


#endif // USER_MANAGER_USER_H
