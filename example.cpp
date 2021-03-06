#include <iostream>
#include <string>

#include "user_manager.h"       //
#include "str_helper.h"         // StrHelper
#include "utils/log_test.h"     // log_test

bool create_user_1( user_manager::UserManager * um, user_manager::user_id_t * id, std::string * error_msg )
{
    return um->create_and_add_user( 1, "test", "\xf0\xf0\xf0", "abcd-1234", id, error_msg );
}

bool create_user_2( user_manager::UserManager * um, user_manager::user_id_t * id, std::string * error_msg )
{
    return um->create_and_add_user( 1, "test2", "\xae\xae\xae", "defg-4567", id, error_msg );
}

bool create_user_3( user_manager::UserManager * um, user_manager::user_id_t * id, std::string * error_msg )
{
    return um->create_and_add_user( 1, "test3", "\xff\xff\xff", "a1b2-c7d8", id, error_msg );
}

bool create_user_4( user_manager::UserManager * um, user_manager::user_id_t * id, std::string * error_msg )
{
    return um->create_and_add_user( 1, "test4", "\xa1\xa1\xa1", "hgfs-uiy3", id, error_msg );
}

user_manager::User init_user_1( user_manager::UserManager * um, user_manager::user_id_t id, std::string * error_msg )
{
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

user_manager::User init_user_2( user_manager::UserManager * um, user_manager::user_id_t id, std::string * error_msg )
{
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

user_manager::User init_user_3( user_manager::UserManager * um, user_manager::user_id_t id, std::string * error_msg )
{
    auto res = um->find__unlocked( id );

    res.add_field( user_manager::User::STATUS,          int( user_manager::status_e::INACTIVE ) );
    res.add_field( user_manager::User::GENDER,          int( user_manager::gender_e::MALE ) );
    res.add_field( user_manager::User::LAST_NAME,       "Farmer" );
    res.add_field( user_manager::User::FIRST_NAME,      "Bogdan" );
    res.add_field( user_manager::User::COMPANY_NAME,    "Yoyodyne Inc." );
    res.add_field( user_manager::User::EMAIL,           "bogdan.farmer@yoyodyne.com" );
    res.add_field( user_manager::User::PHONE,           "+9876547777" );
    res.add_field( user_manager::User::TIMEZONE,        "Europe/Paris" );

    return res;
}

user_manager::User init_user_4( user_manager::UserManager * um, user_manager::user_id_t id, std::string * error_msg )
{
    auto res = um->find__unlocked( id );

    res.add_field( user_manager::User::STATUS,          int( user_manager::status_e::INACTIVE ) );
    res.add_field( user_manager::User::GENDER,          int( user_manager::gender_e::FEMALE ) );
    res.add_field( user_manager::User::LAST_NAME,       "Muller" );
    res.add_field( user_manager::User::FIRST_NAME,      "Anna" );
    res.add_field( user_manager::User::COMPANY_NAME,    "Yoyodyne Inc." );
    res.add_field( user_manager::User::EMAIL,           "anna.muller@yoyodyne.com" );
    res.add_field( user_manager::User::PHONE,           "+9876548787" );
    res.add_field( user_manager::User::TIMEZONE,        "Europe/Berlin" );

    return res;
}

void dump_selection( const std::vector<user_manager::User> & vec, const std::string & comment )
{
    std::cout << comment << ":" << "\n";

    for( auto & e : vec )
    {
        std::cout << user_manager::StrHelper::to_string( e ) << "\n";
    }

    std::cout << "\n";
}

void test_1_add_ok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    auto b = create_user_1( & m, & id, & error_msg );

    log_test( "test_1_add_ok_1", b, true, "user was added", "cannot add user", error_msg );
}

void test_1_add_nok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );

    auto b = create_user_1( & m, & id, & error_msg );

    log_test( "test_1_add_nok_1", b, false, "user was not added", "user was unexpectedly added", error_msg );
}

void test_2_delete_ok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );

    auto b = m.delete_user( id, & error_msg );

    log_test( "test_2_delete_ok_1", b, true, "user was deleted", "cannot delete user", error_msg );
}

void test_2_delete_ok_2()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    create_user_2( & m, & id, & error_msg );
    create_user_3( & m, & id, & error_msg );

    auto b = m.delete_user( id, & error_msg );

    log_test( "test_2_delete_ok_2", b, true, "user was deleted", "cannot delete user", error_msg );
}

void test_2_delete_nok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    auto b = m.delete_user( 121212, & error_msg );

    log_test( "test_2_delete_nok_1", b, false, "user was not deleted", "user was unexpectedly deleted", error_msg );
}

