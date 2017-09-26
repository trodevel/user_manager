#include <iostream>
#include <string>

#include "user_manager.h"       //
#include "str_helper.h"         // StrHelper

void test_2()
{
    user_manager::UserManager m;

    user_manager::User * u = new user_manager::User;

    u->user_id  = 1;
    u->group_id = 1;
    u->status   = user_manager::status_e::ACTIVE;
    u->login    = "test";
    u->password_hash    = "f0f0f0";

    u->gender   = user_manager::gender_e::MALE;
    u->name         = "Doe";
    u->first_name   = "John";
    u->company_name = "Yoyodyne Inc.";
    u->email        = "joh.doe@yoyodyne.com";
    //u->email_2;
    u->phone        = "+1234567890";
    //u->phone_2;
    u->timezone     = "Europe/Berlin";

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

    return 0;
}
