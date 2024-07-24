//
// Created by daniel on 7/24/24.
//

#ifndef MODBUS_HPP
#define MODBUS_HPP

#include <iostream>
#include "logger.hpp"
#include "modbus/modbus.h"

class Modbus
{
    const std::string    TAG                     = "MODBUS";
    modbus_t *           m_context               = nullptr;
    std::string          m_server_ip             = "127.0.0.1";
    int32_t              m_server_port           = 502;
    uint8_t              m_is_server_connected   = false;

public:
    ~Modbus()
    {
        if(m_context)
        {
            modbus_close(m_context);
            modbus_free(m_context);
        }
        m_is_server_connected = false;
        logger.debug("Modbus connection closed");
    }
    explicit Modbus( const std::string_view ip, const int32_t port )
        : m_server_ip{ip}, m_server_port{port}
    {
        logger.debug("Modbus constructed");

        m_context = modbus_new_tcp(m_server_ip.c_str(), m_server_port);
        logger.debug("Modbus context created");

        if( modbus_connect(m_context) == -1 )
        {
            std::string msg = "Fail to connect to server";
            logger.error(TAG, msg);
            throw std::runtime_error(TAG + ": " + msg);
        }
        logger.debug("Modbus connection established with server: " + m_server_ip + ":" + std::to_string(m_server_port));
        m_is_server_connected = true;
    }

    int32_t read_bits(int addr, int nb, uint8_t * buffer)
    {
        int rc = -1;
        if(m_is_server_connected)
        {
            rc = modbus_read_bits(m_context, addr, nb, buffer); // modbus_read_bits(modbus_t *ctx, int addr, int nb, uint8_t *dest);
            if(rc == -1)
            {
                auto msg = "Modbus error during coil(s) read";
                logger.error(TAG, msg);
                throw std::runtime_error(TAG + ": " + msg);
            }
        }
        logger.debug(TAG, "Success coil(s) read");
        return rc;
    }

    int32_t write_bits(const int addr, const int nb, const uint8_t * data )
    {
        int32_t rc = -1;
        if(m_is_server_connected)
        {
            rc = modbus_write_bits(m_context, addr, nb, data);
            if(rc == -1)
            {
                auto msg = "Modbus error during coil(s) write";
                logger.error(TAG, msg);
                throw std::runtime_error(TAG + ": " + msg);
            }
        }
        logger.debug(TAG, "Success coil(s) write");
        return rc;
    }

    int32_t write_registers(const int addr, const int nb, const uint16_t * data)
    {
        int32_t rc = -1;
        if(m_is_server_connected)
        {
            rc = modbus_write_registers(m_context, addr, nb, data);
            if(rc == -1)
            {
                auto msg = "Modbus error during register(s) write";
                logger.error(TAG, msg);
                throw std::runtime_error(msg);
            }
        }
        logger.debug(TAG, "Success register(s) write");
        return rc;
    }
};

#endif //MODBUS_HPP
