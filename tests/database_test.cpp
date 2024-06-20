#include <catch2/catch_test_macros.hpp>
#include "database.hpp"

TEST_CASE("Test1") {

}
TEST_CASE( "Database class tests" ) {

    //Create database
    auto db = Core::Database::create("localhost", "5432", "imgui", "1234", "project");
    SECTION( "Create database" ) {
        REQUIRE( nullptr != db );
    }
    //Connect to the database
    SECTION( "Getting connection from the pool" ) {

        auto connection = db->get_connection(0);
        REQUIRE( true == connection->is_open() );
        db->release_connection(connection);

    }
    //Execute non-transaction queries
    //Execute transaction queries

    //CRUD
    //Create a new user
    //Update a current user
    //Delete a selected user
    //Verify user password
}




