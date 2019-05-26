#include <iostream>
#include <string>

#include "user_manager.h"       //
#include "str_helper.h"         // StrHelper

user_manager::User * create_user_1()
{
    auto res = new user_manager::User;

    res->user_id        = 1;
    res->group_id       = 1;
    res->status         = user_manager::status_e::ACTIVE;
    res->login          = "test";
    res->password_hash  = "\xf0\xf0\xf0";

    res->add_field( user_manager::User::GENDER, int( user_manager::gender_e::MALE ) );

    res->add_field( user_manager::User::LAST_NAME,      "Doe" );
    res->add_field( user_manager::User::FIRST_NAME,     "John" );
    res->add_field( user_manager::User::COMPANY_NAME,   "Yoyodyne Inc." );
    res->add_field( user_manager::User::EMAIL,          "john.doe@yoyodyne.com" );
    //res->email_2 );
    res->add_field( user_manager::User::PHONE,          "+1234567890" );
    //res->phone_2 );
    res->add_field( user_manager::User::TIMEZONE,       "Europe/Berlin" );

    return res;
}

user_manager::User * create_user_2()
{
    auto res = new user_manager::User;

    res->user_id        = 2;
    res->group_id       = 1;
    res->status         = user_manager::status_e::ACTIVE;
    res->login          = "test2";
    res->password_hash  = "\xae\xae\xae";

    static const int PHONE_2    = user_manager::User::USER_DEFINED_FIELD_ID_BASE + 1;

    res->add_field( user_manager::User::GENDER,         int( user_manager::gender_e::FEMALE ) );
    res->add_field( user_manager::User::LAST_NAME,      "Bowie" );
    res->add_field( user_manager::User::FIRST_NAME,     "Doris" );
    res->add_field( user_manager::User::COMPANY_NAME,   "Yoyodyne Inc." );
    res->add_field( user_manager::User::EMAIL,          "doris.bowie@yoyodyne.com" );
    res->add_field( user_manager::User::PHONE,          "+9876542310" );
    res->add_field( user_manager::User::field_e(PHONE_2),   "+877777777" );
    res->add_field( user_manager::User::TIMEZONE,       "Europe/London" );

    return res;
}

void test_2()
{
    user_manager::UserManager m;

    auto u = create_user_1();

    std::string error_msg;

    auto b = m.add_loaded( u, error_msg );

    if( b )
    {
        std::cout << "OK: user was added" << std::endl;
    }
    else
    {
        std::cout << "ERROR: cannot add user" << std::endl;
    }

    b = m.add_loaded( u, error_msg );

    if( b == false )
    {
        std::cout << "OK: duplicate user was not added" << std::endl;
    }
    else
    {
        std::cout << "ERROR: duplicated user was added" << std::endl;
    }
}

void test_3( user_manager::UserManager & m )
{
    auto u = m.find__unlocked( "testuser" );

    if( u )
    {
        std::cout << "OK: found user: " << user_manager::StrHelper::to_string( * u ) << std::endl;
    }
    else
    {
        std::cout << "ERROR: cannot find user" << std::endl;
    }
}

void test_4( user_manager::UserManager & m )
{
    auto u = m.find( 2849000613 );

    if( u )
    {
        std::cout << "OK: found user: " << user_manager::StrHelper::to_string( * u ) << std::endl;
    }
    else
    {
        std::cout << "ERROR: cannot find user" << std::endl;
    }
}


void test_5()
{
    user_manager::UserManager m;

    auto u1 = create_user_1();
    auto u2 = create_user_2();

    std::string error_msg;

    m.add_loaded( u1, error_msg );
    m.add_loaded( u2, error_msg );

    auto b = m.save( & error_msg, "test.dat" );

    if( b )
    {
        std::cout << "OK: user file was written" << std::endl;
    }
    else
    {
        std::cout << "ERROR: cannot write file: " << error_msg << std::endl;
    }
}

int main( int argc, const char* argv[] )
{
    user_manager::UserManager m;

    auto b = m.init( "users.dat" );

    if( b )
    {
        std::cout << "OK: user file was loaded" << std::endl;
    }
    else
    {
        std::cout << "ERROR: cannot load users" << std::endl;
        return -1;
    }

    test_2();
    test_3( m );
    test_4( m );
    test_5();

    return 0;
}
