#include <iostream>
#include <string>

#include "user_manager.h"       //
#include "str_helper.h"         // StrHelper

void log_test(
        const std::string   & test_name,
        bool                res,
        bool                expected_res,
        const std::string   & exp_msg,
        const std::string   & not_exp_msg,
        const std::string   & error_msg )
{
    std::cout << "log_test: "<< test_name << " - ";

    if( res == expected_res )
    {
        std::cout << "OK: " << exp_msg;
    }
    else
    {
        std::cout << "ERROR: " << not_exp_msg;
    }

    if( ! error_msg.empty() )
    {
        std::cout << ": " << error_msg;
    }

    std::cout << std::endl;
}

user_manager::User create_user_1( user_manager::UserManager * um, std::string * error_msg )
{
    user_manager::user_id_t id;

    um->create_and_add_user( 1, "test", "\xf0\xf0\xf0", "abcd-1234", & id, error_msg );

    auto res = um->find__unlocked( id );

    res.add_field( user_manager::User::STATUS, int( user_manager::status_e::ACTIVE ) );
    res.add_field( user_manager::User::GENDER, int( user_manager::gender_e::MALE ) );
    res.add_field( user_manager::User::LAST_NAME,       "Doe" );
    res.add_field( user_manager::User::FIRST_NAME,      "John" );
    res.add_field( user_manager::User::COMPANY_NAME,    "Yoyodyne Inc." );
    res.add_field( user_manager::User::EMAIL,           "john.doe@yoyodyne.com" );
    //res.email_2 );
    res.add_field( user_manager::User::PHONE,           "+1234567890" );
    //res.phone_2 );
    res.add_field( user_manager::User::TIMEZONE,        "Europe/Berlin" );

    return res;
}

user_manager::User create_user_2( user_manager::UserManager * um, std::string * error_msg )
{
    user_manager::user_id_t id;

    um->create_and_add_user( 1, "test2", "\xae\xae\xae", "defg-4567", & id, error_msg );

    auto res = um->find__unlocked( id );

    static const int PHONE_2    = user_manager::User::USER_DEFINED_FIELD_ID_BASE + 1;

    res.add_field( user_manager::User::STATUS,          int( user_manager::status_e::ACTIVE ) );
    res.add_field( user_manager::User::GENDER,          int( user_manager::gender_e::FEMALE ) );
    res.add_field( user_manager::User::LAST_NAME,       "Bowie" );
    res.add_field( user_manager::User::FIRST_NAME,      "Doris" );
    res.add_field( user_manager::User::COMPANY_NAME,    "Yoyodyne Inc." );
    res.add_field( user_manager::User::EMAIL,           "doris.bowie@yoyodyne.com" );
    res.add_field( user_manager::User::PHONE,           "+9876542310" );
    res.add_field( user_manager::User::field_e(PHONE_2),   "+877777777" );
    res.add_field( user_manager::User::TIMEZONE,        "Europe/London" );

    return res;
}

void test_2()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    auto b = m.load( "users.duplicate_id.dat", & error_msg );

    if( b )
    {
        std::cout << "ERROR: file w/ broken IDs was unexpectedly loaded" << std::endl;
    }
    else
    {
        std::cout << "OK: file w/ broken IDs was not loaded (as expected)" << std::endl;
    }
}

void test_3( user_manager::UserManager & m )
{
    auto u = m.find__unlocked( "testuser" );

    if( ! u.is_empty() )
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
    auto u = m.find__unlocked( 2849000613 );

    if( ! u.is_empty() )
    {
        std::cout << "OK: found user: " << user_manager::StrHelper::to_string( u ) << std::endl;
    }
    else
    {
        std::cout << "ERROR: cannot find user" << std::endl;
    }
}


void test_1_save_ok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    create_user_1( & m, & error_msg );
    create_user_2( & m, & error_msg );

    auto b = m.save( & error_msg, "test.dat" );

    log_test( "test_1_save_ok_1", b, true, "user file was written", "cannot write file", error_msg );
}

void test_6( const user_manager::UserManager & m )
{
    std::string error_msg;
    m.save( & error_msg, "users_new.dat" );
}

void test_7()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    auto b = m.load( "users_new.dat", & error_msg );

    if( b )
    {
        std::cout << "OK: user file was loaded" << std::endl;
    }
    else
    {
        std::cout << "ERROR: cannot load users" << std::endl;
    }
}

void test_8()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    auto b = m.load( "users.duplicate_login.dat", & error_msg );

    if( b )
    {
        std::cout << "ERROR: file w/ duplicate logins was unexpectedly loaded" << std::endl;
    }
    else
    {
        std::cout << "OK: file w/ duplicate logins was not loaded (as expected)" << std::endl;
    }
}

int main( int argc, const char* argv[] )
{
    user_manager::UserManager m;


//    m.init();
//
//    std::string error_msg;
//
//    auto b = m.load( "users.v2.dat", & error_msg );
//
//    if( b )
//    {
//        std::cout << "OK: user file was loaded" << std::endl;
//    }
//    else
//    {
//        std::cout << "ERROR: cannot load users" << std::endl;
//        return -1;
//    }

//    test_2();
//    test_3( m );
//    test_4( m );
    test_1_save_ok_1();
    test_6( m );
    test_7();
    test_8();

    return 0;
}
