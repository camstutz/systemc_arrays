/*!
 * @file sc_object_array.hpp
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
#include <array>
#include <string>

#include <systemc.h>

template<typename object_type, std::size_t object_count>
class sc_object_array
{
public:
    typedef std::array<object_type*, object_count> object_array_t;

    static const unsigned int index_start = 0;

    sc_object_array();
    sc_object_array(const char* name);

    const char* name() const;

    typename object_array_t::size_type size() const;
    object_type* operator[](std::size_t pos);
    object_type** begin();
    object_type* const * begin() const;
    object_type** end();
    object_type* const * end() const;

private:
    object_array_t objects;
    const char* name_string;
};

#include "sc_object_array.cpp"
