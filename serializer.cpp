/*

Serializer.

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

// $Revision: 11641 $ $Date:: 2019-05-26 #$ $Author: serge $

#include "serializer.h"     // self

#include <stdexcept>        // std::invalid_argument

#include "anyvalue/serializer.h"        // save( ..., anyvalue::Value & )
#include "serializer/serializer.h"      // serializer::
#include "utils/hex_codec.h"            // utils::unhex_string

namespace serializer
{

user_manager::User::field_e * load( std::istream & is, user_manager::User::field_e * e )
{
    return user_manager::Serializer::load( is, e );
}

bool save( std::ostream & os, const user_manager::User::field_e & e )
{
    return user_manager::Serializer::save( os, e );
}

user_manager::User* load( std::istream & is, user_manager::User* e )
{
    if( e != nullptr )
        throw std::invalid_argument( "Serializer::load: e must be null" );

    auto el = new user_manager::User;

    auto res = user_manager::Serializer::load( is, static_cast< user_manager::User *>( el ) );

    if( res == nullptr )
    {
        delete el;
        return nullptr;
    }

    return el;
}

user_manager::User** load( std::istream & is, user_manager::User** e )
{
    auto res = load( is, static_cast< user_manager::User *>( nullptr ) );

    if( res == nullptr )
    {
        return nullptr;
    }

    *e =  res;

    return e;
}

bool save( std::ostream & os, const user_manager::User * e )
{
    return user_manager::Serializer::save( os, * e );
}

}

namespace user_manager
{

User* Serializer::load_1( std::istream & is, User* res )
{
    if( res == nullptr )
        throw std::invalid_argument( "Serializer::load: User is null" );

    uint32_t    status;
    std::string login;
    std::string password_hash;

    int         gender;
    std::string name;
    std::string first_name;
    std::string company_name;
    std::string email;
    std::string email_2;
    std::string phone;
    std::string phone_2;

    if( serializer::load( is, & res->user_id ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->group_id ) == nullptr )
        return nullptr;
    if( serializer::load( is, & status ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->login ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->password_hash ) == nullptr )
        return nullptr;
    if( serializer::load( is, & gender ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & name ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & first_name ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & company_name ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & email ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & email_2 ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & phone ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & phone_2 ) == nullptr )
        return nullptr;

    res->status         = static_cast<status_e>( status );
    res->password_hash  = utils::unhex_string( res->password_hash );

    static const int EMAIL_2    = user_manager::User::USER_DEFINED_FIELD_ID_BASE + 1;
    static const int PHONE_2    = user_manager::User::USER_DEFINED_FIELD_ID_BASE + 2;

    res->add_field( user_manager::User::GENDER,             gender );
    res->add_field( user_manager::User::LAST_NAME,          name );
    res->add_field( user_manager::User::FIRST_NAME,         first_name );
    res->add_field( user_manager::User::COMPANY_NAME,       company_name );
    res->add_field( user_manager::User::EMAIL,              email );
    res->add_field( user_manager::User::field_e(EMAIL_2),   email_2 );
    res->add_field( user_manager::User::PHONE,              phone );
    res->add_field( user_manager::User::field_e(PHONE_2),   phone_2 );

    return res;
}

User* Serializer::load_2( std::istream & is, User* res )
{
    if( res == nullptr )
        throw std::invalid_argument( "Serializer::load: res must not be null" );

    uint32_t    status;

    int         gender;
    std::string name;
    std::string first_name;
    std::string company_name;
    std::string email;
    std::string email_2;
    std::string phone;
    std::string phone_2;
    std::string timezone;

    if( serializer::load( is, & res->user_id ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->group_id ) == nullptr )
        return nullptr;
    if( serializer::load( is, & status ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->login ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->password_hash ) == nullptr )
        return nullptr;
    if( serializer::load( is, & gender ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & name ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & first_name ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & company_name ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & email ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & email_2 ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & phone ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & phone_2 ) == nullptr )
        return nullptr;
    if( serializer::load_enc( is, & timezone ) == nullptr )
        return nullptr;

    res->status         = static_cast<status_e>( status );
    res->password_hash  = utils::unhex_string( res->password_hash );

    static const int EMAIL_2    = user_manager::User::USER_DEFINED_FIELD_ID_BASE + 1;
    static const int PHONE_2    = user_manager::User::USER_DEFINED_FIELD_ID_BASE + 2;

    res->add_field( user_manager::User::GENDER,             gender );
    res->add_field( user_manager::User::LAST_NAME,          name );
    res->add_field( user_manager::User::FIRST_NAME,         first_name );
    res->add_field( user_manager::User::COMPANY_NAME,       company_name );
    res->add_field( user_manager::User::EMAIL,              email );
    res->add_field( user_manager::User::field_e(EMAIL_2),   email_2 );
    res->add_field( user_manager::User::PHONE,              phone );
    res->add_field( user_manager::User::field_e(PHONE_2),   phone_2 );
    res->add_field( user_manager::User::TIMEZONE,           timezone );

    return res;
}

User* Serializer::load_3( std::istream & is, User* res )
{
    if( res == nullptr )
        throw std::invalid_argument( "Serializer::load: res must not be null" );

    uint32_t    status;

    if( serializer::load( is, & res->user_id ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->group_id ) == nullptr )
        return nullptr;
    if( serializer::load( is, & status ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->login ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->password_hash ) == nullptr )
        return nullptr;

    res->status         = static_cast<status_e>( status );
    res->password_hash  = utils::unhex_string( res->password_hash );

    if( serializer::load( is, & res->map_id_to_value_ ) == nullptr )
        return nullptr;

    return res;
}

User* Serializer::load( std::istream & is, User* e )
{
    return load_t_1_2_3( is, e );
}

bool Serializer::save( std::ostream & os, const User & e )
{
    static const unsigned int VERSION = 3;

    auto b = serializer::save( os, VERSION );

    if( b == false )
        return false;

    b &= serializer::save( os, e.user_id );
    b &= serializer::save( os, e.group_id );
    b &= serializer::save( os, static_cast<unsigned>( e.status ) );
    b &= serializer::save( os, e.login );
    b &= serializer::save( os, utils::hex_string( e.password_hash ) );

    b &= serializer::save( os, e.map_id_to_value_ );

    return b;
}

User::field_e* Serializer::load( std::istream & is, User::field_e* e )
{
    uint32_t    v;

    if( serializer::load( is, & v ) == nullptr )
        return nullptr;

    * e = static_cast<User::field_e>( v );

    return e;
}

bool Serializer::save( std::ostream & os, const User::field_e & e )
{
    return serializer::save( os, static_cast<unsigned>( e ) );
}


} // namespace user_manager
