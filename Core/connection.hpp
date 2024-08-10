//
// Created by daniel on 8/10/24.
//
#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "utils.hpp"
#include "logger.hpp"
#include "modbus/modbus.h"

enum class ContextType { TCP };

class Connection : public std::enable_shared_from_this< Connection > {
    const std::string           m_TAG = "Connection";
    ContextType                 m_context_type = ContextType::TCP;
    modbus_t *                  m_context = nullptr;
    std::string                 m_server_ip = "127.0.0.1";
    int32_t                     m_server_port = 502;
    bool                        m_is_connected = false;
    std::mutex                  m_mutex;
    std::condition_variable     m_condition;

public:
    ~Connection() {
        disconnect();
        modbus_free(m_context);
        logger.debug(m_TAG, "Modbus connection released");
    };

    Connection(const ContextType contextType, const std::string_view ip, const int32_t port)
        : m_context_type{contextType}, m_server_ip{ip}, m_server_port{port}
    {
        m_context = create_context(m_context_type);
        m_is_connected = connect();
        logger.debug(m_TAG, "Modbus connection created");
    };

    std::shared_ptr< Connection > get() { return this->shared_from_this(); };

    bool connect() {
        if(m_context) { return connect(m_context); }
        return false;
    }

    void disconnect() {
        if (m_context) { modbus_close(m_context); }
        m_is_connected = false;
    };

    inline bool is_connected() const { return m_is_connected; }

private:
    modbus_t * create_context(ContextType context_type) {
        modbus_t * context = nullptr;
        if (context_type == ContextType::TCP) {
            context = modbus_new_tcp(m_server_ip.c_str(), m_server_port);
            if (context == nullptr) {
                std::string msg = "Fail to create modbus context";
                logger.error(m_TAG, msg);
                throw std::runtime_error(m_TAG + ": " + msg);
            }
            logger.debug(m_TAG, "Modbus context created");
        }
        else {
            std::string msg = "Context type not supported";
            logger.error(m_TAG, msg);
            throw std::invalid_argument(m_TAG + ": " + msg);
        }
        return context;
    };

    bool connect(modbus_t *context) {
        std::lock_guard<std::mutex> lock(m_mutex);
        int rc = -1;
        if( context ) {
            rc = modbus_connect( context );
            if( rc == -1 ) {
                std::string msg = "Fail to connect to server";
                logger.error(m_TAG, msg);
                logger.error(m_TAG, modbus_strerror(errno));
                throw std::runtime_error(modbus_strerror(errno));
            }
        }
        logger.debug(m_TAG, "PLC connected");
        return true;
    };
};