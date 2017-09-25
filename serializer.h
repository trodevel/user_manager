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

// $Revision: 7916 $ $Date:: 2017-09-25 #$ $Author: serge $

#ifndef USER_MANAGER_SERIALIZER_H
#define USER_MANAGER_SERIALIZER_H

#include <iostream>         // std::istream

#include "serializer/versionable_loader_t.h"        // serializer::VersionableLoaderT
#include "user.h"           // User

namespace serializer
{
user_manager::User** load( std::istream & is, user_manager::User** e );
}

#include "serializer/serializer.h"   // serializer::

namespace user_manager
{

class Serializer: public serializer::VersionableLoaderT<Serializer>
{
    friend serializer::VersionableLoaderT<Serializer>;

public:
    static User* load( std::istream & is, User* e );
    static bool save( std::ostream & os, const User & e );

private:

    static User* load_1( std::istream & is, User* e );
    static User* load_2( std::istream & is, User* e );
};

} // namespace user_manager

#endif // USER_MANAGER_SERIALIZER_H
