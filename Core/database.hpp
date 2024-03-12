#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include "pqxx/pqxx"
#include "logger.hpp"
#include "user.hpp"

namespace Core {

class Database : public std::enable_shared_from_this<Database> {
private:
    std::string m_host;
    std::string m_port;
    std::string m_username;
    std::string m_password;
    std::string m_dbname;
    std::string m_connection_string;
    const uint8_t m_connection_pool_size = 5U;
    std::queue< std::shared_ptr<pqxx::connection> > m_connections;
    std::mutex m_mutex;
    std::condition_variable m_condition;

    std::shared_ptr<pqxx::connection> connect();

    std::shared_ptr<pqxx::connection> connect(const std::string_view _connection_string);
    /* init connection pool */
    void init_connection_pool(uint32_t _size);

    void prepare_statements(pqxx::connection& connection)
    {
        /* Create user */
        connection.prepare( "create_user", "INSERT INTO tb_users (username, security_level, \"password\") VALUES($1, $2, $3)");
        /* Read given usernanem*/
        connection.prepare( "read_user", "SELECT * FROM tb_users WHERE username = $1");
        /* Update user*/
        connection.prepare( "update_user", "UPDATE tb_users SET username=$2, security_level=$3, \"password\"=$4 WHERE user_id=(SELECT user_id FROM tb_users WHERE  username = $1)");
        /* Delete user*/
        connection.prepare( "delete_user", "DELETE FROM tb_users WHERE username=$1");
        /* Check user's credentials */
        connection.prepare( "check_password", "SELECT * FROM tb_users WHERE username = $1 AND password = $2");
        /* table_size - Row count at table */
        connection.prepare( "users_size", "SELECT COUNT(*) AS tb_size FROM tb_users");
        /* Read all data at given table */
        connection.prepare( "read_all_users", "SELECT * FROM tb_users");
    };
public:
    ~Database(){/* The destructor of pqxx::connection will close connection automatically.*/};

    explicit Database(const std::string_view _connection_string) : m_connection_string{_connection_string}
    {
        init_connection_pool(m_connection_pool_size);
    }
    explicit Database(
            const std::string_view _host,
            const std::string_view _port,
            const std::string_view _username,
            const std::string_view _password,
            const std::string_view _dbname)
            : m_host{_host}, m_port{_port}, m_username{_username}, m_password{_password}, m_dbname{_dbname}
    {
        set_connection_string("host=" + m_host + " port=" + m_port + " user=" + m_username + " password=" + m_password + " dbname=" + m_dbname);
        init_connection_pool(m_connection_pool_size);
    }

    static std::shared_ptr<Database> create(const std::string_view _connection_string)
    {
        return std::make_shared<Database>(_connection_string);
    };

    static std::shared_ptr<Database> create(const std::string_view _host,
                                            const std::string_view _port,
                                            const std::string_view _username,
                                            const std::string_view _password,
                                            const std::string_view _dbname)
    {
        return std::make_shared<Database>(_host, _port, _username, _password, _dbname);
    };

    std::shared_ptr<Database> get() { return shared_from_this(); };

    /*get connection from the pool*/
    std::shared_ptr< pqxx::connection > get_connection(uint32_t _timeout);
    /*return connection to the pool*/
    void release_connection( std::shared_ptr<pqxx::connection> _conn );

    pqxx::result exec_query(std::string_view _sql_query);

    pqxx::result commit_query(std::string_view _sql_query);

    bool create_user(const std::string_view _username, unsigned int _security_level, const std::string_view _password)
    {
        pqxx::result result;

        try {
            if(_username.empty()){
                throw "Username is empty";
            }

            auto connection = get_connection(100);
            pqxx::work work(*connection);
            if (connection->is_open())
            {
                result = work.exec_prepared("create_user", _username, _security_level, _password );
                work.commit();
            }else
            {
                work.abort();
            }
            release_connection(connection);
            return true;

        } catch (const pqxx::sql_error &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
            // Handle SQL-related errors
        } catch (const std::exception &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            // Handle other exceptions
        } catch(const char* message){
            std::cerr << "ERROR: " << message << std::endl;
        } catch (...) {
            std::cerr << "ERROR: Exception occurred" << std::endl;
        }
        return false;
    };

    pqxx::result read_user(const std::string_view _username)
    {
        pqxx::result result;
        try{

            if(_username.empty()){
                throw "Username is empty";
            }
            auto connection = get_connection(100);
            pqxx::work work(*connection);
            if (connection->is_open())
            {
                result = work.exec_prepared("read_user", _username);
                work.commit();
            }else
            {
                work.abort();
            }
            release_connection(connection);
            return result;

        } catch (const pqxx::sql_error &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
            // Handle SQL-related errors
        } catch (const std::exception &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            // Handle other exceptions
        } catch(const char* message){
            std::cerr << "ERROR: " << message << std::endl;
        } catch (...) {
            std::cerr << "ERROR: Exception occurred" << std::endl;
        }
        return result;
    };

    pqxx::result update_user(const std::string_view _username, const uint8_t _security_level, const std::string_view _password){

        pqxx::result result;
        try{
            auto connection = get_connection(100);
            pqxx::work work(*connection);
            if (connection->is_open())
            {
                result = work.exec_prepared("update_user", _username, _security_level, _password);
                work.commit();
            }else
            {
                work.abort();
            }
            release_connection(connection);
            return result;

        } catch (const pqxx::sql_error &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
            // Handle SQL-related errors
        } catch (const std::exception &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            // Handle other exceptions
        } catch(const char* message){
            std::cerr << "ERROR: " << message << std::endl;
        } catch (...) {
            std::cerr << "ERROR: Exception occurred" << std::endl;
        }
        return result;
    };

