/*!
 * @file sc_module_array.cpp
 * @author Christian Amstutz
 * @date Feb 13, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_module_array.hpp"

//******************************************************************************
template<typename module_type, std::size_t module_count>
sc_module_array<module_type, module_count>::sc_module_array()
{
    return;
}

//******************************************************************************
template<typename module_type, std::size_t module_count>
sc_module_array<module_type, module_count>::sc_module_array(const char* name) :
        sc_object_array<module_type, module_count>(name)
{
    return;
}
