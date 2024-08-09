//
// Created by daniel on 8/1/24.
//

#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <chrono>

#include "utils.hpp"
#include "logger.hpp"

namespace Core {

template <typename T>
class ConnectionPool : public std::enable_shared_from_this< ConnectionPool<T> >
{
    const std::string                   m_TAG = "ConnectionPool";
    std::mutex                          m_mutex;
    std::condition_variable             m_condition;
    std::queue<std::shared_ptr<T>>      m_connections;
    uint32_t                            m_pool_size = 5U;

public:
    ~ConnectionPool(){};
    explicit ConnectionPool(uint32_t pool_size)
        : m_pool_size{pool_size}
    {
        logger.debug(m_TAG, "Connection Pool()");
    };

    std::shared_ptr< ConnectionPool<T> > get() { return this->shared_from_this(); };

    /* init connection pool */
    void init_connection_pool() {
        logger.debug(m_TAG, "init connection pool");
        for ( uint32_t index = 0; index < get_pool_size(); index++ ) {
        }
    };

    /*get connection from the pool*/
    std::shared_ptr<T> get_connection(uint32_t timeout) {
        /*lock thread*/
        std::unique_lock<std::mutex> lock(m_mutex);

        std::shared_ptr<T> connection = nullptr;
        if(NOT(m_connections.empty())){
            connection = m_connections.front();
            m_connections.pop();
            return connection;
        }
        else{
            if( m_condition.wait_for(lock, std::chrono::milliseconds(timeout),[&](){ return m_connections.empty(); })){
                std::string msg = "Connection pool timeout exceed";
                logger.error(m_TAG, msg);
                throw std::runtime_error(msg);
            }
            else{
                connection = m_connections.front();
                m_connections.pop();
            }
        }
        return connection;
    };

    void release_connection(std::shared_ptr<T>&& connection) {
        /*lock thread*/
        std::unique_lock<std::mutex> lock(m_mutex);
        /*return the connection to the pool*/
        m_connections.push(connection);
        /*notify*/
        m_condition.notify_one();
    };

public:
    [[nodiscard]] inline uint32_t get_pool_size() const { return m_pool_size; }
};

};//namespace Core