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

    res->gender         = user_manager::gender_e::MALE;
    res->name           = "Doe";
    res->first_name     = "John";
    res->company_name   = "Yoyodyne Inc.";
    res->email          = "john.doe@yoyodyne.com";
    //res->email_2;
    res->phone          = "+1234567890";
    //res->phone_2;
    res->timezone       = "Europe/Berlin";

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

    res->gender         = user_manager::gender_e::FEMALE;
    res->name           = "Bowie";
    res->first_name     = "Doris";
    res->company_name   = "Yoyodyne Inc.";
    res->email          = "doris.bowie@yoyodyne.com";
    //res->email_2;
    res->phone          = "+9876542310";
    res->phone_2        = "+877777777";
    res->timezone       = "Europe/London";

    return res;
}

void test_2()
{
    user_manager::UserManager m;

    auto u = create_user_1();

    std::string error_msg;

    auto b = m.add( u, error_msg );

    if( b )
    {
        std::cout << "OK: user was added" << std::endl;
    }
    else
    {
        std::cout << "ERROR: cannot add user" << std::endl;
    }

    b = m.add( u, error_msg );

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
    auto u = m.find( "testuser" );

    if( u )
    {
        std::cout << "OK: found user: " << user_manager::StrHelper::to_string( u ) << std::endl;
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
        std::cout << "OK: found user: " << user_manager::StrHelper::to_string( u ) << std::endl;
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

    m.add( u1, error_msg );
    m.add( u2, error_msg );

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
