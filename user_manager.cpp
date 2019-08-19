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

// $Revision: 11882 $ $Date:: 2019-08-16 #$ $Author: serge $

#include "user_manager.h"               // self

#include <fstream>                      // std::ifstream

#include "utils/mutex_helper.h"         // MUTEX_SCOPE_LOCK
#include "utils/dummy_logger.h"         // dummy_log
#include "utils/utils_assert.h"               // ASSERT
#include "utils/get_now_epoch.h"        // get_now_epoch()
#include "utils/rename_and_backup.h"    // utils::rename_and_backup
#include "anyvalue/value_operations.h"  // anyvalue::compare_values

#include "serializer.h"                 // serializer::load

#define MODULENAME      "UserManager"

namespace user_manager
{

UserManager::UserManager()
{
}

UserManager::~UserManager()
{
}

bool UserManager::init()
{
    req_id_gen_.init( 1, 1 );

    auto b = users_.init( std::vector<anyvalue_db::field_id_t>( { User::USER_ID, User::LOGIN, User::REGISTRATION_KEY } ));

    return b;
}

bool UserManager::load(
        const std::string   & filename,
        std::string         * error_msg )
{
    anyvalue_db::Table  users;

    auto b = users.init( filename );

    if( b == false )
    {
        * error_msg = "cannot load " + filename;
        return false;
    }

    users_  = users;

    return b;
}

bool UserManager::create_and_add_user(
        group_id_t          group_id,
        const std::string   & login,
        const std::string   & password_hash,
        const std::string   & registration_key,
        user_id_t           * user_id,
        std::string         * error_msg )
{
    auto & mutex = users_.get_mutex();

    MUTEX_SCOPE_LOCK( mutex );

    auto rec = users_.find__unlocked( User::LOGIN, login );

    if( rec != nullptr )
    {
        * error_msg = "login " + login + " is already used";

        dummy_log_error( MODULENAME, "create_and_add_user: cannot add user, login %s already exists", login.c_str() );

        return false;
    }

    auto id = req_id_gen_.get_next_request_id();

    User user( id, group_id, true, login, password_hash, registration_key, utils::get_now_epoch() );

    auto b = user.insert_into( & users_, error_msg );

    if( b == false )
    {
        dummy_log_error( MODULENAME, "create_and_add_user: cannot add user, login %s, %s", login.c_str(), error_msg->c_str() );

        return false;
    }

    * user_id = id;

    dummy_log_info( MODULENAME, "create_and_add_user: added user id %u, login %s", id, login.c_str() );

    return true;
}

bool UserManager::delete_user( user_id_t user_id, std::string * error_msg )
{
    auto & mutex = users_.get_mutex();

    MUTEX_SCOPE_LOCK( mutex );

    return users_.delete_record__unlocked( User::USER_ID, anyvalue::Value( user_id ), error_msg );
}

User* UserManager::find__unlocked( user_id_t user_id )
{
    return find__( user_id );
}

const User* UserManager::find__unlocked( user_id_t user_id ) const
{
    return find__( user_id );
}

User* UserManager::find__( user_id_t user_id )
{
    auto it = map_id_to_user_.find( user_id );

    if( it != map_id_to_user_.end() )
    {
        return it->second;
    }

    return nullptr;
}

const User* UserManager::find__( user_id_t user_id ) const
{
    auto it = map_id_to_user_.find( user_id );

    if( it != map_id_to_user_.end() )
    {
        return it->second;
    }

    return nullptr;
}

User* UserManager::find__unlocked( const std::string & login )
{
    auto it = map_login_to_user_id_.find( login );

    if( it != map_login_to_user_id_.end() )
    {
        return find__( it->second );
    }

    return nullptr;
}

const User* UserManager::find__unlocked( const std::string & login ) const
{
    auto it = map_login_to_user_id_.find( login );

    if( it != map_login_to_user_id_.end() )
    {
        return find__( it->second );
    }

    return nullptr;
}

std::vector<User*> UserManager::select_users__unlocked( const User::field_e field_id, anyvalue::comparison_type_e op, const Value & value ) const
{
    std::vector<User*>  res;

    for( auto & e : map_id_to_user_ )
    {
        auto user = e.second;

        if( user->is_open() == false )
            continue;

        Value v;

        if( user->get_field( field_id, & v ) )
        {
            if( anyvalue::compare_values( op, v, value ) )
            {
                res.push_back( e.second );
            }
        }
    }

    return res;
}

std::mutex & UserManager::get_mutex() const
{
    return users_.get_mutex();
}

bool UserManager::is_inited__() const
{
    return true;
}

bool UserManager::load_intern( const std::string & filename )
{
    std::ifstream is( filename );

    if( is.fail() )
    {
        dummy_log_warn( MODULENAME, "load_intern: cannot open credentials file %s", filename.c_str() );
        return false;
    }

    Status status;

    auto res = Serializer::load( is, & status );

    if( res == nullptr )
    {
        dummy_log_error( MODULENAME, "load_intern: cannot load credentials" );
        return false;
    }

    std::string error_msg;

    auto b = init_from_status( & error_msg, status );

    if( b == false )
    {
        dummy_log_error( MODULENAME, "load_intern: cannot init login map: %s", error_msg.c_str() );
        return false;
    }

    dummy_log_info( MODULENAME, "load_intern: loaded %d entries from %s, last id %u", map_id_to_user_.size(), filename.c_str(), status.last_id );

    return true;
}

bool UserManager::save( std::string * error_msg, const std::string & filename ) const
{
    MUTEX_SCOPE_LOCK( mutex_ );

    auto temp_name  = filename + ".tmp";

    auto b = save_intern( error_msg, temp_name );

    if( b == false )
        return false;

    utils::rename_and_backup( temp_name, filename );

    return true;
}

bool UserManager::save_intern( std::string * error_msg, const std::string & filename ) const
{
    std::ofstream os( filename );

    if( os.fail() )
    {
        dummy_log_error( MODULENAME, "save_intern: cannot open credentials file %s", filename.c_str() );

        * error_msg =  "cannot open file " + filename;

        return false;
    }

    Status status;

    get_status( & status );

    auto res = Serializer::save( os, status );

    if( res == false )
    {
        dummy_log_error( MODULENAME, "save_intern: cannot save credentials into file %s", filename.c_str()  );

        * error_msg =  "cannot save data into file " + filename;

        return false;
    }

    dummy_log_info( MODULENAME, "save: save %d entries into %s", map_id_to_user_.size(), filename.c_str() );

    return true;
}

void UserManager::get_status( Status * res ) const
{
    res->last_id   = req_id_gen_.get_last_request_id();

    for( auto & e : map_id_to_user_ )
    {
        res->users.push_back( e.second );
    }
}

bool UserManager::init_from_status( std::string * error_msg, const Status & status )
{
    req_id_gen_.init( status.last_id, 1 );

    map_id_to_user_.clear();

    for( auto & e : status.users )
    {
        auto b = map_id_to_user_.insert( std::make_pair( e->get_user_id(), e ) ).second;

        if( b == false )
        {
            * error_msg = "duplicate user id " + std::to_string( e->get_user_id() );

            return false;
        }
    }

    for( auto e : map_id_to_user_ )
    {
        auto b = map_login_to_user_id_.insert( std::make_pair( e.second->get_login(), e.first ) ).second;

        if( b == false )
        {
            * error_msg = "duplicate login " + e.second->get_login() + ", user id " + std::to_string( e.first );

            return false;
        }
    }

    return true;
}

} // namespace user_manager
