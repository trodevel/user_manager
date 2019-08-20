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

// $Revision: 11905 $ $Date:: 2019-08-20 #$ $Author: serge $

#include "user.h"           // self

#include <cassert>

namespace user_manager
{

User::User():
        record_( nullptr ),
        is_inserted_( false )
{
}

User::User(
        user_id_t           user_id,
        group_id_t          group_id,
        bool                is_open,
        const std::string   & login,
        const std::string   & password_hash,
        const std::string   & registration_key,
        uint32_t            creation_time ):
        is_inserted_( false )
{
    record_ = new anyvalue_db::Record;

    record_->add_field( USER_ID,            anyvalue::Value( int( user_id ) ) );
    record_->add_field( GROUP_ID,           anyvalue::Value( int( group_id ) ) );
    record_->add_field( IS_OPEN,            anyvalue::Value( is_open ) );
    record_->add_field( LOGIN,              anyvalue::Value( login ) );
    record_->add_field( PASSWORD_HASH,      anyvalue::Value( password_hash ) );
    record_->add_field( REGISTRATION_KEY,   anyvalue::Value( registration_key ) );
    record_->add_field( CREATION_TIME,      anyvalue::Value( int ( creation_time ) ) );

    cache_.user_id          = user_id;
    cache_.group_id         = group_id;
    cache_.is_open          = is_open;
    cache_.login            = login;
    cache_.password_hash    = password_hash;
    cache_.registration_key = registration_key;
    cache_.creation_time    = creation_time;

    cache_.has_user_id          = true;
    cache_.has_group_id         = true;
    cache_.has_is_open          = true;
    cache_.has_login            = true;
    cache_.has_password_hash    = true;
    cache_.has_registration_key = true;
    cache_.has_creation_time    = true;
}


User::User(
        anyvalue_db::Record * record ):
                record_( record ),
                is_inserted_( true )
{
}

User::~User()
{
    if( is_inserted_ == false )
    {
        if( record_ != nullptr )
            delete record_;
    }
}

bool User::is_empty() const
{
    assert( is_inserted_ == false );

    return record_ == nullptr;
}

user_id_t User::get_user_id() const
{
    if( cache_.has_user_id )
        return cache_.user_id;

    cache_.user_id      = get_field( USER_ID ).arg_i;
    cache_.has_user_id  = true;

    return cache_.user_id;
}

group_id_t User::get_group_id() const
{
    if( cache_.has_group_id )
        return cache_.group_id;

    cache_.group_id      = get_field( GROUP_ID ).arg_i;
    cache_.has_group_id  = true;

    return cache_.group_id;
}

bool User::is_open() const
{
    if( cache_.has_is_open )
        return cache_.is_open;

    cache_.is_open      = get_field( IS_OPEN ).arg_b;
    cache_.has_is_open  = true;

    return cache_.is_open;
}
const std::string & User::get_login() const
{
    if( cache_.has_login )
        return cache_.login;

    cache_.login      = get_field( LOGIN ).arg_s;
    cache_.has_login  = true;

    return cache_.login;
}
const std::string & User::get_password_hash() const
{
    if( cache_.has_password_hash )
        return cache_.password_hash;

    cache_.password_hash      = get_field( PASSWORD_HASH ).arg_s;
    cache_.has_password_hash  = true;

    return cache_.password_hash;
}
utils::epoch32_t    User::get_creation_time() const
{
    if( cache_.has_creation_time )
        return cache_.creation_time;

    cache_.creation_time      = get_field( CREATION_TIME ).arg_i;
    cache_.has_creation_time  = true;

    return cache_.creation_time;
}

void User::set_password_hash( const std::string & p )
{
    cache_.has_password_hash    = true;
    cache_.password_hash        = p;

    update_field( PASSWORD_HASH, p );
}

bool User::has_field( const field_e field_id ) const
{
    return record_->has_field( field_id );
}

bool User::get_field( const field_e field_id, Value * res ) const
{
    return record_->get_field( field_id, res );
}

Value User::get_field( const field_e field_id ) const
{
    static const Value empty( 0 );

    Value res;

    auto b = record_->get_field( field_id, & res );

    if( b == false )
        return empty;

    return res;
}

bool User::add_field( const field_e field_id, const Value & value )
{
    return record_->add_field( field_id, value );
}

bool User::update_field( const field_e field_id, const Value & value )
{
    return record_->update_field( field_id, value );
}

bool User::delete_field( const field_e field_id )
{
    return record_->delete_field( field_id );
}

bool User::add_field( const field_e field_id, bool value )
{
    return add_field( field_id, anyvalue::Value( value ) );
}

bool User::add_field( const field_e field_id, int value )
{
    return add_field( field_id, anyvalue::Value( value ) );
}

bool User::add_field( const field_e field_id, double value )
{
    return add_field( field_id, anyvalue::Value( value ) );
}

bool User::add_field( const field_e field_id, const std::string & value )
{
    return add_field( field_id, anyvalue::Value( value ) );
}

bool User::add_field( const field_e field_id, int value );
bool User::add_field( const field_e field_id, double value );
bool User::add_field( const field_e field_id, const std::string & value );

bool User::insert_into( anyvalue_db::Table * table, std::string * error_msg )
{
    if( is_inserted_ == true )
    {
        assert( 0 );    // should not happen

        * error_msg = "record is already inserted";

        return false;
    }

    auto b = table->add_record( record_, error_msg );

    if( b )
    {
        is_inserted_    = true;
    }

    return b;
}

} // namespace user_manager
