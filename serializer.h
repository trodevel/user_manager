/*

Serializer.

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

// $Revision: 11719 $ $Date:: 2019-06-06 #$ $Author: serge $

#ifndef USER_MANAGER_SERIALIZER_H
#define USER_MANAGER_SERIALIZER_H

#include <iostream>         // std::istream

#include "anyvalue/serializer.h"    // load( ..., anyvalue::Value * )

#include "serializer/versionable_loader_t.h"        // serializer::VersionableLoaderT
#include "user.h"           // User
#include "status.h"         // Status

namespace serializer
{
user_manager::User::field_e * load( std::istream & is, user_manager::User::field_e * e );
bool save( std::ostream & os, const user_manager::User::field_e & e );

user_manager::User** load( std::istream & is, user_manager::User** e );
bool save( std::ostream & os, const user_manager::User * e );
}

namespace user_manager
{

class Serializer: public serializer::VersionableLoaderT<Serializer>
{
    friend serializer::VersionableLoaderT<Serializer>;

public:
    static User* load( std::istream & is, User* e );
    static bool save( std::ostream & os, const User & e );

    static User::field_e* load( std::istream & is, User::field_e* e );
    static bool save( std::ostream & os, const User::field_e & e );

    static Status* load( std::istream & is, Status* e );
    static bool save( std::ostream & os, const Status & e );

private:

    static User* load_1( std::istream & is, User* e );
    static User* load_2( std::istream & is, User* e );
    static User* load_3( std::istream & is, User* e );

    static Status* load_1( std::istream & is, Status* e );
    static Status* load_2( std::istream & is, Status* e );
};

} // namespace user_manager

#endif // USER_MANAGER_SERIALIZER_H
