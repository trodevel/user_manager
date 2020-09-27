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

// $Revision: 13881 $ $Date:: 2020-09-27 #$ $Author: serge $

#include "user_manager.h"               // self

#include "utils/mutex_helper.h"         // MUTEX_SCOPE_LOCK
#include "utils/dummy_logger.h"         // dummy_log
#include "utils/utils_assert.h"               // ASSERT
#include "utils/get_now_epoch.h"        // get_now_epoch()
#include "utils/to_lower.h"             // utils::to_lower
#include "anyvalue/value_operations.h"  // anyvalue::compare_values

#define MODULENAME      "UserManager"

namespace user_manager
{

UserManager::UserManager()
{
}

UserManager::~UserManager()
{
}

void UserManager::init()
{
    req_id_gen_.init( 1, 1 );

    users_.reset( new anyvalue_db::Table() );

    users_->init( std::vector<anyvalue_db::field_id_t>( { User::USER_ID, User::LOGIN, User::REGISTRATION_KEY } ));
}

bool UserManager::load(
        const std::string   & filename,
        std::string         * error_msg )
{
    assert( is_inited__() );

    std::unique_ptr<anyvalue_db::Table> users( new anyvalue_db::Table() );

    auto b = users->init( filename );

    if( b == false )
    {
        * error_msg = "cannot load " + filename;
        return false;
    }

    anyvalue::Value last_id;

    b = users->get_meta_key( LAST_ID, & last_id );

    if( b == false )
    {
        * error_msg = "LAST_ID is missing";
        return false;
    }

    req_id_gen_.init( last_id.arg_i, 1 );

    users_.reset( users.release() );

    return b;
}

user_id_t UserManager::convert_login_to_user_id( const std::string & login, bool is_case_sensitive ) const
{
    auto l = is_case_sensitive ? login : utils::to_lower( login );

    assert( is_inited__() );

    auto & mutex = users_->get_mutex();

    MUTEX_SCOPE_LOCK( mutex );

    auto user = find__unlocked( l );

    if( user.is_empty() )
        return 0;

    return user.get_user_id();
}

bool UserManager::create_and_add_user(
        group_id_t          group_id,
        const std::string   & login,
        const std::string   & password_hash,
        const std::string   & registration_key,
        user_id_t           * user_id,
        std::string         * error_msg )
{
    assert( is_inited__() );

    auto & mutex = users_->get_mutex();

    MUTEX_SCOPE_LOCK( mutex );

    auto rec = users_->find__unlocked( User::LOGIN, login );

    if( rec != nullptr )
    {
        * error_msg = "login " + login + " is already used";

        dummy_log_error( MODULENAME, "create_and_add_user: cannot add user, login %s already exists", login.c_str() );

        return false;
    }

    auto id = req_id_gen_.get_next_request_id();

    User user( id, group_id, true, login, password_hash, registration_key, utils::get_now_epoch() );

    auto b = user.insert_into__unlocked( users_.get(), error_msg );

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
    assert( is_inited__() );

    auto & mutex = users_->get_mutex();

    MUTEX_SCOPE_LOCK( mutex );

    return users_->delete_record__unlocked( User::USER_ID, anyvalue::Value( int( user_id ) ), error_msg );
}

User UserManager::find__unlocked( user_id_t user_id )
{
    auto rec = users_->find__unlocked( User::USER_ID, anyvalue::Value( int( user_id ) ) );

    if( rec != nullptr )
        return User( rec );

    return User();
}

User UserManager::find__unlocked( user_id_t user_id ) const
{
    auto rec = users_->find__unlocked( User::USER_ID, anyvalue::Value( int( user_id ) ) );

    if( rec != nullptr )
        return User( rec );

    return User();
}

User UserManager::find__unlocked( const std::string & login )
{
    auto rec = users_->find__unlocked( User::LOGIN, anyvalue::Value( login ) );

    if( rec != nullptr )
        return User( rec );

    return User();
}

User UserManager::find__unlocked( const std::string & login ) const
{
    auto rec = users_->find__unlocked( User::LOGIN, anyvalue::Value( login ) );

    if( rec != nullptr )
        return User( rec );

    return User();
}

User UserManager::find_regkey__unlocked( const std::string & regkey )
{
    auto rec = users_->find__unlocked( User::REGISTRATION_KEY, anyvalue::Value( regkey ) );

    if( rec != nullptr )
        return User( rec );

    return User();
}

User UserManager::find_regkey__unlocked( const std::string & regkey ) const
{
    auto rec = users_->find__unlocked( User::REGISTRATION_KEY, anyvalue::Value( regkey ) );

    if( rec != nullptr )
        return User( rec );

    return User();
}

std::vector<User> UserManager::select_users__unlocked( const User::field_e field_id, anyvalue::comparison_type_e op, const Value & value ) const
{
    std::vector<User>  res;

    auto recs = users_->select__unlocked( field_id, op, value );

    for( auto r : recs )
    {
        res.push_back( User( r ) );
    }

    return res;
}

std::vector<User> UserManager::select_users__unlocked( bool is_or, const std::vector<SelectCondition> & conditions ) const
{
    std::vector<User>  res;

    auto recs = users_->select__unlocked( is_or, conditions );

    for( auto r : recs )
    {
        res.push_back( User( r ) );
    }

    return res;
}

std::mutex & UserManager::get_mutex() const
{
    return users_->get_mutex();
}

bool UserManager::is_inited__() const
{
    return users_ != nullptr;
}

bool UserManager::save( std::string * error_msg, const std::string & filename ) const
{
    assert( is_inited__() );

    users_->set_meta_key( LAST_ID, int( req_id_gen_.get_last_request_id() ) );

    return users_->save( error_msg, filename );
}


} // namespace user_manager
