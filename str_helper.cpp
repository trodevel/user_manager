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

#include "str_helper.h"             // self

#include <sstream>                  // std::ostringstream

#include "anyvalue/str_helper.h"    // anyvalue::StrHelper

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
        { status_e:: TUPLE_VAL_STR( WAITING_REGISTRATION_CONFIRMATION ) },
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

std::string StrHelper::to_string( User::field_e l )
{
    typedef User::field_e   Type;

    typedef std::map< Type, std::string > Map;
    static Map m =
    {
        { Type:: TUPLE_VAL_STR( UNDEF ) },
        { Type:: TUPLE_VAL_STR( USER_ID ) },
        { Type:: TUPLE_VAL_STR( GROUP_ID ) },
        { Type:: TUPLE_VAL_STR( LOGIN ) },
        { Type:: TUPLE_VAL_STR( PASSWORD_HASH ) },
        { Type:: TUPLE_VAL_STR( IS_OPEN ) },
        { Type:: TUPLE_VAL_STR( CREATION_TIME ) },
        { Type:: TUPLE_VAL_STR( MODIFICATION_TIME ) },
        { Type:: TUPLE_VAL_STR( STATUS ) },
        { Type:: TUPLE_VAL_STR( GENDER ) },
        { Type:: TUPLE_VAL_STR( TITLE ) },
        { Type:: TUPLE_VAL_STR( FIRST_NAME ) },
        { Type:: TUPLE_VAL_STR( LAST_NAME ) },
        { Type:: TUPLE_VAL_STR( COMPANY_NAME ) },
        { Type:: TUPLE_VAL_STR( EMAIL ) },
        { Type:: TUPLE_VAL_STR( PHONE ) },
        { Type:: TUPLE_VAL_STR( TIMEZONE ) },
        { Type:: TUPLE_VAL_STR( ZIP ) },
        { Type:: TUPLE_VAL_STR( COUNTRY ) },
        { Type:: TUPLE_VAL_STR( CITY ) },
        { Type:: TUPLE_VAL_STR( STREET ) },
        { Type:: TUPLE_VAL_STR( HOUSE_NUMBER ) },
        { Type:: TUPLE_VAL_STR( EAL ) },
        { Type:: TUPLE_VAL_STR( REGISTRATION_KEY ) },
        { Type:: TUPLE_VAL_STR( REGISTRATION_EXPIRATION ) },
        { Type:: TUPLE_VAL_STR( REGISTRATION_TIME ) },
    };

    auto it = m.find( l );

    if( it == m.end() )
        return "ID_" + std::to_string( l );

    return it->second;
}

std::ostream & StrHelper::write( std::ostream & os, const User & u )
{
    os << "user_id " << u.get_user_id()
    << " group_id " << u.get_group_id()
    << " is_open " << int( u.is_open() )
    << " login " << u.get_login()
    << " password_hash " << "... ";

    static const User::field_e fields[] =
    {
            User::field_e::CREATION_TIME,
            User::field_e::MODIFICATION_TIME,
            User::field_e::STATUS,
            User::field_e::GENDER,
            User::field_e::TITLE,
            User::field_e::FIRST_NAME,
            User::field_e::LAST_NAME,
            User::field_e::COMPANY_NAME,
            User::field_e::EMAIL,
            User::field_e::PHONE,
            User::field_e::TIMEZONE,
            User::field_e::ZIP,
            User::field_e::COUNTRY,
            User::field_e::CITY,
            User::field_e::STREET,
            User::field_e::HOUSE_NUMBER,
            User::field_e::EAL,
            User::field_e::REGISTRATION_KEY,
            User::field_e::REGISTRATION_EXPIRATION,
            User::field_e::REGISTRATION_TIME,
    };

    for( auto f : fields )
    {
        anyvalue::Value v;

        if( u.record_->get_field( f, & v) )
        {
            os << to_string( f ) << "=" << anyvalue::StrHelper::to_string( v ) << " ";
        }
    }

    return os;
}

} // namespace user_manager

