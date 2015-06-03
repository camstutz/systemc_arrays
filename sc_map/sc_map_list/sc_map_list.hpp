/*!
 * @file sc_map_list.hpp
 * @author Christian Amstutz
 * @date June 3, 2015
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
    typedef value_T value_type;
    typedef sc_map_list_key<value_type> key_type;
    typedef object_T object_type;
    typedef sc_map_base<sc_map_list_key_range<value_type>, object_type> base;
    typedef sc_map_list_key_range<value_type> range_type;
    typedef typename base::size_type size_type;

    sc_map_list(std::vector<value_type>& key_vector, const sc_module_name name);
    template <typename config_T>
    sc_map_list(std::vector<value_type>& key_vector, const sc_module_name name, const config_T configuration);
    virtual ~sc_map_list() {};

    virtual range_type* get_range();

private:
    range_type range;
};

//******************************************************************************

//******************************************************************************
template <typename value_T, typename object_T>
sc_map_list<value_T, object_T>::sc_map_list(std::vector<value_type>& key_vector,
        const sc_module_name name) :
        sc_map_base<range_type, object_type>(name)
{
    std::vector<key_type> keys;

    for (typename std::vector<value_type>::iterator value_it = key_vector.begin();
         value_it != key_vector.end();
         ++value_it)
    {
        keys.push_back(key_type(*value_it));
    }

    range = keys;
    this->init(keys, typename base::creator());

    return;
}

//******************************************************************************
template <typename value_T, typename object_T>
template <typename config_T>
sc_map_list<value_T, object_T>::sc_map_list(std::vector<value_type>& key_vector,
        const sc_module_name name, const config_T configuration) :
        sc_map_base<range_type, object_type>(name)
{
    std::vector<key_type> keys;

    for (typename std::vector<value_type>::iterator value_it = key_vector.begin();
         value_it != key_vector.end();
         ++value_it)
    {
        keys.push_back(key_type(*value_it));
    }

    range = keys;
    this->init(base::range.get_key_vector(), typename base::creator(), configuration);

    return;
}

//******************************************************************************
template <typename value_T, typename object_T>
typename sc_map_list<value_T, object_T>::range_type*
        sc_map_list<value_T, object_T>::get_range()
{
    sc_map_list_key_range<value_type>* new_range = new sc_map_list_key_range<value_type>(range);

    return new_range;
}
