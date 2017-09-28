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
along with this program. If not, see <http://www.gnu->org/licenses/>.

*/

// $Revision: 7939 $ $Date:: 2017-09-28 #$ $Author: serge $

#include "str_helper.h"             // self

#include <sstream>                  // std::ostringstream

namespace user_manager
{

#define TUPLE_VAL_STR(_x_)  _x_,#_x_

const std::string & StrHelper::to_string( status_e l )
{
    typedef std::map< status_e, std::string > Map;
    static Map m =
    {
        { status_e:: TUPLE_VAL_STR( INACTIVE ) },
        { status_e:: TUPLE_VAL_STR( ACTIVE ) },
        { status_e:: TUPLE_VAL_STR( DELETED ) },
    };

    auto it = m.find( l );

    static const std::string undef( "undef" );

    if( it == m.end() )
        return undef;

    return it->second;
}

const std::string & StrHelper::to_string( gender_e l )
{
    typedef std::map< gender_e, std::string > Map;
    static Map m =
    {
        { gender_e:: TUPLE_VAL_STR( UNDEF ) },
        { gender_e:: TUPLE_VAL_STR( MALE ) },
        { gender_e:: TUPLE_VAL_STR( FEMALE ) },
    };

    auto it = m.find( l );

    static const std::string undef( "undef" );

    if( it == m.end() )
        return undef;

    return it->second;
}

std::string StrHelper::to_string( const User * u )
{
    std::ostringstream s;

    s << "user_id " << u->user_id
    << " group_id " << u->group_id
    << " status " << to_string( u->status )
    << " login " << u->login
    << " password_hash " << "..."
    << " gender " << to_string( u->gender )
    << " name " << u->name
    << " first_name " << u->first_name
    << " company_name " << u->company_name
    << " email " << u->email
    << " email_2 " << u->email_2
    << " phone " << u->phone
    << " phone_2 " << u->phone_2
    << " timezone " << u->timezone;

    return s.str();
}

} // namespace user_manager

