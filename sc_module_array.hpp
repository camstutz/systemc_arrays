/*!
 * @file sc_module_array.hpp
 * @author Christian Amstutz
 * @date Feb 13, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <cstddef>
#include <string>

#include <systemc.h>

#include "sc_object_array.hpp"

template<typename module_type, std::size_t module_count>
class sc_module_array : public sc_object_array<module_type, module_count>
{

public:
    sc_module_array();
    sc_module_array(const char* name);

private:

};

#include "sc_module_array.cpp"
