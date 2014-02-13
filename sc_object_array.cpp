/*!
 * @file sc_object_array.cpp
 * @author Christian Amstutz
 * @date Feb 13, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_object_array.hpp"

//******************************************************************************
template<typename object_type, unsigned int object_count>
sc_object_array<object_type, object_count>::sc_object_array() :
        name_string("") {

    for(auto& object : objects) {
        object = new object_type();
    }

    return;
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
sc_object_array<object_type, object_count>::sc_object_array(const char* name) :
        name_string(name) {

    unsigned int idx = index_start;
    for(auto& object : objects) {
        std::string full_name = name + std::to_string(idx);
        object = new object_type(full_name.c_str());
        ++idx;
    }

    return;
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
const char* sc_object_array<object_type, object_count>::name() const {

    return(name_string);
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
typename sc_object_array<object_type, object_count>::object_array_t::size_type
        sc_object_array<object_type, object_count>::size() const {

    return(objects.size());
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
object_type* sc_object_array<object_type, object_count>::operator[](
        unsigned int pos) {

    return(objects[pos]);
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
object_type** sc_object_array<object_type, object_count>::begin() {

    return(objects.size()>0 ? objects.begin() : nullptr);
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
object_type* const* sc_object_array<object_type, object_count>::begin() const {

    return(objects.size()>0 ? objects.begin() : nullptr);
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
object_type** sc_object_array<object_type, object_count>::end() {

    return(objects.size()>0 ? objects.end() : nullptr);
}

//******************************************************************************
template<typename object_type, unsigned int object_count>
object_type* const* sc_object_array<object_type, object_count>::end() const {

    return(objects.size()>0 ? objects.end() : nullptr);
}
