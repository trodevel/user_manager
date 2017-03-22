/*

User.

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

// $Revision: 6126 $ $Date:: 2017-03-20 #$ $Author: serge $

#ifndef USER_MANAGER_USER_H
#define USER_MANAGER_USER_H

#include <map>              // std::map
#include <cstdint>          // uint32_t

namespace user_manager
{

enum class status_e
{
    INACTIVE    = 0,
    ACTIVE      = 1,
    DELETED     = 2,
};

enum class gender_e
{
    UNDEF       = 0,
    MALE        = 1,
    FEMALE      = 2,
};

struct User
{
    uint32_t    user_id;
    uint32_t    group_id;
    status_e    status;
    std::string login;
    std::string password_hash;

    gender_e    gender;
    std::string name;
    std::string first_name;
    std::string company_name;
    std::string email;
    std::string email_2;
    std::string phone;
    std::string phone_2;
};

} // namespace user_manager


#endif // USER_MANAGER_USER_H
