/*!
 * @file sc_objects_linear.cpp
 * @author Christian Amstutz
 * @date Feb 17, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_objects_linear.hpp"

//******************************************************************************
template<typename id_type, typename object_type>
sc_objects_linear<id_type, object_type>::sc_objects_linear(
        const unsigned int element_count, const sc_module_name &name,
        const int start_idx) {

    this->name = name;

    for (int idx = start_idx; idx<element_count; ++idx) {
        std::ostringstream object_name;
        object_name << name << std::to_string(idx);
        sc_objects.emplace(std::piecewise_construct, std::forward_as_tuple(idx),
                std::forward_as_tuple(object_name.str().c_str()));
    }

    return;
}

//******************************************************************************
template<typename id_type, typename object_type>
object_type* sc_objects_linear<id_type, object_type>::at(const id_type key) {

    return(&sc_objects[key]);
}
