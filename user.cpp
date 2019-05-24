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

// $Revision: 11594 $ $Date:: 2019-05-24 #$ $Author: serge $

#include "user.h"           // self

namespace user_manager
{

bool User::has_field( const field_e field_id ) const
{
    return map_id_to_value_.count( field_id ) > 0;
}

bool User::get_field( const field_e field_id, Value * res ) const
{
    auto it = map_id_to_value_.find( field_id );

    if( it == map_id_to_value_.end() )
        return false;

    * res = it->second;

    return true;
}

bool User::add_field( const field_e field_id, const Value & value )
{
    return map_id_to_value_.insert( std::make_pair( field_id, value ) ).second;
}

bool User::delete_field( const field_e field_id )
{
    return map_id_to_value_.erase( field_id ) > 0;
}

} // namespace user_manager


#endif // USER_MANAGER_USER_H
