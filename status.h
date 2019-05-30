/*

User Manager. Status.

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

// $Revision: 11671 $ $Date:: 2019-05-30 #$ $Author: serge $

#ifndef USER_MANAGER__STATUS_H
#define USER_MANAGER__STATUS_H

#include <vector>           // std::vector

#include "user.h"           // User

namespace user_manager
{

struct Status
{
    uint32_t            last_id;
    std::vector<User*>  users;
};

} // namespace user_manager

#endif // USER_MANAGER__STATUS_H
