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

// $Revision: 6142 $ $Date:: 2017-03-20 #$ $Author: serge $

#ifndef USER_MANAGER_USER_MANAGER_H
#define USER_MANAGER_USER_MANAGER_H

#include <mutex>            // std::mutex
#include <map>              // std::map
#include <cstdint>          // uint32_t

#include "user.h"           // User

namespace user_manager
{

class UserManager
{
public:

    UserManager();

    bool init(
            const std::string & credentials_file );

private:

    typedef std::map<uint32_t,User>     MapUserIdToUser;

private:

    bool is_inited__() const;

    bool load_credentials( const std::string & credentials_file );

private:
    mutable std::mutex          mutex_;

    // Config
    std::string                 credentials_file_;

    MapUserIdToUser             map_id_to_user_;
};

} // namespace user_manager


#endif // USER_MANAGER_USER_MANAGER_H
