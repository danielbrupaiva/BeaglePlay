//
// Created by daniel on 6/11/24.
//

#pragma once

#include "iostream"

class IWindow;
// Interface for graphics api
class IGraphicApi{
public:
    virtual int8_t init() = 0;
    virtual void shutdown() = 0;
    virtual bool is_close() = 0;
    virtual void* get_window() = 0;
};