void test_3_find_ok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    create_user_2( & m, & id, & error_msg );
    create_user_3( & m, & id, & error_msg );

    auto b = m.find__unlocked( id );

    log_test( "test_3_find_ok_1", b.is_empty() == false, true, "user was found", "cannot find user", error_msg );
}

void test_3_find_ok_2()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    create_user_2( & m, & id, & error_msg );
    create_user_3( & m, & id, & error_msg );

    auto b = m.find__unlocked( "test2" );

    log_test( "test_3_find_ok_2", b.is_empty() == false, true, "user was found", "cannot find user", error_msg );
}

void test_3_find_ok_3()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    create_user_2( & m, & id, & error_msg );
    create_user_3( & m, & id, & error_msg );

    auto b = m.find_regkey__unlocked( "abcd-1234" );

    log_test( "test_3_find_ok_3", b.is_empty() == false, true, "user was found", "cannot find user", error_msg );
}

void test_3_find_nok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    create_user_2( & m, & id, & error_msg );
    create_user_3( & m, & id, & error_msg );

    auto b = m.find__unlocked( 121212 );

    log_test( "test_3_find_nok_1", b.is_empty(), true, "non-existing user was not found", "non-existing user was unexpectedly found", error_msg );
}

void test_3_find_nok_2()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    create_user_2( & m, & id, & error_msg );
    create_user_3( & m, & id, & error_msg );

    auto b = m.find__unlocked( "test4" );

    log_test( "test_3_find_nok_2", b.is_empty(), true, "non-existing user was not found", "non-existing user was unexpectedly found", error_msg );
}

void test_3_find_nok_3()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    create_user_2( & m, & id, & error_msg );
    create_user_3( & m, & id, & error_msg );

    auto b = m.find_regkey__unlocked( "abcd-5678" );

    log_test( "test_3_find_nok_3", b.is_empty(), true, "non-existing user was not found", "non-existing user was unexpectedly found", error_msg );
}

void test_4_select_ok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    init_user_1( & m, id, & error_msg );

    create_user_2( & m, & id, & error_msg );
    init_user_2( & m, id, & error_msg );

    create_user_3( & m, & id, & error_msg );
    init_user_3( & m, id, & error_msg );

    auto res = m.select_users__unlocked( user_manager::User::STATUS, anyvalue::comparison_type_e::EQ, int( user_manager::status_e::ACTIVE ) );

    dump_selection( res, "users" );

    log_test( "test_4_select_ok_1", res.size() == 2, true, "users were found", "users were not found", error_msg );
}

void test_4_select_ok_2()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    init_user_1( & m, id, & error_msg );

    create_user_2( & m, & id, & error_msg );
    init_user_2( & m, id, & error_msg );

    create_user_3( & m, & id, & error_msg );
    init_user_3( & m, id, & error_msg );

    auto res = m.select_users__unlocked( user_manager::User::STATUS, anyvalue::comparison_type_e::EQ, int( user_manager::status_e::INACTIVE ) );

    dump_selection( res, "users" );

    log_test( "test_4_select_ok_2", res.size() == 1, true, "user was found", "user was not found", error_msg );
}

void test_4_select_ok_3()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    init_user_1( & m, id, & error_msg );

    create_user_2( & m, & id, & error_msg );
    init_user_2( & m, id, & error_msg );

    create_user_3( & m, & id, & error_msg );
    init_user_3( & m, id, & error_msg );

    auto res = m.select_users__unlocked( user_manager::User::COMPANY_NAME, anyvalue::comparison_type_e::EQ, "Yoyodyne Inc." );

    dump_selection( res, "users" );

    log_test( "test_4_select_ok_3", res.size() == 3, true, "users were found", "users were not found", error_msg );
}

void test_4_multi_select_ok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    init_user_1( & m, id, & error_msg );

    create_user_2( & m, & id, & error_msg );
    init_user_2( & m, id, & error_msg );

    create_user_3( & m, & id, & error_msg );
    init_user_3( & m, id, & error_msg );

    create_user_4( & m, & id, & error_msg );
    init_user_4( & m, id, & error_msg );

    user_manager::UserManager::SelectCondition c1 = { user_manager::User::COMPANY_NAME, anyvalue::comparison_type_e::EQ, "Yoyodyne Inc." };
    user_manager::UserManager::SelectCondition c2 = { user_manager::User::GENDER, anyvalue::comparison_type_e::EQ, int( user_manager::gender_e::MALE ) };

    std::vector<user_manager::UserManager::SelectCondition> conditions = { c1, c2 };

    auto res = m.select_users__unlocked( false, conditions );

    dump_selection( res, "users" );

    log_test( "test_4_multi_select_ok_1", res.size() == 2, true, "users were found", "users were not found", error_msg );
}

