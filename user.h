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

// $Revision: 11884 $ $Date:: 2019-08-16 #$ $Author: serge $

#ifndef USER_MANAGER_USER_H
#define USER_MANAGER_USER_H

#include <map>              // std::map
#include "types.h"          // user_id_t
#include "anyvalue_db/table.h"  // Table
#include "utils/epoch32_t.h"    // utils::epoch32_t

namespace user_manager
{

typedef anyvalue::Value Value;

enum class status_e
{
    INACTIVE    = 0,
    ACTIVE      = 1,
    WAITING_REGISTRATION    = 2,
};

enum class gender_e
{
    UNDEF       = 0,
    MALE        = 1,
    FEMALE      = 2,
};

struct User
{
    friend class StrHelper;
    friend class Serializer;

    enum field_e
    {
        UNDEF   = 0,
        USER_ID,
        GROUP_ID,
        LOGIN,
        PASSWORD_HASH,
        IS_OPEN,
        CREATION_TIME,
        MODIFICATION_TIME,
        STATUS,
        GENDER,
        TITLE,
        FIRST_NAME,
        LAST_NAME,
        COMPANY_NAME,
        EMAIL,
        PHONE,
        TIMEZONE,
        ZIP,
        COUNTRY,
        CITY,
        STREET,
        HOUSE_NUMBER,
        EAL,
        REGISTRATION_KEY,
        REGISTRATION_EXPIRATION,
        USER_DEFINED_FIELD_ID_BASE  = 1000,
    };

    User();

    User(
            user_id_t           user_id,
            group_id_t          group_id,
            bool                is_open,
            const std::string   & login,
            const std::string   & password_hash,
            const std::string   & registration_key,
            uint32_t            creation_time );

    User(
            anyvalue_db::Record * record );

    ~User();

    bool is_empty() const;

    user_id_t get_user_id() const;
    group_id_t get_group_id() const;
    bool is_open() const;
    const std::string & get_login() const;
    const std::string & get_password_hash() const;
    utils::epoch32_t    get_creation_time() const;

    void set_password_hash( const std::string & password_hash );

    bool has_field( const field_e field_id ) const;
    bool get_field( const field_e field_id, Value * res ) const;
    const Value & get_field( const field_e field_id ) const;
    bool add_field( const field_e field_id, const Value & value );
    bool update_field( const field_e field_id, const Value & value );
    bool delete_field( const field_e field_id );

    bool insert_into( anyvalue_db::Table * table, std::string * error_msg );

private:

    struct Cache
    {
        Cache():
            has_user_id( false ),
            has_group_id( false ),
            has_is_open( false ),
            has_login( false ),
            has_password_hash( false ),
            has_registration_key( false ),
            has_creation_time( false )
        {}

        bool                has_user_id;
        user_id_t           user_id;

        bool                has_group_id;
        group_id_t          group_id;

        bool                has_is_open;
        bool                is_open;

        bool                has_login;
        std::string         login;

        bool                has_password_hash;
        std::string         password_hash;

        bool                has_registration_key;
        std::string         registration_key;

        bool                has_creation_time;
        utils::epoch32_t    creation_time;
    };

private:

    anyvalue_db::Record *record_;
    bool                is_inserted_;

    Cache               cache_;
};

} // namespace user_manager


#endif // USER_MANAGER_USER_H
