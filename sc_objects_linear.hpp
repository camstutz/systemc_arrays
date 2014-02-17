/*!
 * @file sc_object_map.hpp
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
#include <sstream>
#include <map>

#include <systemc.h>

#include "sc_objects_map.hpp"

template<typename id_type, typename object_type>
class sc_objects_linear : public sc_objects_map<id_type, object_type>
{
public:
    static const int start_index = 0;

    sc_objects_linear(const unsigned int element_count, const sc_module_name &name = "", const int start_idx = start_index);

    object_type* at(const id_type key);

    sc_objects_array<object_type*> getArray();
    //sc_object_array<object_type*> getArray(const id_type start, const id_type end);

private:
    std::map<int, object_type> sc_objects;
};

#include "sc_objects_linear.cpp"
