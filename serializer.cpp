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

// $Revision: 7939 $ $Date:: 2017-09-28 #$ $Author: serge $

#include "serializer.h"     // self

#include <stdexcept>        // std::invalid_argument

#include "utils/nonascii_hex_codec.h"   // nonascii_hex_codec::decode
#include "utils/hex_codec.h"            // utils::unhex_string

namespace serializer
{

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

User* Serializer::load_1( std::istream & is, User* e )
{
    if( e == nullptr )
        throw std::invalid_argument( "Serializer::load: User is null" );

    uint32_t    user_id;
    uint32_t    group_id;
    uint32_t    status;
    std::string login;
    std::string password_hash;

    uint32_t    gender;
    std::string name;
    std::string first_name;
    std::string company_name;
    std::string email;
    std::string email_2;
    std::string phone;
    std::string phone_2;

    is >> user_id >> group_id >> status >> login >> password_hash
        >> gender >> name >> first_name >> company_name >> email >> email_2
        >> phone >> phone_2;

    if( is.fail() )
        return nullptr;

    e->user_id      = user_id;
    e->group_id     = group_id;
    e->status       = static_cast<status_e>( status );
    e->login        = login;
    e->password_hash    = utils::unhex_string( password_hash );

    e->gender       = static_cast<gender_e>( gender );
    e->name         = utils::nonascii_hex_codec::decode( name );
    e->first_name   = utils::nonascii_hex_codec::decode( first_name );
    e->company_name = utils::nonascii_hex_codec::decode( company_name );
    e->email        = utils::nonascii_hex_codec::decode( email );
    e->email_2      = utils::nonascii_hex_codec::decode( email_2 );
    e->phone        = utils::nonascii_hex_codec::decode( phone );
    e->phone_2      = utils::nonascii_hex_codec::decode( phone_2 );

    return e;
}

User* Serializer::load_2( std::istream & is, User* res )
{
    if( res == nullptr )
        throw std::invalid_argument( "Serializer::load: res must not be null" );

    uint32_t    status;
    uint32_t    gender;

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
    if( serializer::load( is, & res->name ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->first_name ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->company_name ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->email ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->email_2 ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->phone ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->phone_2 ) == nullptr )
        return nullptr;
    if( serializer::load( is, & res->timezone ) == nullptr )
        return nullptr;

    res->status     = static_cast<status_e>( status );
    res->gender     = static_cast<gender_e>( gender );

    res->password_hash  = utils::unhex_string( res->password_hash );
    res->name           = utils::nonascii_hex_codec::decode( res->name );
    res->first_name     = utils::nonascii_hex_codec::decode( res->first_name );
    res->company_name   = utils::nonascii_hex_codec::decode( res->company_name );
    res->email          = utils::nonascii_hex_codec::decode( res->email );
    res->email_2        = utils::nonascii_hex_codec::decode( res->email_2 );
    res->phone          = utils::nonascii_hex_codec::decode( res->phone );
    res->phone_2        = utils::nonascii_hex_codec::decode( res->phone_2 );

    return res;
}

User* Serializer::load( std::istream & is, User* e )
{
    return load_t_1_2( is, e );
}

bool Serializer::save( std::ostream & os, const User & e )
{
    static const unsigned int VERSION = 2;

    auto b = serializer::save( os, VERSION );

    if( b == false )
        return false;

    b &= serializer::save( os, e.user_id );
    b &= serializer::save( os, e.group_id );
    b &= serializer::save( os, static_cast<unsigned>( e.status ) );
    b &= serializer::save( os, e.login );
    b &= serializer::save( os, utils::hex_string( e.password_hash ) );
    b &= serializer::save( os, static_cast<unsigned>( e.gender ) );
    b &= serializer::save( os, utils::nonascii_hex_codec::encode( e.name ) );
    b &= serializer::save( os, utils::nonascii_hex_codec::encode( e.first_name ) );
    b &= serializer::save( os, utils::nonascii_hex_codec::encode( e.company_name ) );
    b &= serializer::save( os, utils::nonascii_hex_codec::encode( e.email ) );
    b &= serializer::save( os, utils::nonascii_hex_codec::encode( e.email_2 ) );
    b &= serializer::save( os, utils::nonascii_hex_codec::encode( e.phone ) );
    b &= serializer::save( os, utils::nonascii_hex_codec::encode( e.phone_2 ) );
    b &= serializer::save( os, e.timezone );

    return b;
}

} // namespace user_manager
