/*!
 * @file sc_map_list.hpp
 * @author Christian Amstutz
 * @date June 8, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../sc_map_base.hpp"
#include "sc_map_list_key_range.hpp"

#include <systemc.h>

#include <vector>
#include <string>
#include <sstream>

//******************************************************************************
template <typename value_T, typename object_T>
class sc_map_list : public sc_map_base<sc_map_list_key_range<value_T>, object_T>
{
public:
    typedef sc_map_base<sc_map_list_key_range<value_T>, object_T> base;
    typedef value_T value_type;

    sc_map_list(std::vector<value_type>& key_vector, const sc_module_name name);
    template <typename config_T>
    sc_map_list(std::vector<value_type>& key_vector, const sc_module_name name, const config_T configuration);
    virtual ~sc_map_list() {};
};

//******************************************************************************

//******************************************************************************
template <typename value_T, typename object_T>
sc_map_list<value_T, object_T>::sc_map_list(std::vector<value_type>& key_vector,
        const sc_module_name name) :
        sc_map_base<typename base::range_type, object_T>(name)
{
    std::vector<typename base::key_type> keys;

    for (typename std::vector<value_type>::iterator value_it = key_vector.begin();
         value_it != key_vector.end();
         ++value_it)
    {
        typename base::key_type new_key = typename base::key_type(*value_it);
        keys.push_back(new_key);
    }

    base::range = keys;
    this->init(keys, typename base::creator());

    return;
}

//******************************************************************************
template <typename value_T, typename object_T>
template <typename config_T>
sc_map_list<value_T, object_T>::sc_map_list(std::vector<value_type>& key_vector,
        const sc_module_name name, const config_T configuration) :
        sc_map_base<typename base::range_type, object_T>(name)
{
    std::vector<typename base::key_type> keys;

    for (typename std::vector<value_type>::iterator value_it = key_vector.begin();
         value_it != key_vector.end();
         ++value_it)
    {
        keys.push_back(typename base::key_type(*value_it));
    }

    base::range = keys;
    this->init(base::range.get_key_vector(), typename base::creator(), configuration);

    return;
}
