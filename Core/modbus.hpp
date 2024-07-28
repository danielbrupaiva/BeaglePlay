//
// Created by daniel on 7/24/24.
//
// References
// https://libmodbus.org/
// https://github.com/stephane/libmodbus
// https://www.fernhillsoftware.com/help/drivers/modbus/modbus-protocol.html
// https://github.com/fz-lyu/modbuspp/tree/master


/*-------------------------------------------------------------------------------------------------------------------------------*/
// Data Type            Access      Code        Method                          Description
// Discrete Input       Read-only   0x02 (02)   modbus_read_input_bits    	    Read Physical Discrete Inputs.
// Coil	                Read-write  0x01 (01)   modbus_read_coils               Read Internal Bits or Physical Coils
//                                  0x05 (05)   modbus_write_coil               Write Internal Bits or Physical Coils
//                                  0x0F (15)   modbus_write_coils              Write Multiple Internal Bits or Physical Coils
/*-------------------------------------------------------------------------------------------------------------------------------*/
// Input Register       Read-only   0x04 (04)   modbus_read_input_registers     Read Physical Input Registers 16-bit
// Holding Register     Read-write  0x03 (03)   modbus_read_holding_registers  	Read Multiple Holding 16-bit registers
//                                  0x06 (06)   modbus_write_register           Write Single Holding 16-bit registers
//                                  0x10 (16)   modbus_write_registers          Write Multiple Holding 16-bit registers
/*-------------------------------------------------------------------------------------------------------------------------------*/

#ifndef MODBUS_HPP
#define MODBUS_HPP

#include <iostream>
#include "logger.hpp"
#include "modbus/modbus.h"

namespace PLC
{
class Modbus
{
public:
    enum class ContextType { TCP };
    struct Data{
        enum class Type { COIL, DISCRETE_INPUT, INPUT_REGISTER, HOLDING_REGISTER };
        Type        type;
        uint16_t    address;
        uint16_t    value;
    };
private:
    const std::string               m_TAG                   = "PLC";
    modbus_t *                      m_context               = nullptr;
    std::string                     m_server_ip             = "127.0.0.1";
    int32_t                         m_server_port           = 502;
    uint8_t                         m_is_connected          = false;
    std::map<std::string, Data>     m_variables             = {};

public:
    ~Modbus()
    {
        if(m_context)
        {
            // disconnect to plc and free resources
            disconnect(m_context);
            modbus_free(m_context);
        }
        logger.debug(m_TAG, "Modbus destroyed");
    }
    explicit Modbus( const std::string& TAG )
        : m_TAG{TAG}
    {
        logger.debug(TAG, "Modbus constructed");
        create_context(ContextType::TCP, m_server_ip, m_server_port);
        connect(m_context, m_server_ip, m_server_port);
    }

    explicit Modbus( const std::string& TAG, const std::string_view ip, const int32_t port)
        : m_TAG{TAG}, m_server_ip{ip}, m_server_port{port}
    {
        logger.debug(TAG, "Modbus constructed");
        create_context(ContextType::TCP, m_server_ip, m_server_port);
        connect(m_context, m_server_ip, m_server_port);
    }

    explicit Modbus( const std::string& TAG, const std::string_view ip, const int32_t port, const std::map<std::string, Data>& variables )
        : m_TAG{TAG}, m_server_ip{ip}, m_server_port{port}, m_variables{variables}
    {
        logger.debug(TAG, "Modbus constructed");
        create_context(ContextType::TCP, m_server_ip, m_server_port);
        connect(m_context, m_server_ip, m_server_port);
    }

public:

    void create_context(ContextType context_type, const std::string& ip, const int32_t port)
    {
        if( context_type == ContextType::TCP )
        {
            m_context = modbus_new_tcp(ip.c_str(), port);
            if(m_context == nullptr)
            {
                std::string msg = "Fail to create modbus context";
                logger.error(m_TAG, msg);
                throw std::runtime_error(m_TAG + ": " + msg);
            }
            logger.debug(m_TAG, "Modbus context created");
        }
        else
        {
            std::string msg = "Unsupported context type";
            logger.error(m_TAG, msg);
            throw std::invalid_argument(m_TAG + ": " + msg);
        }
    }

