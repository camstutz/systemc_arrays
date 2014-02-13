/*!
 * @file sc_com_array.cpp
 * @author Christian Amstutz
 * @date Feb 13, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_com_array.hpp"

//******************************************************************************
template<typename object_type, unsigned int object_count>
sc_com_array<object_type, object_count>::sc_com_array() {

    return;
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
sc_com_array<object_type, object_count>::sc_com_array(const char* name) :
        sc_object_array<object_type, object_count>(name) {

    return;
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
void sc_com_array<object_type, object_count>::make_sensitive(
        sc_sensitive& sensitive_list) const {

    // todo: change it to a traditional way of sensitivity lists
    // todo: make it possible to react on other than pos
    for (auto com_object : *this) {
        sensitive_list << com_object->pos();
    }

    return;
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
void sc_trace(sc_trace_file* tf,
        const sc_com_array<object_type, object_count>& com_objects,
        const std::string& name)
{
    unsigned int idx = com_objects.index_start;
    for (auto com_object : com_objects) {
        sc_trace(tf, *com_object, name + std::to_string(idx));
        ++idx;
    }
}
