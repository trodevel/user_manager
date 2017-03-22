/*

User Manager.

Copyright (C) 2016 Sergey Kolevatov

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

// $Revision: 6161 $ $Date:: 2017-03-21 #$ $Author: serge $

#include "user_manager.h"               // self

#include <fstream>                      // std::ifstream

#include "utils/mutex_helper.h"         // MUTEX_SCOPE_LOCK
#include "utils/dummy_logger.h"         // dummy_log
#include "utils/assert.h"               // ASSERT

#include "serializer.h"                 // serializer::load

#define MODULENAME      "UserManager"

namespace user_manager
{

UserManager::UserManager()
{
}

UserManager::~UserManager()
{
    for( auto e: map_id_to_user_ )
    {
        delete e.second;
    }
}

bool UserManager::init(
        const std::string   & credentials_file )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    auto b = load_credentials( credentials_file );

    return b;
}

bool UserManager::add( User * user, std::string & error_msg )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    auto it = map_id_to_user_.find( user->user_id );
    if( it != map_id_to_user_.end() )
    {
        error_msg   = "user id " + std::to_string( user->user_id ) + " already exists";
        return false;
    }

    auto it2 = map_login_to_user_id_.find( user->login );
    if( it2 != map_login_to_user_id_.end() )
    {
        error_msg   = "user login " + user->login + " (with user id " + std::to_string( user->user_id ) + ") already exists";
        return false;
    }

    map_id_to_user_.insert( std::make_pair( user->user_id, user ) );
    map_login_to_user_id_.insert( std::make_pair( user->login, user->user_id ) );

    return true;
}

const User* UserManager::find( uint32_t user_id ) const
{
    MUTEX_SCOPE_LOCK( mutex_ );

    return find__( user_id );
}

const User* UserManager::find__( uint32_t user_id ) const
{
    auto it = map_id_to_user_.find( user_id );

    if( it != map_id_to_user_.end() )
    {
        return it->second;
    }

    return nullptr;
}

const User* UserManager::find( const std::string & login ) const
{
    MUTEX_SCOPE_LOCK( mutex_ );

    auto it = map_login_to_user_id_.find( login );

    if( it != map_login_to_user_id_.end() )
    {
        return find__( it->second );
    }

    return nullptr;
}

bool UserManager::is_inited__() const
{
    return true;
}

bool UserManager::load_credentials( const std::string & credentials_file )
{
    std::ifstream is( credentials_file );

    if( is.fail() )
    {
        dummy_log_warn( MODULENAME, "load_credentials: cannot open credentials file %s", credentials_file.c_str() );
        return false;
    }

    auto res = serializer::load( is, & map_id_to_user_ );

    if( res == nullptr )
    {
        dummy_log_error( MODULENAME, "load_credentials: cannot load credentials" );
        return false;
    }

    auto b = init_login_map();

    if( b == false )
    {
        dummy_log_error( MODULENAME, "load_credentials: cannot init login map, duplicate logins found" );
        return false;
    }

    dummy_log_info( MODULENAME, "load_credentials: loaded %d entries", map_id_to_user_.size() );

    return true;
}

bool UserManager::init_login_map()
{
    for( auto e : map_id_to_user_ )
    {
        auto b = map_login_to_user_id_.insert( std::make_pair( e.second->login, e.first ) ).second;

        if( b == false )
        {
            return false;
        }
    }

    return true;
}

} // namespace user_manager