    int32_t connect(modbus_t* context, const std::string& ip, const int32_t port)
    {
        int rc = -1;
        if( context ) { rc = modbus_connect( context ); }

        if( rc == -1 )
        {
            std::string msg = "Fail to connect to server";
            logger.error(m_TAG, msg);
            logger.error(m_TAG, modbus_strerror(errno));
            throw std::runtime_error(modbus_strerror(errno));
        }
        m_is_connected = true;
        logger.debug(m_TAG, "Modbus connection established with server: " + ip + ":" + std::to_string(port));
        return rc;
    }
    // Disconnect to plc context ONLY.
    void disconnect(modbus_t* context)
    {
        if(context)
        {
            modbus_close(context);
        }
        m_is_connected = false;
        logger.debug(m_TAG, "Modbus connection closed");
    }

    int32_t read_plc_variables( std::map<std::string, PLC::Modbus::Data>& data )
    {
        int32_t rc = -1;
        if(m_context == nullptr)
        {
            std::string msg = "Invalid modbus context";
            logger.error(m_TAG, msg);
            throw std::runtime_error(m_TAG + ": " + msg);
        }
        if( NOT(m_is_connected) )
        {
            std::string msg = "PLC not connected";
            logger.error(m_TAG, msg);
            throw std::runtime_error(m_TAG + ": " + msg);
        }

        std::string msg;
        std::for_each(data.begin(), data.end(), [&](std::pair<const std::string, Data>& data){
            switch (data.second.type)
            {
                case Data::Type::COIL :
                {
                    rc = modbus_read_bits(m_context, data.second.address, 1, reinterpret_cast<uint8_t *>(&data.second.value));
                    msg = "Success read modbus Data::Type::COIL value: " + std::to_string(data.second.value);
                    logger.debug(m_TAG, msg);
                    break;
                }
                case Data::Type::DISCRETE_INPUT :
                {
                    rc = modbus_read_input_bits(m_context, data.second.address, 1, reinterpret_cast<uint8_t *>(&data.second.value));
                    msg = "Success read modbus Data::Type::DISCRETE_INPUT value: " + std::to_string(data.second.value);
                    logger.debug(m_TAG, msg);
                    break;
                }
                case Data::Type::HOLDING_REGISTER :
                {
                    rc = modbus_read_registers(m_context, data.second.address, 1, &data.second.value);
                    msg = "Success read modbus Data::Type::HOLDING_REGISTER value: "+ std::to_string(data.second.value);
                    logger.debug(m_TAG, msg);
                    break;
                }
                case Data::Type::INPUT_REGISTER :
                {
                    rc = modbus_read_input_registers(m_context, data.second.address, 1, &data.second.value);
                    msg = "Success read modbus Data::Type::INPUT_REGISTER value: "+ std::to_string(data.second.value);
                    logger.debug(m_TAG, msg);
                    break;
                }
                default:
                    throw std::invalid_argument("Data type not supported");
            }
        });

        if(rc == -1)
        {
            msg = "Modbus error during" + msg;
            logger.error(m_TAG, msg);
            logger.error(m_TAG, modbus_strerror(errno));
            throw std::runtime_error(modbus_strerror(errno));
        }
        return rc;
    }

public:
    int32_t read_bits(int addr, int nb, uint8_t * buffer)
    {
        int rc = -1;
        if(m_is_connected)
        {
            rc = modbus_read_bits(m_context, addr, nb, buffer);
            if(rc == -1)
            {
                auto msg = "Modbus error during coil(s) read";
                logger.error(m_TAG, msg);
                throw std::runtime_error(m_TAG + ": " + msg);
            }
        }
        logger.debug(m_TAG, "Success coil(s) read");
        return rc;
    }

    int32_t write_bits(const int addr, const int nb, const uint8_t * data )
    {
        int32_t rc = -1;
        if(m_is_connected)
        {
            rc = modbus_write_bits(m_context, addr, nb, data);
            if(rc == -1)
            {
                auto msg = "Modbus error during coil(s) write";
                logger.error(m_TAG, msg);
                throw std::runtime_error(m_TAG + ": " + msg);
            }
        }
        logger.debug(m_TAG, "Success coil(s) write");
        return rc;
    }

    int32_t write_registers(const int addr, const int nb, const uint16_t * data)
    {
        int32_t rc = -1;
        if(m_is_connected)
        {
            rc = modbus_write_registers(m_context, addr, nb, data);
            if(rc == -1)
            {
                auto msg = "Modbus error during register(s) write";
                logger.error(m_TAG, msg);
                throw std::runtime_error(msg);
            }
        }
        logger.debug(m_TAG, "Success register(s) write");
        return rc;
    }
};
}; // namespace Modbus

#endif //MODBUS_HPP
