/*!
 * @file sc_objects_map.hpp
 * @author Christian Amstutz
 * @date Feb 17, 2014
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

template<typename id_type, typename object_type>
class sc_objects_map
{
public:
    //sc_objects_map();
    //sc_objects_map(const char* name);

protected:
    std::string name;

};

#include "sc_objects_map.cpp"
