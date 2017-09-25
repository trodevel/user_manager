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

// $Revision: 7913 $ $Date:: 2017-09-25 #$ $Author: serge $

#ifndef USER_MANAGER_USER_MANAGER_H
#define USER_MANAGER_USER_MANAGER_H

#include <mutex>            // std::mutex
#include <map>              // std::map

#include "user.h"           // User

namespace user_manager
{

class UserManager
{
public:

    UserManager();
    ~UserManager();

    bool init(
            const std::string & credentials_file );

    bool add( User * user, std::string & error_msg );

    const User* find( user_id_t user_id ) const;

    const User* find( const std::string & login ) const;

private:

    typedef std::map<user_id_t,User*>       MapUserIdToUser;
    typedef std::map<std::string,user_id_t> MapLoginToUserId;

private:

    const User* find__( user_id_t user_id ) const;

    bool is_inited__() const;

    bool load_credentials( const std::string & credentials_file );
    bool init_login_map();

private:
    mutable std::mutex          mutex_;

    // Config
    std::string                 credentials_file_;

    MapUserIdToUser             map_id_to_user_;
    MapLoginToUserId            map_login_to_user_id_;
};

} // namespace user_manager


#endif // USER_MANAGER_USER_MANAGER_H
