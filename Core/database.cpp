#include "database.hpp"

/* init connection pool */
void Core::Database::init_connection_pool(uint32_t _size)
{

    for (uint32_t index = 0; index < _size; ++index)
    {
        auto conn = connect(get_connection_string());
        if (conn->is_open())
        {
            prepare_statements(*conn);
            m_connections.push(conn);
        }
        else{
            throw std::runtime_error("ERROR: Not possible to connect to database");
        }
    }
};

/*get connection from the pool*/
std::shared_ptr< pqxx::connection > Core::Database::get_connection(const uint32_t _timeout)
{
    std::chrono::milliseconds timeout{_timeout};
    /*lock thread*/
    std::unique_lock<std::mutex> lock(m_mutex);
    /*check if there is connection avaiable in the container*/
    if ( m_connections.empty() )
    {
        /* ConnectionPool is empty, wait for a connection to be returned or until the _timeout */
        /* wait until connection is avaiable */
        if (m_condition.wait_for(lock, timeout, [this] { return !m_connections.empty(); }))
        { /*get connection from pool*/
            auto conn = std::move( m_connections.front() );
            m_connections.pop();
            return conn;
        }else
        {
            throw std::runtime_error("Connection pool timeout");
        }
    }
    auto conn = std::move( m_connections.front() );
    m_connections.pop();
    return conn;
};

void Core::Database::release_connection( std::shared_ptr<pqxx::connection> _conn )
{
    /*lock thread*/
    std::lock_guard<std::mutex> lock(m_mutex);
    /*return the connection to the pool*/
    m_connections.push(_conn);
    /*notify*/
    m_condition.notify_one();
};

std::shared_ptr<pqxx::connection> Core::Database::connect()
{
    try
    {
        auto connection = std::make_shared<pqxx::connection>(m_connection_string);
        if (connection->is_open())
        {
            return connection;
        }
    }
    catch (const pqxx::sql_error& e)
    {
        std::cerr << "SQL error: " << e.what() << std::endl;
        std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
        // Handle SQL-related errors
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        // Handle other exceptions
    }
    catch (const char* message)
    {
        std::cerr << "ERROR: " << message << std::endl;
    }
    catch (...)
    {
        std::cerr << "ERROR: Exception occurred" << std::endl;
    }
    return nullptr;
};

std::shared_ptr<pqxx::connection> Core::Database::connect(const std::string_view _connection_string)
{
    set_connection_string(_connection_string);
    return connect();
};

pqxx::result Core::Database::exec_query(std::string_view _sql_query)
{
    pqxx::result result;
    try
    {
        auto connection = get_connection(100);
        pqxx::work work(*connection);
        if (connection->is_open())
        {
            result = work.exec(_sql_query);
        }
        release_connection(connection);
        return result;
    }
    catch (const pqxx::sql_error& e)
    {
        std::cerr << "SQL error: " << e.what() << std::endl;
        std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
        // Handle SQL-related errors
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        // Handle other exceptions
    }
    catch (const char* message)
    {
        std::cerr << "ERROR: " << message << std::endl;
    }
    catch (...)
    {
        std::cerr << "ERROR: Exception occurred" << std::endl;
    }
    return result;
};

pqxx::result Core::Database::commit_query(std::string_view _sql_query)
{
    pqxx::result result;
    try
    {
        auto connection = get_connection(100);
        pqxx::work work(*connection);
        if (connection->is_open())
        {
            result = work.exec(_sql_query);
            work.commit();
        }else
        {
            work.abort();
        }
        release_connection(connection);
        return result;
    }
    catch (const pqxx::sql_error& e)
    {
        std::cerr << "SQL error: " << e.what() << std::endl;
        std::cerr << "Query: " << e.query() << std::endl; // Retrieve the query causing the error
        // Handle SQL-related errors
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        // Handle other exceptions
    }
    catch (const char* message)
    {
        std::cerr << "ERROR: " << message << std::endl;
    }
    catch (...)
    {
        std::cerr << "ERROR: Exception occurred" << std::endl;
    }
    return result;
};

