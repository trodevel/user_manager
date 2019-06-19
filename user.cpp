/*

User.

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

// $Revision: 11755 $ $Date:: 2019-06-17 #$ $Author: serge $

#include "user.h"           // self

namespace user_manager
{

User::User():
                user_id( 0 ),
                group_id( 0 ),
                is_open_( false ),
                creation_time( 0 )
{
}

User::User(
        user_id_t           user_id,
        group_id_t          group_id,
        bool                is_open,
        const std::string   & login,
        const std::string   & password_hash,
        uint32_t            creation_time ):
                user_id( user_id ),
                group_id( group_id ),
                is_open_( is_open ),
                login( login ),
                password_hash( password_hash ),
                creation_time( creation_time )
{
}

User::~User()
{
}

user_id_t User::get_user_id() const
{
    return user_id;
}

group_id_t User::get_group_id() const
{
    return group_id;
}

bool User::is_open() const
{
    return is_open_;
}
const std::string & User::get_login() const
{
    return login;
}
const std::string & User::get_password_hash() const
{
    return password_hash;
}
utils::epoch32_t    User::get_creation_time() const
{
    return creation_time;
}

void User::set_password_hash( const std::string & p )
{
    password_hash   = p;
}

bool User::has_field( const field_e field_id ) const
{
    return map_id_to_value_.count( field_id ) > 0;
}

bool User::get_field( const field_e field_id, Value * res ) const
{
    auto it = map_id_to_value_.find( field_id );

    if( it == map_id_to_value_.end() )
        return false;

    * res = it->second;

    return true;
}

const Value & User::get_field( const field_e field_id ) const
{
    static const Value empty( 0 );

    auto it = map_id_to_value_.find( field_id );

    if( it == map_id_to_value_.end() )
        return empty;

    return it->second;
}

bool User::add_field( const field_e field_id, const Value & value )
{
    return map_id_to_value_.insert( std::make_pair( field_id, value ) ).second;
}

bool User::update_field( const field_e field_id, const Value & value )
{
    auto it = map_id_to_value_.find( field_id );

    if( it == map_id_to_value_.end() )
        return false;

    it->second  = value;

    return true;
}

bool User::delete_field( const field_e field_id )
{
    return map_id_to_value_.erase( field_id ) > 0;
}

} // namespace user_manager
