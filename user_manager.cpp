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

bool UserManager::init(
        const std::string   & credentials_file )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    auto b = load_credentials( credentials_file );

    return b;
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

    dummy_log_info( MODULENAME, "load_credentials: loaded %d entries", map_id_to_user_.size() );

    return true;
}

} // namespace user_manager
