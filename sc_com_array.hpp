/*!
 * @file sc_com_array.hpp
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

#include <string>

#include <systemc.h>

#include "sc_object_array.hpp"

// Forward declarations
template<typename object_type, unsigned int object_count>
class sc_com_array;

template<typename object_type, unsigned int object_count>
void sc_trace(sc_trace_file* tf,
            const sc_com_array<object_type, object_count>& com_objects,
            const std::string& name);

// todo: change to size_type
template<typename object_type, unsigned int object_count>
class sc_com_array : public sc_object_array<object_type, object_count>
{

public:

    sc_com_array();
    sc_com_array(const char* name);

    void make_sensitive(sc_sensitive& sensitive_list) const;
    //todo: void write_all(data_type value);

    friend void sc_trace<>(sc_trace_file* tf,
            const sc_com_array<object_type, object_count>& com_objects,
            const std::string& name);

private:

};

#include "sc_com_array.cpp"