void test_4_select_nok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    init_user_1( & m, id, & error_msg );

    create_user_2( & m, & id, & error_msg );
    init_user_2( & m, id, & error_msg );

    create_user_3( & m, & id, & error_msg );
    init_user_3( & m, id, & error_msg );

    auto res = m.select_users__unlocked( user_manager::User::COMPANY_NAME, anyvalue::comparison_type_e::NEQ, "Yoyodyne Inc." );

    dump_selection( res, "users" );

    log_test( "test_4_select_nok_1", res.size() == 0, true, "users were not found", "users were unexpectedly found", error_msg );
}

void test_5_save_ok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    user_manager::user_id_t id;

    create_user_1( & m, & id, & error_msg );
    init_user_1( & m, id, & error_msg );

    create_user_2( & m, & id, & error_msg );
    init_user_2( & m, id, & error_msg );

    auto b = m.save( & error_msg, "test.dat" );

    log_test( "test_5_save_ok_1", b, true, "user file was written", "cannot write file", error_msg );
}

void test_5_save_ok_2()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    auto b = m.save( & error_msg, "test_empty.dat" );

    log_test( "test_5_save_ok_2", b, true, "user file was written", "cannot write file", error_msg );
}

void test_6_load_ok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;
    auto b = false;

    try
    {
        m.init( "test.dat" );

        b = true;
    }
    catch( std::exception & e )
    {
        error_msg = e.what();
    }

    log_test( "test_6_load_ok_1", b, true, "user file was loaded", "cannot load file", error_msg );
}

void test_6_load_ok_2()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    auto b = false;

    try
    {
        m.init( "test_empty.dat" );

        b = true;
    }
    catch( std::exception & e )
    {
        error_msg = e.what();
    }

    log_test( "test_6_load_ok_2", b, true, "user file was loaded", "cannot load file", error_msg );
}

void test_6_load_nok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    auto b = false;

    try
    {
        m.init( "test_missing.dat" );

        b = true;
    }
    catch( std::exception & e )
    {
        error_msg = e.what();
    }

    log_test( "test_6_load_nok_1", b, false, "non-existing user file was not loaded", "non-existing user file was unexpectedly loaded", error_msg );
}

void test_7_load_add_save_ok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    auto b = false;

    try
    {
        m.init( "test.dat" );

        b = true;
    }
    catch( std::exception & e )
    {
        error_msg = e.what();
    }

    log_test( "test_7_load_add_save_ok_1: 1", b, true, "user file was loaded", "cannot load file", error_msg );

    user_manager::user_id_t id;

    create_user_3( & m, & id, & error_msg );
    init_user_3( & m, id, & error_msg );

    b = m.save( & error_msg, "test_new.dat" );

    log_test( "test_7_load_add_save_ok_1: 2", b, true, "user file was written", "cannot write file", error_msg );
}

void test_8_load_add_nok_1()
{
    user_manager::UserManager m;

    m.init();

    std::string error_msg;

    auto b = false;

    try
    {
        m.init( "test.dat" );

        b = true;
    }
    catch( std::exception & e )
    {
        error_msg = e.what();
    }

    log_test( "test_8_load_add_nok_1: 1", b, true, "user file was loaded", "cannot load file", error_msg );

    user_manager::user_id_t id;

    b = create_user_1( & m, & id, & error_msg );

    log_test( "test_8_load_add_nok_1: 2", b, false, "user with duplicate login cannot be added", "unexpectedly added a user with duplicate login", error_msg );
}

int main( int argc, const char* argv[] )
{
    user_manager::UserManager m;

    test_1_add_ok_1();
    test_1_add_nok_1();
    test_2_delete_ok_1();
    test_2_delete_ok_2();
    test_2_delete_nok_1();
    test_3_find_ok_1();
    test_3_find_ok_2();
    test_3_find_ok_3();
    test_3_find_nok_1();
    test_3_find_nok_2();
    test_3_find_nok_3();
    test_4_select_ok_1();
    test_4_select_ok_2();
    test_4_select_ok_3();
    test_4_select_nok_1();
    test_4_multi_select_ok_1();
    test_5_save_ok_1();
    test_5_save_ok_2();
    test_6_load_ok_1();
    test_6_load_ok_2();
    test_6_load_nok_1();
    test_7_load_add_save_ok_1();
    test_8_load_add_nok_1();

    return 0;
}
