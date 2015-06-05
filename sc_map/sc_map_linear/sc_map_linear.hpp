/*!
 * @file sc_map_linear.hpp
 * @author Christian Amstutz
 * @date June 5, 2015
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

template <typename object_T>
class sc_map_linear : public sc_map_base<sc_map_linear_key_range, object_T>
{
public:
    typedef sc_map_base<sc_map_linear_key_range, object_T> base;
    typedef typename base::key_type::index_type index_type;

    sc_map_linear(const typename base::size_type element_cnt_X, const sc_module_name name, const index_type start_id_X = sc_map_linear_key::default_start_id);
    template <typename config_type>
    sc_map_linear(const typename base::size_type element_cnt_X, const sc_module_name name, const config_type configuration, const index_type start_id_X = sc_map_linear_key::default_start_id);
    virtual ~sc_map_linear() {};
};

//******************************************************************************

//******************************************************************************
template <typename object_T>
sc_map_linear<object_T>::sc_map_linear(const typename base::size_type element_cnt_X,
        const sc_module_name name, const index_type start_id_X) :
        sc_map_base<typename base::range_type, object_T>(name)
{
    base::range = typename base::range_type(sc_map_linear_key(start_id_X),
            sc_map_linear_key(start_id_X+element_cnt_X-1));

    std::vector<typename base::key_type> range_keys = base::range.get_key_vector();

    this->init(range_keys, typename base::creator());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_linear<object_T>::sc_map_linear(const typename base::size_type element_cnt_X,
        const sc_module_name name, const config_type configuration,
        const index_type start_id_X) :
        sc_map_base<typename base::range_type, object_T>(name)
{
    base::range = typename base::range_type(sc_map_linear_key(start_id_X),
                sc_map_linear_key(start_id_X+element_cnt_X-1));

    this->init(base::range.get_key_vector(), typename base::creator(), configuration);

    return;
}
