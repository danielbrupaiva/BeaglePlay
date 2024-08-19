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

#pragma once

#include <iostream>
#include <map>
#include "logger.hpp"
#include "utils.hpp"
#include "modbus/modbus.h"
#include "connection.hpp"
#include "connection_pool.hpp"

namespace Core {
namespace PLC {

class Modbus : public ConnectionPool<Connection>
{
private:
    const std::string   m_TAG   =   "PLC";
public:
    ~Modbus() {
        logger.debug(m_TAG, "Modbus destroyed");
    }

    explicit Modbus(const std::string &TAG,const std::string_view ip, const int32_t port, uint32_t pool_size)
        : m_TAG{TAG}, ConnectionPool<Connection>(ip, port, pool_size)
        {
            logger.debug(TAG, "Modbus constructed");
        }

    int32_t read_plc_variable( Data& data ) {
        //get connection from the pool
        auto connection = get_connection(100);
        connection->read_plc_variable(data);
        // return connection to the pool
        release_connection(connection);
    }
    int32_t read_plc_variables( std::map<std::string, Data> &data ) {
        //get connection from the pool
        auto connection = get_connection(100);
        connection->read_plc_variables(data);
        // return connection to the pool
        release_connection(connection);
    }

    void write_plc_variable( Data& data ) {
        //get connection from the pool
        auto connection = get_connection(100);

        // return connection to the pool
        release_connection(connection);
    }
};
}; // namespace Modbus
}; // namespace Core