    pqxx::result delete_user(const std::string_view _username, Core::User& _system_user)
    {
        pqxx::result result;
        try{
            if(_username.empty()){
                throw "Username is empty";
            }
            auto connection = get_connection(100);
            pqxx::work work(*connection);
            if (connection->is_open())
            {
                result = work.exec_prepared("delete_user", _username);
                work.commit();
            }else
            {
                work.abort();
            }
            release_connection(connection);
            return result;

        } catch (const pqxx::sql_error &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
            // Handle SQL-related errors
        } catch (const std::exception &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            // Handle other exceptions
        } catch(const char* message){
            std::cerr << "ERROR: " << message << std::endl;
        } catch (...) {
            std::cerr << "ERROR: Exception occurred" << std::endl;
        }
        return result;
    };

    //TODO: add encrypt _password ´check
    bool check_password(const std::string_view _username, const std::string_view _password, Core::User& _system_user)
    {
        pqxx::result result;
        try{
            if(_username.empty()) {
                throw "Username is empty";
            }
            auto connection = get_connection(100);
            pqxx::work work(*connection);
            result = work.exec_prepared("check_password", _username, _password);
            work.commit();
            release_connection(connection);
            if( result.empty() )
            {
                _system_user.reset();
                return false;
            }
            else
            {
                pqxx::row row = result[0];
                _system_user.set_user(row["user_id"].as<int>(),
                                      row["username"].as<std::string>(),
                                      row["password"].as<std::string>(),
                                      row["security_level"].as<int>(),
                                      true );
                return true;
            }

        } catch (const pqxx::sql_error &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
            // Handle SQL-related errors
        } catch (const std::exception &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            // Handle other exceptions
        } catch(const char* message){
            std::cerr << "ERROR: " << message << std::endl;
        } catch (...) {
            std::cerr << "ERROR: Exception occurred" << std::endl;
        }
        return false;
    }

    uint32_t tb_users_size()
    {
        pqxx::result result;
        try {

            auto connection = get_connection(100);
            pqxx::work work(*connection);
            result = work.exec_prepared("users_size");
            pqxx::row row{result[0]};
            release_connection(connection);
            return row["tb_size"].as<uint32_t>();

        }catch (const pqxx::sql_error &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
            // Handle SQL-related errors
        } catch (const std::exception &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            // Handle other exceptions
        } catch(const char* message){
            std::cerr << "ERROR: " << message << std::endl;
        } catch (...) {
            std::cerr << "ERROR: Exception occurred" << std::endl;
        }
        return 0U;
    };

    pqxx::result read_all_users()
    {
        pqxx::result result;
        try{
            auto connection = get_connection(100);
            pqxx::work work(*connection);
            if (connection->is_open())
            {
                result = work.exec_prepared("read_all_users");
                work.commit();
            }else
            {
                work.abort();
            }
            release_connection(connection);
            return result;

        } catch (const pqxx::sql_error &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
            // Handle SQL-related errors
        } catch (const std::exception &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            // Handle other exceptions
        } catch(const char* message){
            std::cerr << "ERROR: " << message << std::endl;
        } catch (...) {
            std::cerr << "ERROR: Exception occurred" << std::endl;
        }
        return result;
    };

    void reset_database()
    {
        std::string initial_setup_query =
                "CREATE EXTENSION IF NOT EXISTS pgcrypto;\
        DO $$ \
        BEGIN \
        IF EXISTS (SELECT 1 FROM information_schema.tables WHERE table_schema = 'public' AND table_name = 'tb_users') THEN \
        DROP TABLE public.tb_users; \
        END IF;\
        CREATE TABLE IF NOT EXISTS public.tb_users ( \
                                                    user_id SERIAL PRIMARY KEY, \
                                                    username VARCHAR(50) UNIQUE NOT NULL, \
                                                    security_level INT CHECK (security_level IN (0, 1, 2)) NOT NULL, \
                                                    password VARCHAR(100) NOT NULL);\
        INSERT INTO public.tb_users (username, security_level, password) VALUES('admin', 0, '1234');\
        INSERT INTO public.tb_users (username, security_level, password) VALUES('supervisor', 1, '1234');\
        INSERT INTO public.tb_users (username, security_level, password) VALUES('operator_1', 2, '1234');\
        INSERT INTO public.tb_users (username, security_level, password) VALUES('operator_2', 2, '1234');\
        INSERT INTO public.tb_users (username, security_level, password) VALUES('operator_3', 2, '1234');\
        END $$;";
        commit_query(initial_setup_query);
    };
public:
    /** Getters and Setters **/
    inline std::string get_connection_string() const { return m_connection_string; }
    inline void set_connection_string(const std::string_view newConnection_string) { m_connection_string = newConnection_string; }

    inline std::string get_host() const{ return m_host; }
    inline void set_host(const std::string_view newHost){ m_host = newHost; }

    inline std::string get_port() const{ return m_port; }
    inline void set_port(const std::string_view newPort){ m_port = newPort; }

    inline std::string get_username() const{ return m_username; }
    inline void set_username(const std::string_view newUsername){ m_username = newUsername; }

    inline std::string get_password() const { return m_password; }
    inline void set_password(const std::string_view newPassword) { m_password = newPassword; }

    inline std::string get_dbname() const { return m_dbname; }
    inline void set_dbname(const std::string_view newDbname){ m_dbname = newDbname; }

    inline uint8_t get_connection_pool_size() const { return m_connection_pool_size; }
};

};//namespace Core