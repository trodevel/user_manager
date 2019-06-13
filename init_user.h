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

// $Revision: 11732 $ $Date:: 2019-06-13 #$ $Author: serge $

#ifndef USER_MANAGER__INIT_USER_H
#define USER_MANAGER__INIT_USER_H

#include "user.h"           // User

namespace user_manager
{

inline User * init_User(
        User                * res,
        user_id_t           user_id,
        group_id_t          group_id,
        const std::string   & login,
        const std::string   & password_hash,
        utils::epoch32_t    creation_time )
{
    res->user_id    = user_id;
    res->group_id   = group_id;
    res->is_open    = true;
    res->login      = login;
    res->password_hash  = password_hash;
    res->creation_time  = creation_time;

    return res;
}

} // namespace user_manager


#endif // USER_MANAGER__INIT_USER_H
