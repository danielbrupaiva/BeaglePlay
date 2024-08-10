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
class ConnectionPool
{
    const std::string                   m_TAG = "ConnectionPool";
    std::mutex                          m_mutex;
    std::condition_variable             m_condition;
    std::queue<std::shared_ptr<T>>      m_connections;
    uint32_t                            m_pool_size;
    std::string                         m_server_ip;
    int32_t                             m_server_port;

public:
    ~ConnectionPool(){};
    explicit ConnectionPool(const std::string_view server_ip, const int32_t server_port, const uint32_t pool_size)
        : m_server_port{server_port}, m_server_ip{server_ip}, m_pool_size{pool_size}
    {
        logger.debug(m_TAG, "Connection Pool()");
        init_connection_pool(m_pool_size);
    }

    void init_connection_pool(const uint32_t pool_size) {
        for(size_t index = 0; index < pool_size; index++){
            auto connection = std::make_shared<T>(ContextType::TCP, m_server_ip, m_server_port);
            if(connection){
                m_connections.push(connection);
            }
            else{
                std::string msg = "Fail to create connection pool";
                logger.error(m_TAG, msg);
                logger.error(m_TAG, modbus_strerror(errno));
                throw std::runtime_error(modbus_strerror(errno));
            }
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