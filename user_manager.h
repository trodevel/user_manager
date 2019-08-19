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

// $Revision: 11891 $ $Date:: 2019-08-19 #$ $Author: serge $

#ifndef USER_MANAGER_USER_MANAGER_H
#define USER_MANAGER_USER_MANAGER_H

#include <mutex>            // std::mutex
#include <map>              // std::map

#include "user.h"           // User
#include "status.h"         // Status

#include "anyvalue/operations.h"    // anyvalue::comparison_type_e
#include "anyvalue_db/table.h"      // anyvalue_db::Table

#include "utils/request_id_gen.h"   // utils::RequestIdGen

namespace user_manager
{

class UserManager
{
    friend class Serializer;

public:

    UserManager();
    ~UserManager();

    bool init();

    bool load(
            const std::string   & filename,
            std::string         * error_msg );

    bool create_and_add_user(
            group_id_t          group_id,
            const std::string   & login,
            const std::string   & password_hash,
            const std::string   & registration_key,
            user_id_t           * user_id,
            std::string         * error_msg );
    bool delete_user( user_id_t user_id, std::string * error_msg );

    User find__unlocked( user_id_t user_id );
    User find__unlocked( user_id_t user_id ) const;

    User find__unlocked( const std::string & login );
    User find__unlocked( const std::string & login ) const;

    User find_regkey__unlocked( const std::string & regkey );
    User find_regkey__unlocked( const std::string & regkey ) const;

    std::vector<User> select_users__unlocked( const User::field_e field_id, anyvalue::comparison_type_e op, const Value & value ) const;

    bool save( std::string * error_msg, const std::string & filename ) const;

    std::mutex & get_mutex() const;

private:

    bool is_inited__() const;

private:
    // Config
    std::string                 credentials_file_;

    anyvalue_db::Table          users_;

    utils::RequestIdGen         req_id_gen_;
};

} // namespace user_manager


#endif // USER_MANAGER_USER_MANAGER_H
