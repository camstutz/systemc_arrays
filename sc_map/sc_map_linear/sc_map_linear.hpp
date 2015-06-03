/*!
 * @file sc_map_linear.hpp
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
#include "sc_map_linear_key.hpp"
#include "sc_map_linear_key_range.hpp"

#include <systemc.h>

#include <string>
#include <sstream>

//******************************************************************************

template <typename object_type>
class sc_map_linear : public sc_map_base<sc_map_linear_key_range, object_type>
{
public:
    typedef sc_map_base<sc_map_linear_key_range, object_type> base;
    typedef sc_map_linear_key key_type;
    typedef sc_map_linear_key_range range_type;
    typedef key_type::index_type index_type;
    typedef typename base::size_type size_type;

    virtual sc_map_linear_key_range* get_range();

    sc_map_linear(const size_type element_cnt_X, const sc_module_name name, const index_type start_id_X = sc_map_linear_key::default_start_id);
    template <typename config_type>
    sc_map_linear(const size_type element_cnt_X, const sc_module_name name, const config_type configuration, const index_type start_id_X = sc_map_linear_key::default_start_id);
    virtual ~sc_map_linear() {};

private:
    range_type range;
};

//******************************************************************************

//******************************************************************************
template <typename object_type>
sc_map_linear_key_range* sc_map_linear<object_type>::get_range()
{
    sc_map_linear_key_range* new_range = new sc_map_linear_key_range(range);

    return new_range;
}

//******************************************************************************
template <typename object_type>
sc_map_linear<object_type>::sc_map_linear(const size_type element_cnt_X,
        const sc_module_name name, const index_type start_id_X) :
        sc_map_base<range_type, object_type>(name),
        range(sc_map_linear_key(start_id_X),
        sc_map_linear_key(start_id_X+element_cnt_X-1))
{
    std::vector<key_type> range_keys = range.get_key_vector();

    this->init(range_keys, typename base::creator());

//   sc_map_linear<sc_core::sc_out<bool> >::init(std::vector<sc_map_linear_key>&,          sc_map_base<sc_map_linear_key_range, sc_core::sc_out<bool> >::creator)’
//   sc_map_base<range_T, object_T>       ::init(std::vector<typename range_T::key_type>&, sc_map_base<sc_map_linear_key_range, sc_core::sc_out<bool> >::creator&)                [with Creator = sc_map_base<sc_map_linear_key_range, sc_core::sc_out<bool> >::creator; range_T = sc_map_linear_key_range; object_T = sc_core::sc_out<bool>; typename range_T::key_type = sc_map_linear_key]


    return;
}

//******************************************************************************
template <typename object_type>
template <typename config_type>
sc_map_linear<object_type>::sc_map_linear(const size_type element_cnt_X,
        const sc_module_name name, const config_type configuration,
        const index_type start_id_X) :
        sc_map_base<range_type, object_type>(name),
        range(sc_map_linear_key(start_id_X),
        sc_map_linear_key(start_id_X+element_cnt_X-1))
{
    this->init(base::range.get_key_vector(), typename base::creator(), configuration);

    return;
}
